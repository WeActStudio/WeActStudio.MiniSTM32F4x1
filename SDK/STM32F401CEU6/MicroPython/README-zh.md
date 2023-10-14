# MicroPython 固件刷入说明

* [English Version](./README.md)

## WeAct Studio STM32F401CEU6

板子没有焊接flash刷入名称含有`internal`的固件，焊接了flash，根据flash的大小选择对应的固件`8M`,`4M`，8MHz晶振版本请进`8MHz_Version`文件夹。

恢复出厂设置：按住KEY键，单击复位键，蓝色LED闪烁三下，松开KEY键，即可恢复出厂设置

> 最新固件为：`firmware_xxxxxxx_stm32f401_vxx_v1.14-7`

4MB SPI Flash:

* 硬件版本：V3.0对应固件为：`firmware_4m_flash_stm32f401ce_v30_v1.xx-xxx.hex`

8MB SPI Flash:

* 硬件版本：V3.0对应固件为：`firmware_8m_flash_stm32f401ce_v30_v1.xx-xxx.hex`

内置Flash Internal Rom:

* `firmware_internal_rom_stm32f401ce_v30_v1.xx-xxx.hex`

遇到特殊问题需要擦除外置SPI Flash的：
> 刷入该固件可以擦除外挂的SPI Flash，`LED` 50ms快闪为识别Flash失败，长亮为擦除进行中，0.5s快闪为擦除成功，0.5s慢闪擦除失败

* `SPIFlash_Erase_Firmware.hex`

> micropython入门使用中文教程：<https://www.weact-tc.cn/2020/01/01/micropython/>

更多资料请访问：<https://gitee.com/WeActTC/WeAct_F411CE.git>

## 如何编译micropython 需使用linux (ubuntu或Win10企业版linux子系统)

不建议自己编译固件，使用我们提供的固件即可，如确实需要编译，请自备linux基础使用知识，以下均为linux下的操作

``` c
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j4
cd ../ports/stm32/boards
```

复制当前资料文件夹下的`WeAct_F401CE`到linux系统相应的文件下

``` c
复制 WeAct_F401CE 到 micropython/ports/stm32/boards
```

然后

``` c
cd YourPath/micropython/ports/stm32/

make BOARD=WeAct_F401CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j
# 或者
make BOARD=WeAct_F401CE -j
```

注意：CROSS_COMPILE 修改为自己的编译器路径

## mpconfigboard.h 相应修改

``` c
/* 板子版本为 V2.0 设置为 1 ，其他设置为 0 例如.V1.3,V2.1 V3.0 */
#define VERSION_V20 (1)

/* 使用内置flash改1 使用外置flash改0 */
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)

// Flash Size:
// 4MB Flash 32Mbit
// 8MB Flash 64Mbit
// 16MB Flash 128Mbit
#define MICROPY_HW_SPIFLASH_SIZE_BITS (32 * 1024 * 1024)
```

SPI FLASH:

``` c
#define MICROPY_HW_SPIFLASH_CS      (pin_A4)
#define MICROPY_HW_SPIFLASH_SCK     (pin_A5)
#if VERSION_V20
 #define MICROPY_HW_SPIFLASH_MISO    (pin_B4)
#else
 #define MICROPY_HW_SPIFLASH_MISO    (pin_A6)
#endif
#define MICROPY_HW_SPIFLASH_MOSI    (pin_A7)
```
