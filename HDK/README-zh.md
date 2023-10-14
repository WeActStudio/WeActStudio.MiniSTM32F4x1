# 版本说明

* [English Version](./README.md)

![](/images/STM32F4x1C_Logo&Version.png "STM32F401 3D View")

## V3.1

> 背面增加短路焊盘，焊接焊盘，USB C支持输出5V，支持`USB Host`

> 更换LDO为`ME6206A33XG`，方便维修

> 金属化Logo

> 尺寸不变，引脚定义不变

## V3.0

> 按键`KEY`串联330Ω电阻，防止用户设置`KEY`引脚为输出后按键按下造成短路，外观不变。工艺改善，使用无铅工艺,更环保

> 解决带e-marker芯片的USB C数据线不能供电的问题，同时增加D4二极管（型号：`B5819WS SL`），防止USB端口电涌，外观不变。

## V2.2

> 解决带e-marker芯片的USB C数据线不能供电的问题，同时增加D4二极管（型号：`B5819WS SL`），防止USB端口电涌，外观不变。

## V2.1

> SDIO不常用，恢复Flash引脚: Flash MISO脚由PB4改为PA6，外观与V2.0版本一致

## V2.0

> 板厚改为1.6mm，Flash MISO脚由PA6改为PB4，同时按键更换为大颗按键

> 此按键乃减压神器，MISO脚变更，F401用户无影响，默认刷入HID Bootloader，实现类似51单片机下载

## V1.3

> 增加用户按键 KEY (PA0)

## V1.2

### Production has be discontinued on 2019.10.01 已于2019.10.01停产

> BOOT设置由跳线改为按键，减少安装的麻烦

> 按下BOOT0和NRST，松开NRST，0.5S后松开BOOT0，即可进入串口下载，DFU下载，提供ST官方多合一STM32CubeProgrammer烧录软件。

![STM32F4x1 V3.0](/images/STM32F4x1_V30_BoardShape.png "Board Shape STM32F4x1 V3.0")
