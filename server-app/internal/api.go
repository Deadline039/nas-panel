package main

import (
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"log/slog"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"time"
)

// BuildInfo identifies the running server binary.
type BuildInfo struct {
	Version string `json:"version"`
	Commit  string `json:"commit"`
}

// Server exposes status, configuration, and the built Vue application.
type Server struct {
	config    *Store
	collector *Collector
	panel     *Service
	energy    *EnergyMeter
	build     BuildInfo
	webDir    string
	logger    *slog.Logger
}

// NewServer creates the HTTP API handler.
func NewServer(store *Store, collector *Collector, panelService *Service, energy *EnergyMeter, build BuildInfo, webDir string, logger *slog.Logger) *Server {
	return &Server{config: store, collector: collector, panel: panelService, energy: energy, build: build, webDir: webDir, logger: logger}
}

// Handler returns the complete API and static application handler.
func (s *Server) Handler() http.Handler {
	application := http.NewServeMux()
	application.HandleFunc("GET /api/v1/status", s.status)
	application.HandleFunc("GET /api/v1/config", s.getConfig)
	application.HandleFunc("PUT /api/v1/config", s.putConfig)
	application.HandleFunc("GET /api/v1/health", s.health)
	application.Handle("/", s.staticHandler())
	basePath := s.config.Get().BasePath
	if basePath == "" {
		return requestLogger(s.logger, application)
	}
	router := http.NewServeMux()
	router.Handle("/", application)
	router.Handle(basePath+"/", http.StripPrefix(basePath, application))
	router.HandleFunc(basePath, func(writer http.ResponseWriter, request *http.Request) {
		http.Redirect(writer, request, basePath+"/", http.StatusTemporaryRedirect)
	})
	return requestLogger(s.logger, router)
}

func (s *Server) status(writer http.ResponseWriter, _ *http.Request) {
	writeJSON(writer, http.StatusOK, map[string]any{
		"build":    s.build,
		"energy":   s.energy.Current(),
		"panel":    s.panel.Status(),
		"system":   s.collector.Current(),
		"settings": s.config.Get(),
	})
}

func (s *Server) getConfig(writer http.ResponseWriter, _ *http.Request) {
	writeJSON(writer, http.StatusOK, s.config.Get())
}

func (s *Server) putConfig(writer http.ResponseWriter, request *http.Request) {
	defer request.Body.Close()
	decoder := json.NewDecoder(io.LimitReader(request.Body, 64*1024))
	decoder.DisallowUnknownFields()
	var cfg Config
	if err := decoder.Decode(&cfg); err != nil {
		writeError(writer, http.StatusBadRequest, fmt.Errorf("invalid JSON: %w", err))
		return
	}
	if err := s.config.Save(cfg); err != nil {
		writeError(writer, http.StatusBadRequest, err)
		return
	}
	s.panel.QueueFanCurves(cfg.FanCurves)
	writeJSON(writer, http.StatusOK, s.config.Get())
}

func (s *Server) health(writer http.ResponseWriter, _ *http.Request) {
	writeJSON(writer, http.StatusOK, map[string]string{"status": "ok"})
}

func (s *Server) staticHandler() http.Handler {
	index := filepath.Join(s.webDir, "index.html")
	if _, err := os.Stat(index); err != nil {
		return http.HandlerFunc(func(writer http.ResponseWriter, _ *http.Request) {
			writeJSON(writer, http.StatusNotFound, map[string]string{
				"error": "web application is not built; run npm run build in server-app/web",
			})
		})
	}
	files := http.FileServer(http.Dir(s.webDir))
	return http.HandlerFunc(func(writer http.ResponseWriter, request *http.Request) {
		cleaned := filepath.Clean(strings.TrimPrefix(request.URL.Path, "/"))
		requested := filepath.Join(s.webDir, cleaned)
		if info, err := os.Stat(requested); err == nil && info.IsDir() == false {
			files.ServeHTTP(writer, request)
			return
		}
		http.ServeFile(writer, request, index)
	})
}

func writeJSON(writer http.ResponseWriter, status int, value any) {
	writer.Header().Set("Content-Type", "application/json; charset=utf-8")
	writer.WriteHeader(status)
	_ = json.NewEncoder(writer).Encode(value)
}

func writeError(writer http.ResponseWriter, status int, err error) {
	writeJSON(writer, status, map[string]string{"error": err.Error()})
}

func requestLogger(logger *slog.Logger, next http.Handler) http.Handler {
	return http.HandlerFunc(func(writer http.ResponseWriter, request *http.Request) {
		started := time.Now()
		next.ServeHTTP(writer, request)
		if strings.HasPrefix(request.URL.Path, "/api/") {
			logger.Debug("HTTP request", "method", request.Method, "path", request.URL.Path, "duration", time.Since(started))
		}
	})
}

// RunHTTPServer starts an HTTP server and shuts it down when the context is canceled.
func RunHTTPServer(ctx context.Context, address string, handler http.Handler, logger *slog.Logger) error {
	server := &http.Server{
		Addr:              address,
		Handler:           handler,
		ReadHeaderTimeout: 5 * time.Second,
		ReadTimeout:       15 * time.Second,
		WriteTimeout:      15 * time.Second,
		IdleTimeout:       time.Minute,
	}
	result := make(chan error, 1)
	go func() {
		logger.Info("web server listening", "address", address)
		result <- server.ListenAndServe()
	}()
	select {
	case <-ctx.Done():
		shutdownContext, cancel := context.WithTimeout(context.Background(), 5*time.Second)
		defer cancel()
		return server.Shutdown(shutdownContext)
	case err := <-result:
		if errors.Is(err, http.ErrServerClosed) {
			return nil
		}
		return err
	}
}
