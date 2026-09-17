# GD32 NAS Panel Bootloader

GD32F303CGT6 裸机单区 bootloader，使用 GD32 官方 USB DFU class。项目结构和 CMake
构建方式与 `gd32-app` 保持一致。

## Flash 布局

| 区域 | 起始地址 | 容量 | 烧录文件 |
|---|---:|---:|---|
| Bootloader | `0x08000000` | 32 KB | `nas-panel-bootloader.bin` |
| APP | `0x08008000` | 984 KB | APP BIN |
| 风扇配置 | `0x080FF000` | 4 KB | 保留 |

APP 区最后一个 4 KB 页仅保存镜像长度和 CRC32。APP BIN 保持原始内容，不包含镜像头或尾部元数据。

## 启动与升级

APP 将 `BKP_DATA_0` 写为 `0xB007` 后复位，bootloader 即进入 DFU 模式。没有该标记时，
bootloader 校验 APP 向量表、尾部元数据及 CRC32；校验通过便跳转至 APP，失败则留在 DFU 模式。

DFU VID:PID 为 `3939:3927`，内部 Flash target 为 `0x08008000` 至 `0x080FE000`。
升级期间风扇全速运行，LCD 显示 `Updating: N%`，并以 250 ms 周期循环显示零至三个点。
DFU manifest 时会再次校验完整镜像，成功后清除 BKP 标记并复位。

## 构建

```sh
cmake -S gd32-bootloader -B gd32-bootloader/cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build gd32-bootloader/cmake-build-release --parallel
```

## DFU 测试脚本

脚本依赖 `dfu-util`。先只校验 APP BIN：

```sh
python3 gd32-bootloader/Tools/dfu_update.py APP.bin --check
```

列出 DFU 设备：

```sh
python3 gd32-bootloader/Tools/dfu_update.py --list
```

下载已校验的 APP BIN，完成后设备自动复位：

```sh
python3 gd32-bootloader/Tools/dfu_update.py APP.bin
```

更多 DFU 传输细节见 [Docs/dfu.md](Docs/dfu.md)。
