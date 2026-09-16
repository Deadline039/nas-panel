package main

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"regexp"
	"strconv"
	"time"
)

const releasesURL = "https://github.com/Deadline039/nas-panel/releases"
const latestReleaseAPI = "https://api.github.com/repos/Deadline039/nas-panel/releases/latest"

// UpdateResult 表示正式发布版本的检查结果，开发构建不推断版本先后。
type UpdateResult struct {
	State         string `json:"state"`
	LatestVersion string `json:"latestVersion,omitempty"`
	ReleaseURL    string `json:"releaseURL"`
}

// checkUpdate 按需检查更新，独立于系统采集和 HID 请求处理。
func (s *Server) checkUpdate(writer http.ResponseWriter, request *http.Request) {
	ctx, cancel := context.WithTimeout(request.Context(), 8*time.Second)
	defer cancel()
	result, err := fetchUpdate(ctx, http.DefaultClient, latestReleaseAPI, s.build.Version)
	writer.Header().Set("Cache-Control", "no-store")
	if err != nil {
		s.logger.Warn("check update", "error", err)
		writeError(writer, http.StatusBadGateway, fmt.Errorf("unable to check GitHub releases"))
		return
	}
	writeJSON(writer, http.StatusOK, result)
}

// fetchUpdate 查询正式 Release；只生成固定项目下的发布链接。
func fetchUpdate(ctx context.Context, client *http.Client, endpoint string, current string) (UpdateResult, error) {
	result := UpdateResult{State: "unreleased", ReleaseURL: releasesURL}
	request, err := http.NewRequestWithContext(ctx, http.MethodGet, endpoint, nil)
	if err != nil {
		return result, err
	}
	request.Header.Set("Accept", "application/vnd.github+json")
	request.Header.Set("User-Agent", "nas-panel-server")
	response, err := client.Do(request)
	if err != nil {
		return result, err
	}
	defer response.Body.Close()
	if response.StatusCode == http.StatusNotFound {
		return result, nil
	}
	if response.StatusCode != http.StatusOK {
		return result, fmt.Errorf("GitHub returned HTTP %d", response.StatusCode)
	}
	var release struct {
		Tag        string `json:"tag_name"`
		Draft      bool   `json:"draft"`
		Prerelease bool   `json:"prerelease"`
	}
	if err := json.NewDecoder(io.LimitReader(response.Body, 1024*1024)).Decode(&release); err != nil {
		return result, err
	}
	if release.Tag == "" || release.Draft || release.Prerelease {
		return result, fmt.Errorf("invalid stable release response")
	}
	result.LatestVersion = release.Tag
	result.ReleaseURL = releasesURL + "/tag/" + url.PathEscape(release.Tag)
	result.State = compareRelease(current, release.Tag)
	return result, nil
}

var releaseVersionPattern = regexp.MustCompile(`^v?(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)(?:\.(0|[1-9][0-9]*))?$`)

// releaseVersion 解析正式版本号；拒绝 commit、预发布及带未提交修改的构建。
func releaseVersion(value string) ([3]uint64, bool) {
	var version [3]uint64
	parts := releaseVersionPattern.FindStringSubmatch(value)
	if parts == nil {
		return version, false
	}
	for index, part := range parts[1:] {
		if part == "" {
			continue
		}
		value, err := strconv.ParseUint(part, 10, 64)
		if err != nil {
			return version, false
		}
		version[index] = value
	}
	return version, true
}

// compareRelease 按数值比较版本，无法可靠比较时保留未知状态。
func compareRelease(current string, latest string) string {
	installed, currentOK := releaseVersion(current)
	released, latestOK := releaseVersion(latest)
	if currentOK == false || latestOK == false {
		return "unknown"
	}
	for index := range installed {
		if released[index] > installed[index] {
			return "available"
		}
		if released[index] < installed[index] {
			return "current"
		}
	}
	return "current"
}
