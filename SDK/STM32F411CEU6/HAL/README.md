# HAL sample program

* [中文版本](./README-zh.md)

1. `xxxx_ADC`               is used to measure duty cycle and frequency of rectangular wave for ADC
2. `xxxx_test`              is the factory test routine breathing lamp, USBCDC function, RTC function
3. `XXXX_USBDisk+fatfs`     for usb drives and FATFS file system routines require external FLASH
4. `STM32F411_test_CubeIDE` CubeIDE sample

## Important note

8Mhz crystal oscillator circuit board，Run the `CrystalsChangeTo8Mhz.bat` in the project directory before opening the project, and the script will automatically modify the crystal configuration of the project from 25Mhz to 8Mhz