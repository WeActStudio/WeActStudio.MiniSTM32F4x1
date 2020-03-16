# Release Notes 版本说明

![](/images/STM32F4x1-V30_3D.jpg "3D View")

## V3.0
> Button ` KEY ` series 330Ω resistance, prevent user settings ` KEY ` pin for the output mode after the button press cause short circuit, and the appearance remains unchanged.Process improvement, use Lead-Free process.

> Solve the problem that the USB C line with `e-marker` chip cannot provide power, and add `D4` diode (`B5819WS SL`) to prevent USB power surge, and the appearance remains unchanged

> 按键`KEY`串联330Ω电阻，防止用户设置`KEY`引脚为输出后按键按下造成短路，外观不变。工艺改善，使用无铅工艺,更环保

> 解决带e-marker芯片的USB C数据线不能供电的问题，同时增加D4二极管（型号：`B5819WS SL`），防止USB端口电涌，外观不变。

## V2.1
> SDIO is not commonly used, restore Flash pin: Flash MISO pin changed from PB4 to PA6,The look is consistent with V2.0.

> SDIO不常用，恢复Flash引脚: Flash MISO脚由PB4改为PA6，外观与V2.0版本一致

## V2.0
> The thickness of the board was changed to 1.6mm, the Flash MISO foot was changed from PA6 to PB4, and the keys were changed to large buttons.

> This button is a decompression device, MISO foot change, F401 users have no impact, default brush into HID Bootloader, similar to 51 MCU download.

> 板厚改为1.6mm，Flash MISO脚由PA6改为PB4，同时按键更换为大颗按键

> 此按键乃减压神器，MISO脚变更，F401用户无影响，默认刷入HID Bootloader，实现类似51单片机下载

## V1.3
> Add user KEY (PA0)

> 增加用户按键 KEY (PA0)

## V1.2 
### Production has be discontinued on 2019.10.01 已于2019.10.01停产
> The BOOT setting is changed from jumper to keypad to reduce installation hassle.

> Press BOOT0 and NRST, release NRST, release BOOT0 after 0.5s, then enter serial port for download, DFU download, provide STM32CubeProgrammer burning software of ST official multi-in-one.

> BOOT设置由跳线改为按键，减少安装的麻烦

> 按下BOOT0和NRST，松开NRST，0.5S后松开BOOT0，即可进入串口下载，DFU下载，提供ST官方多合一STM32CubeProgrammer烧录软件。

![STM32F4X1 V2.0+](/images/STM32F4x1-V20+BoardShape.png "Board Shape STM32F4X1 V2.0+")