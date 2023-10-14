# WeAct Studio Download Tool

* [中文版本](./README-zh.md)

> USB Download

1. Hold down the BOOT0 key and connect to the computer

2. DFU devices will appear in the device manager

3. If there is no driver, you can enter the DFU_Driver folder and double-click `STM32Bootloader.Bat` to install

4. Double-click `WeAct Studio USB Download Tool. Bat`, enter the target firmware name and press enter to start downloading

> UART Download

1. Enter ISP mode

2. Use serial port to connect MCU

3. Double-click `WeAct Studio UART Download Tool.bat`, enter the target firmware name and serial port number, press `Enter` to start downloading

## How to enter ISP mode

* Method 1: When the power is on, press the BOOT0 key and the reset key, then release the reset key, and release the BOOT0 key after 0.5 seconds
* Method 2: When the power is off, hold down the BOOT0 key, and release the BOOT0 at 0.5s after the power is on
* DFU Mode: Use the data line to connect to the computer.
* Serial Port Mode: Connect PA9 and PA10 of core board with USB serial port
* Soft: STM32CubeProg。
