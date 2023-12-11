# HAL库示例程序

* [English Version](./README.md)

1. `XXXX_ADC`           为ADC使用例程 测量矩形波占空比、频率
2. `XXXX_test_xx`       为出厂测试例程 呼吸灯、USBCDC功能、RTC功能
3. `XXXX_USBDisk+FATFS` 为U盘和FATFS文件系统例程 需要外接FLASH
4. `STM32F411_test_CubeIDE` CubeIDE 例程

## 重要说明

8Mhz晶振的板子，打开工程前先运行工程目录里的`CrystalsChangeTo8Mhz.bat`,脚本会自动修改工程的晶振配置,由25Mhz改为8Mhz