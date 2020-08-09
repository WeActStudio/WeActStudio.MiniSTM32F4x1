# WeAct Studio STM32F411CEU6 Core Board

* [中文版本](./README-zh.md)

## 重要说明

如果板子背面没有`WeAct`和`版本号`，芯片批次是`537`或旧的，插针和板子是装在一个袋子里，`丝印印刷是错误的`(`3V3`印成了`V3V`)，肯定是盗版。可以issues我们或通过电子邮件(WeAct_TC@163.com)告知我们。

## How to build micropython need ubuntu or Win10 subsystem Linux

It is not recommended to compile the firmware yourself, just use the firmware provided by us. If you really need to compile, please bring your own basic Linux knowledge. The following are the operations under Linux

``` c
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j4
cd ../ports/stm32/boards
```

Copy the `WeAct_F411CE` in the current folder to the appropriate file on your Linux system

``` c
Copy WeAct_F411CE to micropython/ports/stm32/boards
```

Then

``` c
cd YourPath/micropython/ports/stm32/

make BOARD=WeAct_F411CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j
# or
make BOARD=WeAct_F411CE -j
```

Note: CROSS_COMPILE Change to your own compiler path

## mpconfigboard.h

``` c
/* BOARD Ver 2.0 set 1 ，other set 0 ex.V1.3,V2.1 V3.0 */
#define VERSION_V20 (1)

/* Use the built-in flash to change to 1 , use the external flash to change to 0 */
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
