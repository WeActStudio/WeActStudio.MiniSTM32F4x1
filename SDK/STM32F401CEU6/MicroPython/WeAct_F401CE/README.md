# WeAct STM32F401CE Core Board

## How to build 如何编译 ubuntu/Win10内置linux

```
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j
cd ../ports/stm32/boards
git clone https://github.com/WeActTC/WeAct_F411CE.git
cd ..
# CROSS_COMPILE 修改为自己的编译器路径
# CROSS_COMPILE Change to your own compiler path
make BOARD=WeAct_F401CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j4
# or 或者
make BOARD=WeAct_F401CE -j
```
## mpconfigboard.h
```
/* 使用内置flash改1 使用外置flash改0 */
/* Use the built-in flash to change to 1 
   use the external flash to change to 0 */
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
```