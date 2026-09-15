package main

import (
	"context"
	"flag"
	"log/slog"
	"os"
	"os/signal"
	"syscall"

	"github.com/sstallion/go-hid"
)

var (
	version = "dev"
	commit  = "unknown"
)

func main() {
	configPath := flag.String("config", "config.json", "configuration file path")
	webDirectory := flag.String("web-dir", "web/dist", "built Vue application directory")
	energyPath := flag.String("energy-file", "data/energy.json", "persistent energy data file")
	listen := flag.String("listen", "", "override the configured HTTP listen address")
	debug := flag.Bool("debug", false, "enable debug logging")
	flag.Parse()

	level := slog.LevelInfo
	if *debug {
		level = slog.LevelDebug
	}
	logger := slog.New(slog.NewTextHandler(os.Stdout, &slog.HandlerOptions{Level: level}))
	store, err := Load(*configPath)
	if err != nil {
		logger.Error("load configuration", "error", err)
		os.Exit(1)
	}
	address := store.Get().Listen
	if *listen != "" {
		address = *listen
	}

	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)
	defer stop()
	collector := NewCollector(logger)
	go collector.Run(ctx)
	energyMeter, err := NewEnergyMeter(*energyPath, logger)
	if err != nil {
		logger.Error("load energy data", "error", err)
		os.Exit(1)
	}
	defer func() {
		if err := energyMeter.Close(); err != nil {
			logger.Warn("flush energy data", "error", err)
		}
	}()

	if err := hid.Init(); err != nil {
		logger.Error("initialize HID", "error", err)
		os.Exit(1)
	}
	defer func() {
		if err := hid.Exit(); err != nil {
			logger.Warn("finalize HID", "error", err)
		}
	}()
	buildInfo := BuildInfo{Version: version, Commit: commit}
	panelService := NewService(store, collector, energyMeter, buildInfo, logger)
	go panelService.Run(ctx)

	server := NewServer(store, collector, panelService, energyMeter, buildInfo, *webDirectory, logger)
	if err := RunHTTPServer(ctx, address, server.Handler(), logger); err != nil {
		logger.Error("web server stopped", "error", err)
		os.Exit(1)
	}
}
