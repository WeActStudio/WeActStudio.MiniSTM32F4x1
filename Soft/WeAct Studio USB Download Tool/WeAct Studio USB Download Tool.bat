@echo off
title WeAct Studio USB Download Tool
cls
echo.
echo ----- Hold down the BOOT0 key and Connect to the computer -----
echo ----- 按住BOOT0键，然后连接电脑 -----
echo ----- 设备管理器会出现DFU设备 -----
echo ----- Input Firmware Name -----
echo ----- 输入需要烧录固件的文件名 -----
echo ----- Example: firmware.bin -----
echo ----- Download Addr: 0x08000000 -----
echo.
set /p Name=Firmware Name:
.\STM32_Programmer_CLI\STM32_Programmer_CLI.exe --connect port=USB1 --download %Name% 0x08000000 --start
