# NAS Panel Server

`server-app` 是 NAS Panel 的上位机服务，由 Go 后端和 Vue 3 前端组成。Go 服务采集 NAS 状态、响应 GD32 的 USB HID v4 请求，并提供 Web API；Vue 页面用于查看实时状态和配置 About 页二维码。

## 功能

- 自动连接 `3939:0831` HID 设备，可按序列号筛选。
- 严格按照固件的 256 字节 HID v4 协议一问一答。
- 采集运行时间、CPU、内存、物理网卡、流量和挂载磁盘信息。
- 使用 `smartctl` 补充硬盘温度、健康状态、通电时间和通电次数；未安装时其余功能正常运行。
- 每两秒缓存系统状态，HID 请求不等待耗时的系统命令。
- Web 页面包含五个状态页面、风扇曲线页面和设置页面，支持中英文及深浅色主题。
- Web 端可编辑 CPU/HDD 独立的 20 点风扇曲线，保存后通过 HID 发给 GD32 并写入片内 Flash。
- 根据 GD32 上报的电压和电流累计当前开机与历史总耗电，并持久化保存。
- HID 断开后自动重连，Web 服务保持运行。

## 开发环境

需要 Go 1.24 或更高版本、Node.js 22.18 或更高版本，以及 C 编译器。`go-hid` 内置 HIDAPI；Linux 默认使用 hidraw 后端，并需要 libudev 开发包。

Debian/Ubuntu：

```sh
sudo apt install build-essential libudev-dev smartmontools
```

安装依赖并构建：

```sh
cd server-app
npm --prefix web install
npm --prefix web run build
(cd internal && go mod download && go build -o ../nas-panel-server .)
```

构建完成后运行：

```sh
./nas-panel-server -config config.json -web-dir web/dist -energy-file data/energy.json
```

首次启动会生成 `config.json`。浏览器访问 `http://NAS-IP:8080`。没有连接面板时，系统采集和 Web 页面仍然可用，服务会每两秒尝试重新连接 HID。

耗电量以 kWh（度）保存到 `-energy-file` 指定的 JSON 文件。服务每 30 秒及正常退出时原子写入一次。当前开机耗电通过系统 boot ID 识别，因此同一次开机中重启服务不会清零，NAS 重启后才重新累计；历史总耗电持续累加。USB HID 断联期间没有新的功率采样，不会使用旧功率推算耗电。

前端开发服务器：

```sh
(cd internal && go run . -config ../config.json -web-dir ../web/dist -energy-file ../data/energy.json)
npm --prefix web run dev
```

Vite 开发服务器会把 `/api` 转发到 `localhost:8080`。

Web 翻译文件位于 `web/src/i18n/`，每种语言一个文件；新增语言时添加词条文件并在 `i18n/index.js` 注册即可。

## 配置

```json
{
  "listen": ":8080",
  "panelSerial": "676643860B34",
  "serverVersion": "0.1.0",
  "publicScheme": "https",
  "publicPort": 443,
  "basePath": "/nas-panel",
  "links": [
    { "name": "Project", "url": "https://github.com/Deadline039/nas-panel" }
  ],
  "fanCurves": {
    "cpu": [0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100],
    "hdd": [0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100]
  }
}
```

- `listen`：HTTP 监听地址，修改后重启生效。
- `panelSerial`：留空时连接第一块匹配的面板，修改后重启服务生效。
- `serverVersion`：最多 9 个 UTF-8 字节，与 8 位 Git hash 组成 `v0.1.0(12345678)` 后发给面板。
- `publicScheme`、`publicPort`、`basePath`：在 `config.json` 中设置网页的公开协议、端口和反代路径。服务根据每块物理网卡的 IPv4 地址自动生成二维码，例如 `https://192.168.1.10:443/nas-panel/`。
- `links`：可选的额外二维码，排在自动生成的设置地址之后，每个 URL 最多 49 个 UTF-8 字节。
- `fanCurves.cpu` 和 `fanCurves.hdd`：各 20 个 0～100 的 PWM 百分比。前 16 个值对应 25～100℃、每 5℃ 一档，后 4 个值跟随 100℃ 档以保持协议长度；数值必须单调不减。低于 25℃按 25℃处理，高于 100℃按 100℃处理。

前端资源使用相对路径，API 会自动带上浏览器当前访问前缀。Go 服务同时接受根路径和配置的 `basePath`，因此反向代理可以保留或剥离前缀。以下两种 Nginx 写法均可：

```nginx
# Strip /nas-panel before forwarding.
location /nas-panel/ {
    proxy_pass http://127.0.0.1:8080/;
}

# Preserve /nas-panel when forwarding.
location /nas-panel/ {
    proxy_pass http://127.0.0.1:8080;
}
```

修改 `listen`、`panelSerial` 或 `basePath` 后需要重启服务。公开协议和端口只用于生成二维码，可以立即生效。

Linux 下只展示 sysfs 识别到的物理硬盘。分区、LVM 和软件 RAID 用于计算对应物理盘的占用率，不会作为额外硬盘展示。

## Linux 安装

构建完整项目：

```sh
make
```

将以下内容复制到 NAS：

```text
/opt/nas-panel/nas-panel-server
/opt/nas-panel/web/dist/
/etc/nas-panel/config.json
```

创建 `nas-panel` 用户和用户组，然后安装：

```text
deploy/70-nas-panel.rules -> /etc/udev/rules.d/70-nas-panel.rules
deploy/nas-panel.service  -> /etc/systemd/system/nas-panel.service
```

重载规则并启动服务：

```sh
sudo udevadm control --reload-rules
sudo udevadm trigger
sudo systemctl daemon-reload
sudo systemctl enable --now nas-panel
```

读取 SMART 信息通常需要额外设备权限。若服务用户无权运行 `smartctl`，硬盘健康、温度和使用时间会保留为默认值，不影响容量、占用率和 USB 通信。

## API

- `GET /api/v1/status`：系统指标、耗电量、面板连接状态、最新 GD32 上报和构建信息。
- `GET /api/v1/config`：当前配置。
- `PUT /api/v1/config`：校验并原子保存完整配置。
- `GET /api/v1/health`：服务健康检查。

## 检查

```sh
cd internal && go test ./...
npm --prefix web run build
python3 tests/test_hid.py --dry-run
```

Python HID 测试工具和协议细节见 [tests/README.md](tests/README.md)。
