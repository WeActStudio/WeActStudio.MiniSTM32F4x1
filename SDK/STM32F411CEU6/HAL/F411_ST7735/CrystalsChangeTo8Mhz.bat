@echo off
title WeAct Studio Project Crystals Change To 8MHz Tool
setlocal EnableDelayedExpansion
cls

echo.
echo WeAct Studio Project 25Mhz Crystals Change To 8MHz
echo.

call :Search "main.c"
if not %return%=="" (
	call :Replace %return% "RCC_OscInitStruct.PLL.PLLM = 12;" "RCC_OscInitStruct.PLL.PLLM = 4;"
	call :Replace %return% "RCC_OscInitStruct.PLL.PLLN = 96;" "RCC_OscInitStruct.PLL.PLLN = 100;"
)

call :Search "stm32f4xx_hal_conf.h"
if not %return%=="" (
	call :Replace %return% "#define HSE_VALUE    ((uint32_t)25000000U)" "#define HSE_VALUE    ((uint32_t)8000000U)"
)

call :Search "*.ioc"
if not %return%=="" (
	call :Replace %return% "RCC.HSE_VALUE=25000000" "RCC.HSE_VALUE=8000000"
	call :Replace %return% "RCC.PLLM=12" "RCC.PLLM=4"
	call :Replace %return% "RCC.PLLN=96" "RCC.PLLN=100"
)

echo Replace Completed.
echo Thank You
echo.

pause
exit

REM Replace "File" "Old" "New"
:Replace
(echo Set FSO=Wscript.CreateObject("Scripting.FileSystemObject"^)
echo S=ReadFile("%~1","utf-8"^)
echo S=replace(S,"%~2", "%~3"^)
echo Call WriteToFile("%~1",S,"utf-8"^)
echo Wscript.Quit
echo Function ReadFile(FileUrl, CharSet^)
echo     Dim Str
echo     Set stm = CreateObject("Adodb.Stream"^)
echo     stm.Type = 2
echo     stm.mode = 3
echo     stm.charset = CharSet
echo     stm.Open
echo     stm.loadfromfile FileUrl
echo     Str = stm.readtext
echo     stm.Close
echo     Set stm = Nothing
echo     ReadFile = Str
echo End Function
echo Function WriteToFile (FileUrl, Str, CharSet^)
echo     Set stm = CreateObject("Adodb.Stream"^)
echo     stm.Type = 2
echo     stm.mode = 3
echo     stm.charset = CharSet
echo     stm.Open
echo     stm.WriteText Str
echo     stm.SaveToFile FileUrl, 2
echo     stm.flush
echo     stm.Close
echo     Set stm = Nothing
echo End Function)>Replace.vbs
Replace.vbs
del /f /q Replace.vbs
goto :eof

:Search
set return=""
for %%a in (.) do for /f "delims=" %%b in ('dir /a-d/b/s %%a\%~1') do ( 
    echo Find %%b 
	set return=%%b
	goto :eof
)
goto :eof
