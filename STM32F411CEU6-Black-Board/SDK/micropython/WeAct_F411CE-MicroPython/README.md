# WeAct STM32F411 Core Board

## How to build 如何编译 ubuntu/Win10内置linux

```
git clone https://github.com/micropython/micropython.git
cd micropython
git submodule update --init
cd mpy-cross
make -j4
cd ../ports/stm32/boards
git clone https://github.com/WeActTC/WeAct_F411CE.git
cd ..
# CROSS_COMPILE 修改为自己的编译器路径
# CROSS_COMPILE Change to your own compiler path
make BOARD=WeAct_F411CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j4
# or 或者
make BOARD=WeAct_F411CE -j4
```
## mpconfigboard.h
```
/* BOARD Ver 2.0 set 1 ，other set 0 ex.V1.3,V2.1 */
#define VERSION_V20 (1)

/* 使用内置flash改1 使用外置flash改0 */
/* Use the built-in flash to change to 1 
   use the external flash to change to 0 */
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
```

![STM32F4X1 V2.0](https://github.com/WeActTC/Product-Images/raw/master/STM32F4x1C/STM32F4x1C_V20+.png "STM32F4X1 V2.0+")
## Where to buy
You can Buy on [AliExpress](https://www.aliexpress.com/item/4000069263843.html?spm=a2g0o.productlist.0.0.72081e00lBo5VI&algo_pvid=7e5612f1-4014-42a3-8d10-145e22ec794d&algo_expid=7e5612f1-4014-42a3-8d10-145e22ec794d-1&btsid=fae3afec-bf75-42f5-9fad-a780fbe720d7&ws_ab_test=searchweb0_0,searchweb201602_5,searchweb201603_53) or search for "STM32F411CEU6" on AliExpress 
## Stores known to sell pirated copies:
[Global-Purchase Store](https://www.aliexpress.com/item/4000103610226.html?spm=a2g0o.productlist.0.0.72081e00lBo5VI&algo_pvid=7e5612f1-4014-42a3-8d10-145e22ec794d&algo_expid=7e5612f1-4014-42a3-8d10-145e22ec794d-0&btsid=fae3afec-bf75-42f5-9fad-a780fbe720d7&ws_ab_test=searchweb0_0,searchweb201602_5,searchweb201603_53)