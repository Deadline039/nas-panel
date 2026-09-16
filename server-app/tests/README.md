# NAS 面板测试

测试脚本统一为 `server-app/tests/test_hid.py`。它根据 GD32 请求的页面和条目返回模拟数据，页面与设备切换使用面板实体按键。

## 本机运行

在仓库根目录执行：

```sh
python3 -m venv server-app/.venv
server-app/.venv/bin/python -m pip install --index-url https://pypi.org/simple -r server-app/tests/requirements.txt
server-app/.venv/bin/python server-app/tests/test_hid.py --list
server-app/.venv/bin/python server-app/tests/test_hid.py --serial 676643860B34
```

先烧录配套固件并重新插拔 USB。当前为 **协议 v1**，不兼容旧版固件/测试脚本；VID/PID 仍为 `3939:0831`。只有一块面板时可省略 `--serial`。Windows 使用 `.venv\Scripts\python.exe`。

HID 脚本参数：`--count 10` 回复十次后退出；`--delay 1.2` 延迟回复；`--dry-run` 离线检查所有页面的数据布局和 CRC8。模拟数据包含三个网卡、三个磁盘和两个链接，由面板实体按键选择，并覆盖单位切换及温度、占用率阈值。

Linux 无法打开设备时，可在 `/etc/udev/rules.d/70-nas-panel.rules` 添加桌面会话权限规则，重载规则后重新插拔设备：

```text
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="3939", ATTRS{idProduct}=="0831", TAG+="uaccess"
```

## 协议 v1

HID Input/Output Report 固定 **256 字节，无 Report ID**。中断端点 `0x81`/`0x01` 的最大包长为 64 字节，由 USB 驱动分成四包传输。也支持控制端点 `SET_REPORT(Output, ID=0, length=256)`。

HIDAPI `write()` 需额外前置 `0x00`，参数总长 257 字节；前置字节不属于线上报告。`read(256)` 返回完整报告。

| 偏移 | 长度 | 字段 | 含义 |
| --- | --- | --- | --- |
| 0 | 1 | version | 固定 1 |
| 1 | 1 | type | 请求=0，回复=1 |
| 2 | 1 | reserved | 固定 0 |
| 3 | 4 | sequence | 请求序号，回复原样回传 |
| 7 | 2 | length | 有效载荷长度 |
| 9 | 1 | crc8 | 有效载荷 CRC8 |
| 10 | 246 | payload | packed 结构体，剩余填零 |

整数均为小端，浮点为 IEEE 754 binary32，字符串为定长 UTF-8 字节数组，建议尾部填零。

请求 `usb_data_report_t` 为 **12 字节**，Python 格式 `<BffBBB`：页面、电压 V、电流 A、CPU 风扇 PWM 百分比、硬盘风扇 PWM 百分比、选中条目索引 item_idx。百分比范围 0～100。运行时电压、电流来自 GD32 的 INA219；功率由本地电压×电流计算。

| page | 页面 | 回复结构体 | 字节数 | Python 格式 |
| --- | --- | --- | --- | --- |
| 0 | 概览 | `usb_data_resp_t` 前缀 + `usb_data_overview_t` | 11 | `<BBBBBIBB` |
| 1 | 网络 | `usb_data_resp_t` 前缀 + `usb_data_network_t` | 84 | `<BBBBBBBB12sffff16s16s16s` |
| 2 | 存储 | `usb_data_resp_t` 前缀 + `usb_data_disk_t` | 38 | `<BBBBBBB12sQBBBII` |
| 3 | 系统信息 | `usb_data_resp_t` 前缀 + `usb_data_sys_info_t` | 197 | `<BBBBB12s80s50s50s` |
| 4 | 关于/二维码 | `usb_data_resp_t` 前缀 + `usb_data_about_qrcode_t` | 87 | `<BBBBBBB50s30s` |

- 概览运行时间为 `uint32` 分钟，CPU/内存为百分比。
- 网络速率和累计流量基础单位为 KB/s、KB，UI 按 1024 进位显示 KB/MB/GB/TB。这里 KB 沿用项目的 1024 字节口径。
- About 页服务器版本按 `v0.1.0(12345678)` 格式传输，括号内是 8 位 Git commit hash。
- 磁盘容量为 `uint64` 字节，UI 最低从 KB 显示。磁盘使用率为百分比，温度为摄氏度，使用时间为小时。
- 每一个回复负载先放 5 字节前缀：`type`、`valid`、`page_set`、`cpu_temperature`、`hdd_temperature`，随后紧跟对应页面的数据。页面数据回复的 `type=0`、`valid=1`。`data` 是 GD32 收到数据后设置的本地指针，不在线上传输。
- 风扇设置回复使用 `type=1`、`page_set=0`，5 字节前缀后直接放 40 字节数组：前 20 字节是 CPU 曲线，后 20 字节是 HDD 曲线。整个负载为 45 字节，没有额外设置结构体。
- 风扇曲线协议仍传 20 个字节，前 16 个档位覆盖 25～100℃、每 5℃ 一档，后 4 个字节跟随 100℃ 档。低于 25℃按 25℃处理，高于 100℃按 100℃处理。每一档 PWM 必须大于等于前一档。CPU 和 HDD 使用独立曲线，写入后保存在 GD32 Bank1 最后一个 4 KB Flash 页。
- `idx` 从 0 开始，`total=0` 表示无条目。多条目由 GD32 的 item_idx 选择，NAS 必须原样回传 idx，禁止自动轮换。索引超出当前数量时，回复该 idx、最新 total，其余字段清零，GD32 调整索引后再次请求。
- 磁盘状态：0=Good、1=Warning、2=Failure。网络 status：0=未连接、1=获取地址中、2=已连接。

GD32 每秒请求当前页面。回复须匹配协议版本、外层类型、序号、页面和 CRC8；页面或条目改变后清除旧回复的有效标记，等待新回复再刷新页面。

## 显示规则

- Runtime：接收值和最低显示单位均为分钟。大于 60 分钟显示 h，大于 1440 分钟显示 d，换算结果四舍五入；因此 60 分钟显示 `60m`，90 分钟显示 `2h`，1440 分钟显示 `24h`。
- 网络流量和容量：KB→MB→GB→TB，每级 1024，保留一位小数。
- 网络 LED 与状态标签：未连接红色、获取地址中黄色、已连接绿色。
- 首页 NAS LED 与标签：pwr_get_state() 读取 GPIO，运行中绿色，关机灰色。
- 5 分钟无上下键操作关闭背光；首次按键只唤醒，下一次按键正常切换。USB 收发不重置休眠计时。
- 上下键先切换当前页条目，到达首尾后再切换页面；反向进入列表页时选中最后一项。
- 占用率：低于 75% 蓝色，75%～不足 90% 黄色，90% 起红色；圆环与百分比文字同步。
- 磁盘健康标签：Good 绿色，Warning 黄色，Failure 红色。
- CPU/磁盘温度：低于 50℃ 绿色，50℃～不足 85℃ 黄色，85℃ 起红色。

## 离线检查

```sh
python3 server-app/tests/test_hid.py --dry-run
cmake -S gd32-app -B gd32-app/cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build gd32-app/cmake-build-debug -j 6
```
