/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "w25qxx.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// VirtualCOM 在main.h 中修改 将stm32虚拟成一个串口 
// USARTx_TX_PIN                    PA9
// USARTx_RX_PIN                    PA10

#if !VirtualCOM  // 虚拟串口
/* Buffers used for displaying Time and Date */
uint8_t aShow[100] = {0};
#endif
uint8_t CDCopen;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#if !VirtualCOM 
static void RTC_CalendarShow(uint8_t *show);
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t tick,tick1,tick2;
	uint16_t uhAdc[2];
	#if !VirtualCOM 
	static uint16_t w25qxxId;  // 静态变量 防止数据被篡改
	static uint8_t w25qxt;

	uint8_t w25qxSize[][6] = {
									  "ERROR!", // 没有flash或其他型号
									  "W25Q80",
									  "W25Q16",
									  "W25Q32",
									  "W25Q64",
									  };
	
	float Vrefint,TempSensor;
	#endif
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  
 /* 无 FLASH 注释代码 */
//	uint8_t testbuf;
//  W25Qx_Init();

//  W25Qx_Read_ID(&w25qxxId);		  
//  if(w25qxxId >= 0xEF13)
//		w25qxt = w25qxxId - 0xEF12;
//  else w25qxt = 0;
//  if(w25qxxId >= 0xEF13)
//  {
//	  /* 读写擦除测试 */ 
//	  W25Qx_Read(&testbuf,0,1);
//	  if(testbuf != 0x01)
//	  {
//		  W25Qx_Erase_Chip();
//		  testbuf = 0x01;
//		  W25Qx_Write(&testbuf,0,1);
//	  }
//  }
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)uhAdc,sizeof(uhAdc));
  tick2 = tick1 = tick = HAL_GetTick();
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* C13 呼吸灯测试 */
		static uint8_t pwmset;
		static uint16_t time;
		static uint8_t timeflag;
		static uint8_t timecount;
	  if((HAL_GetTick() - tick >= 1 ))
	  {
		   tick = HAL_GetTick();
			

			 /* 呼吸灯 */
			if(timeflag == 0)
			{
				time ++;
				if(time >= 1600) timeflag = 1;
			}
			else
			{
				time --;
				if(time == 0) timeflag = 0;
			}

			/* 占空比设置 */
			pwmset = time/80;

			/* 20ms 脉宽 */
			if(timecount > 20) timecount = 0;
			else timecount ++;

			if(timecount >= pwmset ) HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_SET);
			else HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_RESET);
	  }
	   /* USB RTC ADC测试 */
	 
	  if(HAL_GetTick() - tick1 >= 1000)
	  {
		  tick1 = HAL_GetTick();
		  #if !VirtualCOM // 虚拟串口
		  RTC_CalendarShow(aShow);
		  HAL_Delay(2-1);  // 2ms 等待USB发送完成
		  
		  Vrefint = (float)uhAdc[1] / 4096 * 3.3f;
		  TempSensor = (((float)uhAdc[0]*1200/(float)uhAdc[1]) - 760)/2.5f + 25; // V25 = 0.76V, Avg_Slope = 2.5mV/°C
		  
		  CDC_Transmit_FS(aShow,sprintf((char *)aShow,"VrefintAdc: %.4fV\r\nTempSensorAdc: %.2f°C\r\nFlashID:%#X %.*s\r\n\r\n",
																					Vrefint,TempSensor,w25qxxId,6,(char *)&w25qxSize[w25qxt]));
		  #endif
	  }
	  
	  /* USB CDC 开关测试 */
	  if((HAL_GetTick() - tick2 >= 50 ))
	  {
		  tick2 = HAL_GetTick();
		  if(CDCopen > 0)
		  {
			  CDCopen ++;
			  if(CDCopen%2 == 1) time = 10;
			  else time = 1000;
			  if(CDCopen > 9) 
			  {
				  CDCopen = 0;
				  HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_SET);
			  }
		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4);
}

/* USER CODE BEGIN 4 */
#if !VirtualCOM 
/**
  * @brief  Display the current time and date.
  * @param  show : pointer to buffer
  * @retval None
  */
static void RTC_CalendarShow(uint8_t *show)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;
  int32_t size;
	
  /* 必须同时获取时间和日期 不然会导致下次RTC不能读取 */
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss Display date Format : mm-dd-yy */
  size = sprintf((char *)show, "%02d:%02d:%02d,%02d月%02d日%2d年\r\n", stimestructureget.Hours,  
																					stimestructureget.Minutes,
																					stimestructureget.Seconds,
																					sdatestructureget.Month,
																					sdatestructureget.Date,
																					2000 + sdatestructureget.Year);
  CDC_Transmit_FS(show,size);
}
#endif
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
