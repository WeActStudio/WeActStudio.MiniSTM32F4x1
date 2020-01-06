
WeAct HID bootloader
This software refers to the following source code, but it is not modified from the following source code
STM32_HID_bootloader https://github.com/Serasidis/STM32_HID_Bootloader.git

Bootloader/  ------------------------  Bootloader firmware Default APP forwarding address: 0x8004000
APP/APP   ---------------------------  Project setting method and test firmware
WeAct_HID_Flash-CLI.exe  ----------- Win CLI command line flashing
WeAct_HID_Flash-CLI  --------------- Linux CLI command line flashing
WeAct_HID_Flash_NETFramework4 + V10 FluentWPF xxxxx.exe  ------  APP burning software / host computer

________________
|| 0x8000000  ||
||  Bootloader ||        
||      16KB       ||        
|| 0x8004000  ||
||      APP        ||     
||       .....         ||
||____END__ __||

Both STM32F401CC and STM32F411CE core boards can be used
If the HID device appears when the core board is connected to the computer via USB, the bootloader has been programmed and can be downloaded directly without serial port, STLink, or J-link.
Core board There is no HID device when USB is connected to the computer, there is no bootloader,.Please flash the bootloader to 0x8000000

The APP program can be debugged by the debugger without any impact.

Enter the bootloader method:
(1) Hold down the <KEY key>, power on or reset again, and the C13 LED will blink to release
(2) APP enters the bootloader reference stm32f401_test_APP 0x8004000.zip project
(3) In the bootloader, click / double-click the <KEY key> to turn on or off the C13 LED.

In the bootloader:
(1) <KEY key> Click / double-click to turn on or off the C13 LED
(2) The SW debug port is open and can be programmed by the debugger without entering DFU mode

Exit the bootloader method:
(1) Reset MCU, reset key / upper computer click <MCU reset>
(2) Long press the <KEY key>, the C13 LED flashes and you can release it

Note: Bootloader and APP programming software are not open source