# WeAct HID bootloader

* [English Version](./README.md)

本软件参考了以下源码，但不是修改以下源码而来
STM32_HID_bootloader  <https://github.com/Serasidis/STM32_HID_Bootloader.git>

> Bootloader/ --- Bootloader固件 默认APP转跳地址: 0x8004000

> APP/ --- APP 工程设置方法及测试固件

> WeAct_HID_Flash-CLI.exe --- Win CLI命令行烧录

> WeAct_HID_Flash-CLI --- Linux CLI命令行烧录

> WeAct_HID_Flash_NETFramework4+ V10 FluentWPF xxxxx.exe --- APP烧录软件/上位机

|ROM Addr|
|:--:|
|0x8000000 Bootloader|
|16KB |
|0x8004000 APP|  
|..... |
|END|

``` bash
 if (RTC_BKP_DR19 !=0x1234 && <KEY> != 按下) ，转跳APP地址(0x8004000)运行
 else 进入Bootloader等待命令
 ```

 APP：RTC_BKP_DR19 写入0x1234，HAL_NVIC_SystemReset()，自动进入Bootloader

STM32F401CC、STM32F411CE 核心板均可使用，实现类似 51 单片机下载，但无需串口，只需一根数据线，
和修改Keil工程两个地方（详情见视频）即可实现。速度比串口下载更快且更方便。

核心板 USB连接电脑出现 HID设备，则已烧录bootloader，可无需串口、STLink、J-link直接下载。
核心板 USB连接电脑没有出现 HID设备，则没有Bootloader，请烧录bootloader至0x8000000

APP 程序可用调试器调试仿真，无影响。

## 软件使用步骤

1. 将核心板用数据线连接电脑，出现WeAct HID设备
2. 按住KEY键，重新上电或复位进入Bootloader
3. 软件选择固件，点击\<下载固件\>即可完成下载
4. 所选固件会随KEIL重新编译而更新，无需重新选择

## 进入Bootloader 方法

1. 按住\<KEY\>键，重新上电或复位，C13 LED 闪烁即可松开
2. APP进入Bootloader 参考stm32f401_test_APP 0x8004000.zip 工程

## 在Bootloader 中

1. \<KEY\>键 单击 为 C13 LED 亮灭
2. SW 调试口开放，可以用调试器烧写，无需进入DFU模式
3. 长按\<KEY\>键，C13 LED 闪烁即可松开，为进入内置自举程序，ISP模式

## 退出Bootloader 方法

1. 复位MCU， 复位键/上位机点击\<MCU 复位\>
2. 长按\<KEY\>键，C13 LED 闪烁即可松开

## 注意事项

1. 首次烧录Bootloader，MCU不会往下运行，同时\<C13 LED>200MS闪烁，只需再次复位MCU即可
2. Bootloader 以及 APP烧录软件 源码均不开放

## HID bootloader V1.1

1. Bugs 修复
2. 修改\<KEY\>键长按功能，长按\<KEY>键，C13 LED 闪烁即可松开，为进入内置自举程序，ISP模式
3. 减小bootloader固件大小
4. 移除\<KEY\>键 双击功能

## HID bootloader V1.2

1. 修复systick没有关闭的问题
