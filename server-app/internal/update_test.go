package main

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log/slog"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
	"time"
)

// TestCompareRelease 验证数值顺序和开发构建不会被误判为正式旧版。
func TestCompareRelease(t *testing.T) {
	for _, tc := range []struct{ current, latest, want string }{
		{"v0.1.0", "v0.2.0", "available"},
		{"v1.9.0", "v1.10.0", "available"},
		{"1.2", "v1.2.0", "current"},
		{"v2.0.0", "v1.9.0", "current"},
		{"21cdb6e", "v1.0.0", "unknown"},
		{"v1.0.0-2-gabcdef", "v1.0.0", "unknown"},
		{"v1.0.0-dirty", "v1.0.0", "unknown"},
		{"v1.0.0-rc.1", "v1.0.0", "unknown"},
		{"v1.0.0", "invalid", "unknown"},
	} {
		if got := compareRelease(tc.current, tc.latest); got != tc.want {
			t.Errorf("%q -> %q: got %s, want %s", tc.current, tc.latest, got, tc.want)
		}
	}
}

// TestFetchUpdate 覆盖未发布、限流、异常数据和有效发布的响应。
func TestFetchUpdate(t *testing.T) {
	for _, tc := range []struct {
		name        string
		code        int
		body, state string
		fail        bool
	}{
		{"release", 200, `{"tag_name":"v1.2.0"}`, "available", false},
		{"no release", 404, "", "unreleased", false},
		{"rate limit", 403, "", "", true},
		{"server error", 500, "", "", true},
		{"bad JSON", 200, "invalid", "", true},
		{"missing tag", 200, `{}`, "", true},
		{"prerelease", 200, `{"tag_name":"v2.0.0","prerelease":true}`, "", true},
	} {
		t.Run(tc.name, func(t *testing.T) {
			server := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) { w.WriteHeader(tc.code); fmt.Fprint(w, tc.body) }))
			defer server.Close()
			result, err := fetchUpdate(context.Background(), server.Client(), server.URL, "v1.0.0")
			if (err != nil) != tc.fail {
				t.Fatalf("unexpected error: %v", err)
			}
			if tc.fail {
				return
			}
			if result.State != tc.state {
				t.Fatalf("state: %s", result.State)
			}
			if tc.state == "available" && result.ReleaseURL != releasesURL+"/tag/v1.2.0" {
				t.Fatalf("URL: %s", result.ReleaseURL)
			}
		})
	}
}

// TestFetchUpdateCanceled 验证请求取消时检查及时结束。
func TestFetchUpdateCanceled(t *testing.T) {
	ctx, cancel := context.WithTimeout(context.Background(), time.Nanosecond)
	defer cancel()
	<-ctx.Done()
	if _, err := fetchUpdate(ctx, http.DefaultClient, latestReleaseAPI, "v1.0.0"); err == nil {
		t.Fatal("expected cancellation")
	}
}

// updateTransport 为路由测试提供隔离的 GitHub 响应。
type updateTransport struct{}

// RoundTrip 校验目标并返回固定的发布数据。
func (updateTransport) RoundTrip(request *http.Request) (*http.Response, error) {
	if request.URL.String() != latestReleaseAPI {
		return nil, fmt.Errorf("unexpected URL: %s", request.URL)
	}
	return &http.Response{StatusCode: http.StatusOK, Header: make(http.Header), Body: io.NopCloser(strings.NewReader(`{"tag_name":"v1.2.0"}`))}, nil
}

// TestUpdateRoute 验证根路径和反代前缀都能返回更新结果。
func TestUpdateRoute(t *testing.T) {
	previous := http.DefaultClient
	http.DefaultClient = &http.Client{Transport: updateTransport{}}
	defer func() { http.DefaultClient = previous }()
	cfg := Default()
	cfg.BasePath = "/nas-panel"
	server := NewServer(&Store{cfg: cfg}, nil, nil, nil, BuildInfo{Version: "v1.0.0"}, t.TempDir(), slog.New(slog.NewTextHandler(io.Discard, nil)))
	handler := server.Handler()
	for _, path := range []string{"/api/v1/update", "/nas-panel/api/v1/update"} {
		writer := httptest.NewRecorder()
		handler.ServeHTTP(writer, httptest.NewRequest(http.MethodGet, path, nil))
		var result UpdateResult
		if writer.Code != http.StatusOK {
			t.Fatalf("%s: HTTP %d", path, writer.Code)
		}
		if err := json.Unmarshal(writer.Body.Bytes(), &result); err != nil {
			t.Fatal(err)
		}
		if result.State != "available" {
			t.Fatalf("%s: %+v", path, result)
		}
	}
}
