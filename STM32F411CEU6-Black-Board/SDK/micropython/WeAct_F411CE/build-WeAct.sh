git submodule update --init
cd ../mpy-cross
make -j4
cd ../ports/stm32
# 修改为自己的编译器路径 板子型号区分 WeAct_F411CE （WeAct_F401CC 不可用）
make BOARD=WeAct_F411CE CROSS_COMPILE=/mnt/e/MCU/tools/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi- -j4

