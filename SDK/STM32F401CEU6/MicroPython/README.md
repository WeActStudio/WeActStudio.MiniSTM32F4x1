# Important note

If there is no `WeAct` and `version number` on the back of the board, the chip batch is `537` or old, the stitches and board are packaged in one bag, `the board screen printing is wrong`(`3V3` is going to be labeled `V3V`), it is definitely pirated.Please comment on issues if you can, or let us know by email (Zhuab1997@outlook.com).

# Micropython
## WeAct_F401CE
> firmware_xxxxxxx_stm32f401ce_v30_v1.12-540 The Latest 最新

> 使用教程：https://www.weact-tc.cn/2020/01/01/micropython/

4MB SPI Flash:
* firmware_4m_flash_stm32f401ce_v30_v1.12-540.hex


8MB SPI Flash:
* firmware_8m_flash_stm32f401ce_v30_v1.12-540.hex

内置Flash Internal ROM:
* firmware_internal_rom_stm32f401ce_v30_v1.12-540.hex

遇到特殊问题需要擦除SPI Flash：
> 刷入该固件可以擦除外挂的SPI Flash，`LED` 50ms快闪为识别Flash失败，长亮为擦除进行中，0.5s快闪为擦除成功，0.5s慢闪擦除失败
* SPIFlash_Erase_Firmware.hex

## How to build 如何编译 ubuntu/Win10内置linux

```
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j
cd ../ports/stm32/boards
cp YourPath/WeAct_F401CE to micropython/ports/stm32/boards
cd YourPath/micropython/ports/stm32/
# CROSS_COMPILE 修改为自己的编译器路径
# CROSS_COMPILE Change to your own compiler path
make BOARD=WeAct_F401CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j
# or 或者
make BOARD=WeAct_F401CE -j
```
## mpconfigboard.h
```
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
#define MICROPY_HW_SPIFLASH_MISO    (pin_A6)
#define MICROPY_HW_SPIFLASH_MOSI    (pin_A7)
```