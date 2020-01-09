
/*******************************************************************************
  *
  * HID bootloader for STM32F407 MCU
  *
  ******************************************************************************
  * 
  *	Created by: Vassilis Serasidis
  *       Date: 28 June 2018
  *       Home: http://www.serasidis.gr
  *      email: avrsite@yahoo.gr, info@serasidis.gr
  *
  ******************************************************************************

  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "usb_device.h"
#include "stm32f4xx_ll_rtc.h"
#include "stm32f4xx_ll_pwr.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes	*/

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

uint8_t USB_RX_Buffer[HID_RX_SIZE];
uint8_t USB_TX_Buffer[8]; //USB data -> PC
static uint8_t CMD_SIGNATURE[7] = {'B','T','L','D','C','M','D'};

/* Command: <Send next data pack> */
static uint8_t CMD_DATA_RECEIVED[8] = {'B','T','L','D','C','M','D',2};
uint8_t new_data_is_received = 0;
static uint8_t pageData[SECTOR_SIZE];
typedef void (*funct_ptr)(void);

uint32_t magic_val;
uint16_t erase_page = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void write_flash_sector(uint32_t currentPage);
extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef *pdev, uint8_t *report, uint16_t len);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE BEGIN SysInit */
  MX_GPIO_Init();
   
  HAL_Delay(100);
  
  magic_val = LL_RTC_BAK_GetRegister(RTC, HID_MAGIC_NUMBER_BKP_INDEX);
  
  /* In case of incoming magic number or <BOOT_1_PIN> is LOW,
    jump to HID bootloader */
#if Is_WeAct_Board == 1 
  if ((HAL_GPIO_ReadPin(BOOT_1_PORT, BOOT_1_PIN) != BOOT_1_ENABLED)) {
    HAL_GPIO_WritePin(LED_1_PORT, LED_1_PIN, GPIO_PIN_SET);	
#else
  if ((magic_val != 0x424C)&&(HAL_GPIO_ReadPin(BOOT_1_PORT, BOOT_1_PIN) != BOOT_1_ENABLED)) {
#endif
    if(((*(__IO uint32_t*)FLASH_BASE + USER_CODE_OFFSET) & 0x2FF80000 ) == 0x20000000) {
      typedef void (*pFunction)(void);
      pFunction Jump_To_Application;
      uint32_t JumpAddress;
      
      JumpAddress = *(__IO uint32_t*) (FLASH_BASE + USER_CODE_OFFSET + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      __set_MSP(*(uint32_t *) (FLASH_BASE + USER_CODE_OFFSET));
      
      Jump_To_Application(); 
    }
  }
  
  /* Reset the magic number backup memory */
  
  /* Enable Power Clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Allow access to Backup domain */
  LL_PWR_EnableBkUpAccess();
  
  LL_RTC_BAK_SetRegister(RTC, HID_MAGIC_NUMBER_BKP_INDEX, 0);
  
  /* Forbid access to Backup domain */
  LL_PWR_DisableBkUpAccess();
  
  /* USER CODE END SysInit */
  
  /* Initialize all configured peripherals */
  
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */
                                               
  static volatile uint32_t current_Page = (USER_CODE_OFFSET / 1024);
  static volatile uint16_t currentPageOffset = 0;
                                                           
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    if (new_data_is_received == 1) {
      new_data_is_received = 0;
      if (memcmp(USB_RX_Buffer, CMD_SIGNATURE, sizeof (CMD_SIGNATURE)) == 0) {
        switch(USB_RX_Buffer[7]){
          case 0x00:

          /*------------ Reset pages */
          current_Page = 16;
          currentPageOffset = 0;
          erase_page = 1;
          // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_0);	
          break;

        case 0x01:

          /*------------- Reset MCU */
          if (currentPageOffset > 0) {

          /* There are incoming
             data that are less
             than sector size
             (16384) */
            write_flash_sector(current_Page);
          }
          HAL_Delay(100);
          HAL_NVIC_SystemReset();
          break;
        }
      } else {
        memcpy(pageData + currentPageOffset, USB_RX_Buffer, HID_RX_SIZE);
        currentPageOffset += HID_RX_SIZE;
        if (currentPageOffset == SECTOR_SIZE) {
          write_flash_sector(current_Page);
          current_Page++;
          currentPageOffset = 0;
          CMD_DATA_RECEIVED[7] = 0x02;
          USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, CMD_DATA_RECEIVED, 8);
        }
      }
    }
  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

/* 168 MHz */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the CPU, AHB and APB busses clocks (72 MHz) */

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

#if HSE_VALUE  == 8000000
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  #else
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  #endif
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Initializes the CPU, AHB and APB busses clocks  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
  RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
  RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  // __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  // __HAL_RCC_GPIOD_CLK_ENABLE();
  // __HAL_RCC_GPIOE_CLK_ENABLE();

  /* Configure GPIO pin Output Level */

  /* Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 
                               
                                  
                                        
                                    
                                              

  /* Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = BOOT_1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BOOT_1_PORT, &GPIO_InitStruct);

  /* Configure GPIO pin : PE0 */
  GPIO_InitStruct.Pin = LED_1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_1_PORT, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
void write_flash_sector(uint32_t currentPage) {
  uint32_t pageAddress = FLASH_BASE + (currentPage * SECTOR_SIZE);
  uint32_t SectorError;

  HAL_GPIO_WritePin(LED_1_PORT, LED_1_PIN, GPIO_PIN_SET);	
  FLASH_EraseInitTypeDef EraseInit;
  HAL_FLASH_Unlock();
  
                                                                                                         

  /* Sector to the erase the flash memory (16, 32, 48 ... kbytes) */
  if ((currentPage == 16) || (currentPage == 32) ||
      (currentPage == 48) || (currentPage == 64) ||
      (currentPage % 128 == 0)) {
    EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInit.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
    EraseInit.Banks = FLASH_BANK_1; 
    /* Specify sector number. Starts from 0x08004000 */
    EraseInit.Sector = erase_page++;
                                              
  

    /* This is also important! */
    EraseInit.NbSectors = 1;
    HAL_FLASHEx_Erase(&EraseInit, &SectorError);
  }

  uint32_t dat;
  for (int i = 0; i < SECTOR_SIZE; i += 4) {
    dat = pageData[i+3];
    dat <<= 8;
    dat += pageData[i+2];
    dat <<= 8;
    dat += pageData[i+1];
    dat <<= 8;
    dat += pageData[i];
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, pageAddress + i, dat);
  }
  HAL_GPIO_WritePin(LED_1_PORT, LED_1_PIN,GPIO_PIN_RESET);  
  HAL_FLASH_Lock();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) {
    ;
  }

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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name
   * and line number, tex: printf("Wrong parameters value: file
   * %s on line %d\r\n", file, line)
   */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
