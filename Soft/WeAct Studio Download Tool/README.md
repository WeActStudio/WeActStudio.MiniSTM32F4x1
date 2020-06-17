# WeAct Studio Download Tool

实现USB一键下载固件
1. 按住BOOT0键，然后连接电脑
2. 设备管理器会出现DFU设备
3. 如果没有驱动，可以进入DFU_Driver文件夹，双击`STM32Bootloader.bat`进行安装
4. 双击`WeAct Studio USB Download Tool.bat`,输入目标固件名，回车即可开始下载

实现串口一键下载固件
1. 进入ISP模式
2. 使用串口连接单片机
3. 双击`WeAct Studio UART Download Tool.bat`,输入目标固件名，串口号，回车即可开始下载

## 如何进入ISP模式 How to enter ISP mode
### 中文说明 
* 方法1：上电状态下，按住BOOT0键和复位键，然后松开复位键，0.5秒后松开BOOT0键
* 方法2：掉电状态下，按住BOOT0键，上电后0.5S松开BOOT0
* DFU模式：使用数据线连接电脑即可
* 串口模式：使用USB转串口连接核心板的PA9,PA10即可
* 软件： STM32CubeProg。
### English
* Method 1: When the power is on, press the BOOT0 key and the reset key, then release the reset key, and release the BOOT0 key after 0.5 seconds
* Method 2: When the power is off, hold down the BOOT0 key, and release the BOOT0 at 0.5s after the power is on
* DFU Mode: Use the data line to connect to the computer.
* Serial Port Mode: Connect PA9 and PA10 of core board with USB serial port
* Soft: STM32CubeProg。

## English
> USB Download

1. Hold down the BOOT0 key and connect to the computer

2. DFU devices will appear in the device manager

3. If there is no driver, you can enter the DFU_Driver folder and double-click `STM32Bootloader.Bat` to install

4. Double-click `WeAct Studio USB Download Tool. Bat`, enter the target firmware name and press enter to start downloading

> UART Download

1. Enter ISP mode

2. Use serial port to connect MCU

3. Double-click `WeAct Studio UART Download Tool.bat`, enter the target firmware name and serial port number, press `Enter` to start downloading