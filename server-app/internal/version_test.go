package main

import (
	"encoding/json"
	"strings"
	"testing"
)

// TestPanelBuildVersion 验证面板使用关于页的构建版本，不再从设置读取版本。
func TestPanelBuildVersion(t *testing.T) {
	for _, version := range []string{"v0.1", "v1.2.3", "dev"} {
		response := responseFor(Request{Page: PageAbout}, Snapshot{}, Default(), BuildInfo{Version: version, Commit: "12345678"})
		if response.About.ServerVersion != version+"(12345678)" {
			t.Fatalf("unexpected version %q", response.About.ServerVersion)
		}
	}
	data, err := json.Marshal(Default())
	if err != nil {
		t.Fatal(err)
	}
	if strings.Contains(string(data), "serverVersion") {
		t.Fatal("editable version is still exposed")
	}
}
