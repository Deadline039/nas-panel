# NAS Panel Server

`server-app` 是 NAS Panel 的上位机服务，由 Go 后端和 Vue 3 前端组成。Go 服务采集 NAS 状态、响应 GD32 的 USB HID v1 请求，并提供 Web API；Vue 页面用于查看实时状态和配置 About 页二维码。

## 功能

- 自动连接 `3939:0831` HID 设备，可按序列号筛选。
- 严格按照固件的 256 字节 HID v1 协议一问一答。
- 采集运行时间、CPU、内存、物理网卡、流量和挂载磁盘信息。
- 使用 `smartctl` 补充硬盘温度、健康状态、通电时间和启停次数；未安装时其余功能正常运行。
- 每两秒缓存系统状态，HID 请求不等待耗时的系统命令。
- Web 页面包含五个状态页面、风扇曲线页面和设置页面，支持中英文及深浅色主题。
- Web 端可编辑 CPU/HDD 独立的 20 点风扇曲线，保存后通过 HID 发给 GD32 并写入片内 Flash。
- 根据 GD32 上报的电压和电流累计当前开机与历史总耗电，并持久化保存。
- HID 断开后自动重连，Web 服务保持运行。

## 开发环境

需要 Go 1.24 或更高版本、Node.js 22.18 或更高版本，以及 C 编译器。`go-hid` 内置 HIDAPI；Linux 默认使用 hidraw 后端，并需要 libudev 开发包。

Debian/Ubuntu：

```sh
sudo apt install build-essential libudev-dev smartmontools dfu-util
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
  "webPort": 8080,
  "panelSerial": "676643860B34",
  "serverVersion": "0.1.0",
  "publicScheme": "https",
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

- `webPort`：Web 和 API 共用的端口（1～65535，默认 8080），监听所有本机地址。二维码自动使用同一端口，修改后保存并重启服务生效。旧的 `listen`、`publicPort` 字段及 `-listen` 启动参数已移除，不提供兼容迁移。
- `panelSerial`：留空时连接第一块匹配的面板，修改后重启服务生效。
- `serverVersion`：最多 9 个 UTF-8 字节，与 8 位 Git hash 组成 `v0.1.0(12345678)` 后发给面板。
- `publicScheme`、`basePath`：在 `config.json` 中设置二维码链接的公开协议和反代路径。服务根据每块物理网卡的 IPv4 地址自动生成二维码，例如 `https://192.168.1.10:8080/nas-panel/`。
- 若反向代理的外部端口与 Web 端口不同，可在 `links` 添加完整的外部访问链接。
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

## CI 构建产物

GitHub Actions 会在推送、Pull Request 和手动触发时生成以下 Artifacts：

- `nas-panel-server-linux-amd64`
- `nas-panel-server-linux-arm64`
- `nas-panel-server-macos-amd64`
- `nas-panel-server-macos-arm64`
- `nas-panel-server-windows-amd64`
- `nas-panel-gd32-firmware`

Server 压缩包包含对应平台的可执行文件、Web 资源、`config.example.json` 和 README；Linux 压缩包额外包含安装与卸载脚本、systemd 服务和 udev 规则。固件压缩包包含 BIN、HEX、ELF、MAP 和反汇编 LST 文件。

## Linux 安装

GitHub Actions 的 `nas-panel-server-linux-amd64` 和 `nas-panel-server-linux-arm64` 产物包含一键安装脚本。解压对应架构的压缩包后运行：

```sh
sudo ./install.sh
```

脚本会询问服务运行用户：`1` 为专用用户 `nas-panel`（默认），`2` 为 `root`。root 模式下，整个服务及网页接口都拥有 root 权限。

也可以通过参数指定，跳过询问：

```sh
sudo ./install.sh --user root
sudo ./install.sh --user nas-panel
```

非交互运行且未指定参数时使用 `nas-panel`。重新安装时可重新选择运行用户。脚本在两种模式下都会创建 `nas-panel` 系统用户和组，用于配置文件权限及 udev 规则，安装程序、Web 资源、systemd 服务和 udev 规则，并把卸载命令安装到 `/usr/local/sbin/nas-panel-uninstall` 后启动服务。已有的 `/etc/nas-panel/config.json` 内容不会被覆盖。

若之前通过 `systemctl edit nas-panel.service` 设置过 `User`、`Group` 或能力限制，请移除对应的自定义配置，否则其优先级高于安装脚本生成的服务文件。

卸载程序和服务，同时保留配置及累计电量数据：

```sh
sudo nas-panel-uninstall
```

需要连同 `/etc/nas-panel`、`/var/lib/nas-panel`、系统用户和用户组一起删除时使用：

```sh
sudo nas-panel-uninstall --purge
```

手动安装方式如下。

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
deploy/uninstall.sh       -> /usr/local/sbin/nas-panel-uninstall
```

重载规则并启动服务：

```sh
sudo udevadm control --reload-rules
sudo udevadm trigger
sudo systemctl daemon-reload
sudo systemctl enable --now nas-panel
```

SMART 采集依赖 `smartmontools`。专用用户模式的 systemd 服务通过 `SupplementaryGroups=disk` 访问磁盘设备，
并通过 `CAP_SYS_RAWIO` 执行 ATA/SAT 直通命令；仍以 `nas-panel` 用户运行，保留
`NoNewPrivileges=true`。这些权限仅授予服务及其子进程，不修改所有用户的磁盘权限或 smartctl 文件权限。
特殊 RAID/USB 桥接或其他控制器仍可能需要额外的设备类型配置或权限。
root 模式不设置上述附加组和能力限制，同样保留 `NoNewPrivileges=true`。

已有安装需更新 service 文件后运行 `sudo systemctl daemon-reload` 和
`sudo systemctl restart nas-panel`；重新运行新版安装脚本也会更新服务文件并保留配置和耗电数据。
服务启动时立即采集，之后 SMART 每分钟刷新。查询使用 `smartctl -n standby -a -j`，检测到待机或睡眠状态时跳过完整读取，不主动唤醒硬盘，也不将休眠跳过记录为告警。休眠期间保留本次服务运行中上次成功采集的 SMART 数据（温度等并非实时值）；尚无缓存时保留默认值，硬盘恢复活动后自动刷新。部分 USB 桥接或控制器不支持电源状态检查，仍需在实际设备上验证休眠行为。失败原因现在以 Warning 写入正常日志：

```sh
sudo journalctl -u nas-panel -n 100 --no-pager
```

日志会保留 smartctl 的权限不足、缺少工具、设备类型错误或超时说明。
页面的“启停次数”来自 ATA SMART 属性 4（`Start_Stop_Count`）的原始值，API 和 HID 字段仍使用 `cycles`。未提供此属性的硬盘显示 0，不使用通电次数替代。

## API

- `GET /api/v1/status`：系统指标、耗电量、面板连接状态、最新 GD32 上报和构建信息。
- `GET /api/v1/config`：当前配置。
- `PUT /api/v1/config`：校验并原子保存完整配置。
- `GET /api/v1/update`：手动查询 GitHub 最新正式 Release，返回版本比较结果及发布页面链接（8 秒超时）。
- `GET /api/v1/health`：服务健康检查。

## 检查

```sh
cd internal && go test ./...
npm --prefix web run build
python3 tests/test_hid.py --dry-run
```

Python HID 测试工具和协议细节见 [tests/README.md](tests/README.md)。

About 页位于导航末尾，提供“检查更新”按钮。检查基于实际构建版本，与可编辑的 `serverVersion` 无关；纯 commit、开发构建及无法比较的版本会提示手动查看发布页面。当前只检查正式 Release，不自动下载或安装；没有正式 Release 时会明确提示。

HID 协议编号统一为 v1，保留当前 256 字节帧和风扇设置数据布局。服务端、测试工具和 GD32 固件需配套更新。

## 面板固件升级

About 页的“面板固件升级”支持上传本地 APP `.bin`；GitHub Release 固件升级入口暂未开放。
浏览器将文件上传给 NAS 上的 Go 服务，由服务器调用 `dfu-util` 操作连接在 NAS 上的面板。

服务器需要安装 `dfu-util` 并确保服务进程的 PATH 能找到它。Debian/Ubuntu 使用
`sudo apt install dfu-util`，macOS 使用 `brew install dfu-util`。Windows 需要安装 dfu-util，
并为 DFU 设备 `3939:3927` 配置兼容 libusb 的驱动。Linux 的部署规则已包含 DFU USB 权限；
已有安装需更新 `deploy/70-nas-panel.rules`、重载 udev 并重新插拔设备。

选择链接到 `0x08008000` 的原始 APP BIN，最大 984 KiB。不要选择 bootloader BIN、合并镜像或 ELF。
服务端校验大小、栈顶和复位向量后，在内存中计算 CRC32，生成与
`gd32-bootloader/Tools/dfu_update.py` 一致的 DfuSe 文件：先传长度和 CRC，再传 APP。
临时文件在任务结束后删除。

点击“开始升级”后，服务端通过 HID 设置命令让 APP 进入 bootloader，并暂时停止 HID 重连。
下载结束后单独发送 manifest，由 bootloader 校验 Flash CRC32、提交元数据并重启。
即使 dfu-util 在设备复位时返回 74，也只有同一序列号的面板重新发送有效 HID 数据才显示成功。
升级阶段和日志可在网页查看，刷新页面不会中止后台任务；同时只允许一个升级任务。
升级期间保持供电和 USB 连接。失败后可以重新选择 BIN 重试。

首次使用自动进入功能需要已烧录包含 `USB_DATA_SETTING_BOOTLOADER` 命令的 APP。
旧版 APP 无法响应此命令时，请先手动进入 bootloader：同时按住板上的上、下按键并复位，保持超过 3 秒，
或通过现有调试方式进入。已处于 DFU 的面板也可以直接上传升级。
多面板时使用 `panelSerial` 指定目标；未指定时，恢复模式只接受唯一一块 DFU 面板。

- `GET /api/v1/firmware`：DFU 工具可用性及当前任务状态。
- `POST /api/v1/firmware`：multipart 上传，唯一文件字段为 `file`；接受后返回 HTTP 202。
- `/api/v1/status` 同时返回 `firmware`，便于页面轮询。

本地开发验证：`cd internal && go test -race ./...`。测试使用模拟设备，不执行硬件擦写。


## 硬盘状态 LED

在存储状态表下方的 LED 区域点击“LED 设置”，依次测试四个灯位的 `color0`、`color1`，观察实际灯色并选择对应颜色。勾选“所有灯颜色一致”后，仅第一列颜色可编辑，其他列跟随；每列仍可独立测试。测试只覆盖指定灯位，5 秒后自动恢复状态显示，也可提前停止。

在同页为硬盘选择 LED 位置和正常、警告、错误对应的颜色组合。一个灯位只能绑定一块硬盘，一块硬盘只能绑定一个灯位，三个状态必须使用不同的组合（color0、color1、两者同时亮）。选择已使用的状态颜色时交换两个状态的颜色；保存到已占用灯位前会要求确认替换。离线绑定会保留，可解除或替换。

“与硬盘唯一标识绑定（UUID / WWN）”使用 Linux `/dev/disk/by-id` 中已有的整盘标识，优先 WWN、NVMe EUI/UUID，再使用带序列号的标识。不使用分区/文件系统 UUID，避免一盘多分区或重新格式化导致歧义；没有稳定标识时该选项不可选。读取链接不额外发起磁盘探测，也不会绕过 SMART 休眠保护。绑定到稳定标识后，`/dev/sd*` 编号变化不会改变灯位；未勾选时按设备路径绑定。

配置保存在 `led` 字段，颜色只用于展示，实际字节由服务器按通道编码。每个 HID 回复都带上根据 SMART 状态计算的字节，GD32 原样输出。未绑定、磁盘离线、缺少有效健康数据或采集快照超过 30 秒未更新时关闭对应灯位；待机盘优先使用独立的休眠显示设置：熄灭、color0 闪烁或 color1 闪烁，默认熄灭；无需历史 SMART 健康缓存。闪烁由服务器在回复帧中约每秒切换一次，GD32 仍只输出原始字节。休眠与唤醒随每分钟的 SMART 检查更新，保留非唤醒查询参数。LED 设置立即应用，无需重启服务。测试需要连接面板，升级固件期间不可测试。
