package main

import (
	"errors"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

// firmwareStatus 返回升级任务和服务器 DFU 工具的可用状态。
func (s *Server) firmwareStatus(writer http.ResponseWriter, _ *http.Request) {
	writer.Header().Set("Cache-Control", "no-store")
	writeJSON(writer, http.StatusOK, s.firmware.Status())
}

// uploadFirmware 有界读取单个 BIN，校验通过后提交后台任务。
func (s *Server) uploadFirmware(writer http.ResponseWriter, request *http.Request) {
	defer request.Body.Close()
	if request.Header.Get("Sec-Fetch-Site") == "cross-site" {
		writeError(writer, http.StatusForbidden, errors.New("cross-site firmware upload is not allowed"))
		return
	}
	if origin := request.Header.Get("Origin"); origin != "" {
		parsed, err := url.Parse(origin)
		if err != nil || parsed.Host != request.Host {
			writeError(writer, http.StatusForbidden, errors.New("firmware upload must come from this server"))
			return
		}
	}
	request.Body = http.MaxBytesReader(writer, request.Body, firmwareMaxSize+64*1024)
	reader, err := request.MultipartReader()
	if err != nil {
		writeError(writer, http.StatusBadRequest, errors.New("upload a multipart APP BIN file"))
		return
	}
	var filename string
	var image []byte
	for {
		part, err := reader.NextPart()
		if errors.Is(err, io.EOF) {
			break
		}
		if err != nil {
			writeError(writer, http.StatusBadRequest, fmt.Errorf("invalid upload: %w", err))
			return
		}
		if part.FormName() != "file" || part.FileName() == "" || filename != "" {
			part.Close()
			writeError(writer, http.StatusBadRequest, errors.New("upload exactly one file named file"))
			return
		}
		filename = part.FileName()
		image, err = io.ReadAll(io.LimitReader(part, firmwareMaxSize+1))
		part.Close()
		if err != nil {
			writeError(writer, http.StatusBadRequest, err)
			return
		}
		if len(image) > firmwareMaxSize {
			writeError(writer, http.StatusRequestEntityTooLarge, errors.New("APP BIN exceeds the application flash area"))
			return
		}
	}
	if err := s.firmware.Start(filename, image); err != nil {
		status := http.StatusBadRequest
		if errors.Is(err, errFirmwareBusy) {
			status = http.StatusConflict
		}
		if errors.Is(err, errDFUMissing) {
			status = http.StatusServiceUnavailable
		}
		writeError(writer, status, err)
		return
	}
	writeJSON(writer, http.StatusAccepted, s.firmware.Status())
}
