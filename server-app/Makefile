SHELL := /bin/sh

VERSION ?= $(shell git describe --tags --always --dirty 2>/dev/null || echo dev)
COMMIT ?= $(shell git rev-parse --short=8 HEAD 2>/dev/null || echo unknown)
LDFLAGS := -s -w -X main.version=$(VERSION) -X main.commit=$(COMMIT)

.PHONY: all web server test clean

all: web server

web:
	cd web && npm ci && npm run build

server:
	cd internal && go build -ldflags "$(LDFLAGS)" -o ../nas-panel-server .

test:
	cd internal && go test ./...
	cd web && npm run build

clean:
	rm -rf nas-panel-server web/dist
