# WeAct Studio Download Tool

* [English Version](./README.md)

## 本下载工具可用于micropython固件的烧录，或程序的下载，非常方便

> 实现USB一键下载固件

1. 按住BOOT0键，然后连接电脑
2. 设备管理器会出现DFU设备
3. 如果下载提示没有驱动，可以进入DFU_Driver文件夹，双击`STM32Bootloader.bat`进行安装
4. 双击`WeAct Studio USB Download Tool.bat`,输入目标固件名，回车即可开始下载

> 实现串口一键下载固件

1. 进入ISP模式
2. 使用串口连接单片机
3. 双击`WeAct Studio UART Download Tool.bat`,输入目标固件名，串口号，回车即可开始下载

## 如何进入ISP模式

* 方法1：上电状态下，按住BOOT0键和复位键，然后松开复位键，0.5秒后松开BOOT0键
* 方法2：掉电状态下，按住BOOT0键，上电后0.5S松开BOOT0
* DFU模式：使用数据线连接电脑即可
* 串口模式：使用USB转串口连接核心板的PA9,PA10即可
* 软件： STM32CubeProg。

