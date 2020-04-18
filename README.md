# STM32F4x1 MiniF4 / WeAct Studio 微行工作室 出品
> `STM32F401CCU6` / `STM32F411CEU6` Core Board

![](/images/STM32F4x1-V22-3D.jpg "STM32F411 Immersion Gold Board 3D View")

## Where to buy
You can search for "`STM32F411CEU6`"，"`STM32F401CCU6`","`STM32F411`","`STM32F401`" on [AliExpress](https://www.aliexpress.com/)

### 淘宝购买链接
1. [WeAct Studio官方店](https://shop118454188.taobao.com/index.htm?spm=2013.1.w5002-17867322799.2.212f5cb16nqwNP)
2. [育松电子（代售商家）](https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-14787471870.10.71616865kPY8bZ&id=596986293640)
3. 淘宝其他电子商家未做确认

### 淘宝出售翻版商家
1. [eixpsy旗舰店](https://detail.tmall.com/item.htm?spm=a230r.1.14.16.12f5a581svM8ak&id=611089230357&cm_id=140105335569ed55e27b&abbucket=8)
2. [深圳市海瑟威电子商行](https://item.taobao.com/item.htm?spm=a230r.1.14.38.12f5a581svM8ak&id=588648744621&ns=1&abbucket=8#detail)
3. [佳仕通数码专营店](https://detail.tmall.com/item.htm?spm=a230r.1.14.92.12f5a581svM8ak&id=611294799545&ns=1&abbucket=8)
4. 待更新

> If it doesn't have a logo and version number it isn't made by `WeAct`, probably `Pirated&Fake`.

> The two boards are identical, other than the colour of the contacts.  F401 has silver contacts, while F411 has gold contacts.

> 收到的板子没有Logo `WeAct` && `版本号` 的均不是我们生产，如有质量问题和技术问题请自行寻找卖家解决

> STM32F401 V1.2 `End Of Life` , STM32F411 V1.3 `End Of Life` Since 2019.11

> STM32F401 V1.2,STM32F411 V1.3 已于2019.11停产

![](/images/STM32F4x1C_Logo&Version.png "Logo&Version Logo和版本号说明")

## Pinout Diagram 引脚分配图
> Thanks `Richard·Balint` !! 

Using Pinout Diagram, Write MicroPython and Arduino code will be easier

![](/images/STM32F4x1_PinoutDiagram_RichardBalint.png "/General document/STM32F4x1 v2.0+ Pin Layout")

## MicroPython
* Version: V1.12-35
> STM32F401CCU6 `Supported`, STM32F411CEU6 `Supported`.

### Board Definition
STM32F411CE: `https://github.com/WeActTC/WeAct_F411CE-MicroPython.git`

STM32F401CC: `/STM32F401CCU6-Black-Board/SDK/micropython/WeAct_F401CC`

> 中文使用部分教程：[点击](https://www.weact-tc.cn/2020/01/01/micropython/)

> 中文使用部分教程.pdf文件：`/General document/MicroPython部分使用教程 _WeAct工作室.pdf`

## HID Flash
> 中文STM32下载烧录部分教程：[点击](https://www.weact-tc.cn/2019/11/30/STM32Download/)

> 中文STM32下载烧录部分教程.pdf文件：`/General document/STM32部分下载烧录问题汇总 _WeAct工作室.pdf`

> supported in `English` and `Chinese`
### Enter the HID bootloader method:
1. Hold down the <KEY key>, power on or reset again, and the C13 LED will blink to release
2. APP enters the bootloader reference stm32f401_test_APP 0x8004000.zip project
3. [More instructions](/Soft/WeAct_HID_FW_Bootloader/README.md)

### 进入HID Bootloader 方法：
1. 按住\<KEY\>键，重新上电或复位，C13 LED 闪烁即可松开
2. APP进入Bootloader 参考stm32f401_test_APP 0x8004000.zip 工程
3. [更多使用说明](Soft/WeAct_HID_FW_Bootloader/README_zh-CN.md)

![WeAct HID Flash](https://WeActTC.github.io/images/STM32/HIDFlash2.png)

## 如何进入ISP模式
* 方法1：上电状态下，按住BOOT0键和复位键，然后松开复位键，0.5秒后松开BOOT0键
* 方法2：掉电状态下，按住BOOT0键，上电后0.5S松开BOOT0
* DFU模式：使用数据线连接电脑即可，如出现无法识别问题，可以适当加热芯片(25°C)，再重新进入ISP模式
* 串口模式：使用USB转串口连接核心板的PA9,PA10即可
* 软件： STM32CubeProg。

## How to enter ISP mode
* Method 1: When the power is on, press the BOOT0 key and the reset key, then release the reset key, and release the BOOT0 key after 0.5 seconds
* Method 2: When the power is off, hold down the BOOT0 key, and release the BOOT0 at 0.5s after the power is on
* DFU Mode: Use the data line to connect to the computer. If there is an unrecognized problem, you can heat the chip appropriately (25°C) and then re-enter the ISP mode
* Serial Port Mode: Connect PA9 and PA10 of core board with USB serial port
* Soft: STM32CubeProg。

## Chip information 芯片信息
![STM32F411 Info](/images/DeviceMarkingUFQFPN48.png)

| STM32F411 |STM32F401|
| :--: | :--: |
|![STM32F411 Info](/images/stm32f411_dinfo.png)|![STM32F4X1 V2.0](/images/stm32f401_dinfo.png)|
|Date Code|Date Code|
|947&002 (2020.03)|609&608|
|946&947 (2020.01)|723 (2020.01)|
|19+ (2019)|16+ (2019)|

### All chips are functional and original 所有芯片原装正品，测试正常

## Board Shape 外形
![STM32F4X1 V2.0+](/images/STM32F4x1-V20+BoardShape.png "Board Shape")
