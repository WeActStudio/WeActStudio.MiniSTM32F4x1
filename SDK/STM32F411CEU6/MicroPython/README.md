# MicroPython firmware brush in instructions

* [中文版本](./README-zh.md)

## WeAct Studio STM32F411CEU6

> `firmware_xxxxxxx_stm32f411_xxmhz_vxx_v1.22` The latest  
8MHz crystal version Select the file ending at 8mhz.

Restore factory Settings: Hold down the KEY and click the Reset KEY. The blue LED flashes three times. Release the KEY to restore factory Settings

4MB SPI Flash:

* Hardware version: Version numberV2.1，V2.2，V3.0 Corresponding firmware is：`firmware_4m_flash_stm32f411_v21+&&V13_v1.xx-xxx.hex`
* Hardware version: Version number：`firmware_4m_flash_stm32f411_v20_v1.12-35.hex`

8MB SPI Flash:

* Hardware version: Version numberV2.1，V2.2，V3.0 Corresponding firmware is: `firmware_8m_flash_stm32f411_v21+&&V13_v1.xx-xxx.hex`

Internal Rom Flash:

* `firmware_internal_rom_stm32f411_v1.xx-xxx.hex`

Special problems need to be erased SPI Flash:
> Brush into the firmware to erase the exteranl SPI Flash，`LED` 50ms Flash indicates Flash failure, long light indicates wipe in progress, 0.5s Flash indicates successful wipe, and 0.5s slow Flash erase fails

* SPIFlash_Erase_Firmware.hex

Learn more, please visit : <https://github.com/WeActTC/WeAct_F411CE.git>
> Micropython Chinese tutorial：<https://www.weact-tc.cn/2020/01/01/micropython/>

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
