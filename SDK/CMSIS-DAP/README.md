# CMSIS-DAP Firmware

* [中文版本](./README-zh.md)

This repository contains source and compiled binaries which allow the WeAct Studio STM32F4x1 MiniF4 boards (stm32f401ccu6 stm32f401ceu6 stm32f411ceu6) to act as ARM SWD Debug Probes.

The code is based on ARM's official DAPLink source code: https://github.com/ARMmbed/DAPLink

After a MiniF4 has been programmed with this firmware, it will become a CMSIS-DAP compatible debug probe, which can be used to program and debug other ARM MCUs and MPUs compatible with the ARM SWD debug protocol (e.g. another MiniF4 board).

|Our board|Target board|
|:--:|:--:|
|3V3|3V3¹|
|SWDIO|SWDIO²|
|SWCLK|SWCLK²|
|GND|GND|
|B0|nRST³|

¹Only connect if the target board does not provide its own power.  Do not exceed the capacity of the MiniF4 voltage regulator.  
²The target board must be capable of 3.3v I/O, or otherwise suitable high-speed level shifters must be used.  
³Only necessary if the debug scenario requires the debug probe board to reset the target board. "nRST" is labelled "R" on the MiniF4 silk screen.  

## Important note

Please help us and yourselves by buying a reliable defect-free product made to high standards with a genuine ST Micro STM32F4x1 MCU, by buying from our official stores.

Buying a genine product helps us to continue to develop software like this, and interesting new hardware designs.

WeAct Studio takes pride in producing high quality hardware. The pirates who steal others designs, are also be happy to steal from you by selling you badly manufactured, unreliable boards, made with poor quality components, with no support.

Pirated boards may be a little cheaper, but the savings are small, and you might waste a lot of time debugging an unreliable or counterfiet, or illegally obtained QC-Failed part!

"Cheap is expensive" - Dutch proverb.

## Programming the firmware (without additional hardware):

The following commands illustrate programming the provided binary to an WeAct Studio STM32F4x1 using software which is available on Linux distributions which are based on Debian (e.g. Ubuntu, Mint etc.), the built-in ROM bootloader of the STM32F4xx MCUs, and a USB-C cable.


Install necessary tools:

    apt install unzip binutils usbutils dfu-util

Unzip the downloaded software from https://github.com/WeActTC/MiniSTM32F4x1/blob/master/SDK/CMSIS-DAP/CMSIS-DAP_WeActStudio.zip

    mkdir WeActStudio-stm32f4-DAP && cd WeActStudio-stm32f4-DAP && unzip ~/Downloads/CMSIS-DAP_WeActStudio.zip && cd Objects

Translate the Intel Hex format firmware to a binary file:

    objcopy --input-target=ihex --output-target=binary CMSIS-DAP_WeActStudio.hex CMSIS-DAP_WeActStudio.bin

At this time hold down the "BOOT0" button on the MiniF4 and plug the USB cable into the MiniF4.  After the red "PWR" led turns on, release the "BOOT0" button.

Verify that the STM32F4 has successfully been placed into DFU mode. In DFU mode the output of the `lsusb` command will include a line like this:

    Bus xxx Device yyy: ID 0483:df11 STMicroelectronics STM Device in DFU Mode

Program the binary with:

    dfu-util -a "@Internal Flash  /0x08000000/04*016Kg,01*064Kg,03*128Kg" -s 0x08000000 -D CMSIS-DAP_WeActStudio.bin

After dfu-util has indicated success, press and then release the "NRST" button on the MiniF4.

Verify that the STM32F4 now appears on the USB bus as an ARM Debug Probe.  The output of the `lsusb` command should include the following line:

    Bus xxx Device yyy: ID c251:f001 Keil Software, Inc. WeAct CMSIS-DAP
