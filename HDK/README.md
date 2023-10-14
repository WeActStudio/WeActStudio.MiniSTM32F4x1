# Release Notes

* [中文版本](./README-zh.md)

![STM32F401 3D View](/images/STM32F4x1C_Logo&Version.png)

## V3.1

> Bottom add short circuit pad, welding pad, `USB C` support output `5V`, support `USB Host`

> Change LDO to `ME6206A33XG` for easy maintenance

> Metallized Logo

> Size unchanged, pin definition unchanged

## V3.0

> Button ` KEY ` series 330Ω resistance, prevent user settings ` KEY ` pin for the output mode after the button press cause short circuit, and the appearance remains unchanged.Process improvement, use Lead-Free process.

> Solve the problem that the USB C line with `e-marker` chip cannot provide power, and add `D4` diode (`B5819WS SL`) to prevent USB power surge, and the appearance remains unchanged

## V2.2

> Solve the problem that the USB C line with `e-marker` chip cannot provide power, and add `D4` diode (`B5819WS SL`) to prevent USB power surge, and the appearance remains unchanged

## V2.1

> SDIO is not commonly used, restore Flash pin: Flash MISO pin changed from PB4 to PA6,The look is consistent with V2.0.

## V2.0

> The thickness of the board was changed to 1.6mm, the Flash MISO foot was changed from PA6 to PB4, and the keys were changed to large buttons.

> This button is a decompression device, MISO foot change, F401 users have no impact, default brush into HID Bootloader, similar to 51 MCU download.

## V1.3

> Add user KEY (PA0)

## V1.2

### Production has be discontinued on 2019.10.01

> The BOOT setting is changed from jumper to keypad to reduce installation hassle.

> Press BOOT0 and NRST, release NRST, release BOOT0 after 0.5s, then enter serial port for download, DFU download, provide STM32CubeProgrammer burning software of ST official multi-in-one.


![STM32F4x1 V3.0](/images/STM32F4x1_V30_BoardShape.png "Board Shape STM32F4x1 V3.0")
