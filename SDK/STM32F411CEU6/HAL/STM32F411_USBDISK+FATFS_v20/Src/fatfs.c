/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include "fatfs.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

/* USER CODE BEGIN Variables */
#include "w25qxx.h"
#include <stdio.h>
#include <string.h>
#include "rtc.h"
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;
uint8_t workbuf[4096];
/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the USER driver ###########################*/
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */
	char wtext[100];
  uint32_t byteswritten;                     /* File write/read counts */
	if(retUSER == FR_OK)
	{
		retUSER = f_mount(&USERFatFS,(TCHAR const*)USERPath,1) ;
		if(retUSER != FR_OK)
		{
			retUSER = 2;
			f_mkfs((TCHAR const*)USERPath, 0, 0,workbuf,4096);		
		}
		else
		{
			/*
			FA_READ 指定读访问对象。可以从文件中读取数据。与FA_WRITE结合可以进行读写访问。
			FA_WRITE 指定写访问对象。可以向文件中写入数据。与FA_READ结合可以进行读写访问。
			FA_OPEN_EXISTING 打开文件。如果文件不存在，则打开失败。(默认)
			FA_OPEN_ALWAYS 如果文件存在，则打开；否则，创建一个新文件。
			FA_CREATE_NEW 创建一个新文件。如果文件已存在，则创建失败。
			FA_CREATE_ALWAYS 创建一个新文件。如果文件已存在，则它将被截断并覆盖。
			注意：当 _FS_READONLY == 1 时，模式标志 FA_WRITE, FA_CREATE_ALWAYS, FA_CREATE_NEW, FA_OPEN_ALWAYS 是无效的。
			*/
			if(f_open(&USERFile, "WeAct Core-Board 核心板.txt", FA_CREATE_NEW | FA_WRITE) == FR_OK)
			{
				sprintf(wtext,"W25QXX\r\nFlash ID: 0X%X\r\nFlash Size: %d MB\r\n\r\n",W25Qx_Para.FLASH_ID,W25Qx_Para.FLASH_SIZE / 1024 / 1024);
				f_write(&USERFile, wtext, strlen(wtext), (void *)&byteswritten);
				
				sprintf(wtext,"This is STM32 working with FatFs\r\nSTM32F411 Core Board Design By WeAct\r\nBoard Version: 2.0\r\n");
				f_write(&USERFile, wtext, strlen(wtext), (void *)&byteswritten);
				
				f_close(&USERFile);
			}
		}
	}   	
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
	uint16_t year;
	uint8_t month;
	uint8_t date;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;	
  /* 必须同时获取时间和日期 不然会导致下次RTC不能读取 */
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);	
	
	year = sdatestructureget.Year + 2000;
	month = sdatestructureget.Month;
	date = sdatestructureget.Date;
	hours = stimestructureget.Hours;
	minutes = stimestructureget.Minutes;
	seconds = stimestructureget.Seconds;
	
	return ((year - 1980) << 25) /* Year */
	| (month << 21) /* Month */
	| (date << 16) /* Day */
	| (hours << 11) /* Hour */
	| (minutes << 5) /* Min */
	| (seconds) /* Sec */
	;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
