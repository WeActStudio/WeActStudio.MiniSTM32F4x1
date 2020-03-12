# Micropython
## WeAct_F401CC
> firmware_xxxxxxx_stm32f401_vxx_v1.12-35 The Latest 最新

> `4m_flash`: External Nor Flash as MSC Dervice 外部Nor Flash 作为 MSC 设备

> `none_rom`: None MSC Dervice,Use Serial PA9PA10.使用串口PA9PA10通讯

> 使用教程：https://www.weact-tc.cn/2020/01/01/micropython/


## How to build 如何编译 ubuntu/Win10内置linux

```
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j4
cd ../ports/stm32/boards
cp YourPath/WeAct_F401CC to micropython/ports/stm32/boards
cd YourPath/micropython/ports/stm32/
# CROSS_COMPILE 修改为自己的编译器路径
# CROSS_COMPILE Change to your own compiler path
make BOARD=WeAct_F411CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j4
# or 或者
make BOARD=WeAct_F411CE -j4
```
## mpconfigboard.h
```
/* BOARD Ver 2.0 set 1 ，other set 0 ex.V1.3,V2.1 V3.0 */
#define VERSION_V20 (1)

/* 使用内置flash改1 使用外置flash改0 */
/* Use the built-in flash to change to 1 
   use the external flash to change to 0 */
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)

// Flash Size:
// 4MB Flash 32Mbit
// 8MB Flash 64Mbit
// 16MB Flash 128Mbit
#define MICROPY_HW_SPIFLASH_SIZE_BITS (32 * 1024 * 1024)
```

```
SPIFLASH:
#define MICROPY_HW_SPIFLASH_CS      (pin_A4)
#define MICROPY_HW_SPIFLASH_SCK     (pin_A5)
#if VERSION_V20
	#define MICROPY_HW_SPIFLASH_MISO    (pin_B4)
#else 
	#define MICROPY_HW_SPIFLASH_MISO    (pin_A6)
#endif
#define MICROPY_HW_SPIFLASH_MOSI    (pin_A7)
```