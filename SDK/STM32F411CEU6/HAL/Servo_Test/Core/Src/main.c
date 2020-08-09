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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
	
// WeAct 工作室 舵机测试
// PB9 5V  GND
// 橙  红  棕
// 按键 PA0/KEY
// 双击启动/关闭舵机
// 单击调速 10°/s ~ 480°/s
// 长按恢复呼吸灯

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ServoCtrl.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
unsigned short key_value;
uint32_t servo_speed;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 /*
  *power by WeAct Studio
  *The board with `WeAct` Logo && `version number` is our board, quality guarantee. 
  *For more information please visit: https://github.com/WeActTC/MiniF4-STM32F4x1
  *更多信息请访问：https://gitee.com/WeActTC/MiniF4-STM32F4x1
  */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
  uint32_t tick,tick1,tick2,tick3;
	uint8_t breathsw = 1;
	uint8_t Servosw = 1;
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
  MX_RTC_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
	ServoCtrlInit();
	HAL_TIM_PWM_Start_IT(&htim11,TIM_CHANNEL_1);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  /* C13 呼吸灯测试 */
	  /* C13 Breathing Lamp test */
		static uint8_t pwmset;
		static uint16_t time;
		static uint8_t timeflag;
		static uint8_t timecount;
	  if((HAL_GetTick() - tick >= 1 ))
	  {
		   tick = HAL_GetTick();
			
		   if(breathsw == 1)
			{
				 /* 呼吸灯 */
				 /* Breathing Lamp */
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
				/* Duty Cycle Setting */
				pwmset = time/80;

				/* 20ms 脉宽 */
				/* 20ms Pulse Width */
				if(timecount > 20) timecount = 0;
				else timecount ++;

				if(timecount >= pwmset ) HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_SET);
				else HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_RESET);
			}
		}
	  
	  /* 1ms 按键扫描 */
	  if(HAL_GetTick() - tick2 >= 1)
	  {
		  tick2 = HAL_GetTick();
		  key_check_all_loop_1ms();
	  }
	  
	  /* Key按键按下查询 */
	  if(HAL_GetTick() - tick3 >= 10)
	  {
		  tick3 = HAL_GetTick();
		  key_value = key_read_value();
		  
		  if(key_value == KEY0_UP_SHORT)
		  {
				if(Servosw == 1)
				{
					breathsw = 0;
					
					servo_speed = ServoCtrlS1.ServoSpeed + 40;
					if(servo_speed > 480) servo_speed = 10;
					ServoCtrlS1.ServoSpeed = servo_speed;
					
					HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_RESET);
				}
			  //HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,HAL_GPIO_ReadPin(C13_GPIO_Port,C13_Pin)==GPIO_PIN_SET?GPIO_PIN_RESET:GPIO_PIN_SET);
				
		  }
		  else if(key_value == KEY0_UP_DOUBLE)
		  {
			  breathsw = 0;
				
				Servosw = Servosw == 1?0:1;
				
				if(Servosw == 1)
					HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_RESET);
				else
				{
					ServoCtrlS1.ServoAngleSet = ServoCtrlS1.ServoAngleNow;
					HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,GPIO_PIN_SET);
				}
			  //HAL_GPIO_WritePin(C13_GPIO_Port,C13_Pin,HAL_GPIO_ReadPin(C13_GPIO_Port,C13_Pin)==GPIO_PIN_SET?GPIO_PIN_RESET:GPIO_PIN_SET);
		  }
		  else if(key_value == KEY0_LONG)
		  {
			  breathsw = 1;
		  }
			
			if(ServoCtrlS1.ServoAngleNow == ServoCtrlS1.ServoAngleSet && Servosw == 1)
			{
				if(ServoCtrlS1.ServoAngleSet >= 90)
					ServoCtrlS1.ServoAngleSet = 0;
				else ServoCtrlS1.ServoAngleSet = 180;
			}
	  }

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
