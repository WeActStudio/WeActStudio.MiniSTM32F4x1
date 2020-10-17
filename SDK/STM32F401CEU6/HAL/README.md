# HAL sample program

* [中文版本](./README-zh.md)

* `01-GPIO`' GPIO test. Press KEY, LED flash. If KEY is not pressed, LED flash slowly
* `02-ADC_RTC_test` ADC and RTC test, using USB CDC virtual serial port to display dataE
* `03-CDC_Standalone` The USB virtual serial routine is as follows. PA9 and PA10 are all serial ports
* `04-USBDisk+FATFS` Emulates usb and FATFS file system routines, requiring external FLASH
* `05-SPIFlash_Erase`  SPI Flash Erase routines, requiring external FLASH
* `06-F401_ST7735` The ST7735 LCD display routine, requires an external screen

## Important note

8Mhz crystal oscillator circuit board，Run the `CrystalsChangeTo8Mhz.bat` in the project directory before opening the project, and the script will automatically modify the crystal configuration of the project from 25Mhz to 8Mhz

If there is no `WeAct` and `version number` on the back of the board, the chip batch is `537` or old, the stitches and board are packaged in one bag, `the board screen printing is wrong`(`3V3` is going to be labeled `V3V`), it is definitely pirated.Please comment on issues or let us know by email (WeAct_TC@163.com).
