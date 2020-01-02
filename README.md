# WeAct STM32F411 Core Board
## 如何使用
```
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j4
cd ../ports/stm32
# 修改为自己的编译器路径
make BOARD=WeAct_F411CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j4
```
## mpconfigboard.h
```
/* BOARD Ver 2.0+ set 1 ，other set 0 */
#define VERSION_V20 (1)

/* 使用内置flash改1 使用外置flash改0 */
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
```