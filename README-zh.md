# STM32F4x1 MiniF4 / WeAct Studio 微行工作室 出品

* [English Version](./README.md)

> `STM32F401CEU6` / `STM32F411CEU6` 核心板

!["STM32F411 Immersion Gold Board 3D View"](./images/STM32F4x1-V22-3D.jpg )

## 购买链接

1. 淘宝 [WeAct Studio official store](https://shop118454188.taobao.com/index.htm?spm=2013.1.w5002-17867322799.2.212f5cb16nqwNP)
2. AliExpress [WeAct Studio Official Store](https://weactstudio.aliexpress.com/store/1101545918)

> 收到的板子没有Logo `WeAct Studio` && `版本号` 的均不是我们生产，如有质量问题和技术问题请自行寻找卖家解决，最好举报他们，商品评论他们，以免其他人上当受骗！！！

!["Logo和版本号说明"](./images/STM32F4x1C_Logo&Version.png)

收到的板子没有Logo `WeAct Studio` && `版本号` 的均不是我们生产。

## 我们生产的板子

* 411采用沉金无铅工艺，401采用无铅工艺，排针为镀金排针，所有材料符合ROHS标准，有铅危害身体，而盗版为了利益都是用的有铅

* 均采用最新批次芯片，给客户最好的产品体验

* 25MHZ高速晶振 & 32.768Khz 低速晶振均采用高质量金属外壳晶振，起振效果更好

* 预留Flash焊盘，满足大数据存储和micropython的使用，提供USBDisk&&FATFFS例程

* 支持MicroPython编程，提供可用的MicroPython固件

* 支持Arduino编程，详情见[Github](https://github.com/stm32duino/Arduino_Core_STM32)

* 版本为V3.1，有3个按键，复位键，BOOT0键，用户按键

!["芯片批次介绍"](./images/STM32F4x1_chip_display.png)

> 我们承诺始终采用最好的生产原料，使用最新的芯片，使用户得到最好的用户体验，提高开发效率

## 我们生产的板子的包装

![""](./images/STM32F4x1_pack.png)

## 我们生产的板子芯片参数对比

||STM32F401CCU6|STM32F401CEU6|STM32F411CEU6|
|:--:|:--:|:--:|:--:|
|Freq.|84Mhz|84Mhz|100Mhz|
|ROM|256KB|512KB|512KB|
|RAM|64KB|96KB|128KB|
|出售情况|**停售**|**停售**|在售|

## 引脚分配图

> 感谢 `Richard·Balint` !! 

使用引脚分配图, 使用MicroPython和Arduino会更简单！

![ "/General document/STM32F4x1 v2.0+ Pin Layout"](./images/STM32F4x1_PinoutDiagram_RichardBalint.png)

## MicroPython

* 版本: V1.12-35

> STM32F401CEU6 `已支持`  
STM32F411CEU6 `已支持`  

### 板子定义信息

STM32F401CE: `/SDK/STM32F401CEU6/MicroPython/WeAct_F411CE`

STM32F411CE: `/SDK/STM32F411CEU6/MicroPython/WeAct_F411CE`

> 中文使用部分教程：[点击](https://www.weact-tc.cn/2020/01/01/micropython/)

> 中文使用部分教程.pdf文件：`/General document/MicroPython部分使用教程 _WeAct工作室.pdf`

## HID Flash

> 中文STM32下载烧录部分教程：[点击](https://www.weact-tc.cn/2019/11/30/STM32Download/)

> 中文STM32下载烧录部分教程.pdf文件：`/General document/STM32部分下载烧录问题汇总 _WeAct工作室.pdf`

> 支持`中文`和`英文`

### 进入HID Bootloader 方法

1. 按住\<KEY\>键，重新上电或复位，C13 LED 闪烁即可松开
2. APP进入Bootloader 参考stm32f401_test_APP 0x8004000.zip 工程
3. [更多使用说明](./Soft/WeAct_HID_FW_Bootloader/README_zh-CN.md)

![WeAct HID Flash](images/HIDFlash2.png)

## 如何进入ISP模式

* 方法1：上电状态下，按住BOOT0键和复位键，然后松开复位键，0.5秒后松开BOOT0键
* 方法2：掉电状态下，按住BOOT0键，上电后0.5S松开BOOT0
* DFU模式：使用数据线连接电脑即可，如出现无法识别问题，可以适当加热芯片(25°C)，再重新进入ISP模式
* 串口模式：使用USB转串口连接核心板的PA9,PA10即可
* 软件： STM32CubeProg。

## 芯片信息

|MCU|Freq.|RAM|ROM|
|:--:|:--:|:--:|:--:|
|STM32F401CC|84Mhz|64KB|256KB|
|STM32F401CE|84Mhz|96KB|512KB|
|STM32F411CE|100Mhz|128KB|512KB|

![STM32F411 Info](./images/DeviceMarkingUFQFPN48.png)

| STM32F411CE |STM32F401CC|STM32F401CE|
| :--: | :--: | :--: |
|![STM32F411 Info](./images/stm32f411_dinfo.png)|![STM32F401CC Info](./images/stm32f401cc_dinfo.png)|![STM32F401CE Info](./images/stm32f401ce_dinfo.png)|
|生产日期|生产日期|生产日期|
|014 (2020.06)|**停产**|934&935 (2020.06)|
|947&002 (2020.03)|609&608|
|946&947 (2020.01)|723 (2020.01)|
|19+ (2019)|16+ (2019)|

### 所有芯片原装正品，测试正常

## 外形

![STM32F4X1 V2.0+](./images/STM32F4x1-V20+BoardShape.png "Board Shape")

