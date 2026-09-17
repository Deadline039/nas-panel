# DFU 升级

Bootloader 以 GD32 官方 DFU class 枚举为 `3939:3927`，只提供一个内部 Flash target：
`0x08008000` 至 `0x080FE000`。APP 区最后一个 4 KB 页保存镜像长度和 CRC32，DFU 无法擦写
bootloader、元数据页和风扇配置区。

APP 设置 `BKP_DATA_0` 为 `0xB007` 并复位后，bootloader 保持在 DFU 模式；没有该标记且
APP 镜像有效时，bootloader 跳转到 APP。DFU manifest 成功后清除标记并复位。

```sh
python3 gd32-bootloader/Tools/dfu_update.py --list
python3 gd32-bootloader/Tools/dfu_update.py gd32-app/cmake-build-release/nas-panel.bin
```

脚本先校验 APP BIN 的向量表、长度与 CRC32，再生成带两个 DfuSe element 的临时文件：第一个
element 写入尾部元数据，第二个写入 APP BIN。

```sh
python3 gd32-bootloader/Tools/dfu_update.py nas-panel.bin
```

DFU 传输块大小为 2048 字节。进入 DFU 后 LCD 显示 `Updating: N%`，每 250 ms 循环显示三个
点位；总长度从尾部元数据读取。每个 Flash 写入字均回读验证，manifest 时校验启动向量和整包
CRC32。失败时保留 DFU 模式。
