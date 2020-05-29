::echo off

@echo off
setlocal
for /f "tokens=4-5 delims=. " %%i in ('ver') do set VERSION=%%i.%%j

if "%version%" == "6.1" (
if exist "%windir%\sysnative\pnputil.exe" (
    start "STM32 USB DFU DRIVER" %windir%\sysnative\pnputil.exe -i -a  %0\..\DriverNotSigned\DFU_in_HS_Mode.inf
) else (
    start "STM32 USB DFU DRIVER" pnputil -i -a  %0\..\DriverNotSigned\DFU_in_HS_Mode.inf
)
) else (
if exist "%windir%\sysnative\pnputil.exe" (
    start "STM32 USB DFU DRIVER" %windir%\sysnative\pnputil.exe -i -a  %0\..\Driver\STM32Bootloader.inf
) else (
    start "STM32 USB DFU DRIVER" pnputil -i -a  %0\..\Driver\STM32Bootloader.inf
)
)
endlocal