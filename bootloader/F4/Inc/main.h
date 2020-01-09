/*******************************************************************************
  *
  * HID bootloader for STM32F407 MCU
  *
  ******************************************************************************
  *
  *      Created by: Vassilis Serasidis
  *       Date: 28 June 2018
  *       Home: http://www.serasidis.gr
  *      email: avrsite@yahoo.gr, info@serasidis.gr
  *
  ******************************************************************************







  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */

/* USER CODE BEGIN Private defines */

#define USER_CODE_OFFSET  0x4000 //<USER CODE> flash start address.

#define SECTOR_SIZE   1024
#define HID_RX_SIZE   64

#define HID_MAGIC_NUMBER_BKP_INDEX LL_RTC_BKP_DR4
#define HID_MAGIC_NUMBER_BKP_VALUE 0x424C
                             
                        
#define Is_WeAct_Board (1)
#define BOOT_1_PIN      GPIO_PIN_0 //WeAct STM32F4X1 board (Button PA0, LED PC13)
#define BOOT_1_PORT     GPIOA
#define BOOT_1_ENABLED  GPIO_PIN_RESET
#define LED_1_PIN       GPIO_PIN_13
#define LED_1_PORT      GPIOC
#define HSE_VALUE    (25000000)

// #define BOOT_1_PIN      GPIO_PIN_15 //DIYMROE STM32F407VGT board (Button PD15, LED PE0)
// #define BOOT_1_PORT     GPIOD
// #define BOOT_1_ENABLED  GPIO_PIN_RESET
// #define LED_1_PIN       GPIO_PIN_0
// #define LED_1_PORT      GPIOE
       
// #define BOOT_1_PIN      GPIO_PIN_2 //Black VET6 (http://wiki.stm32duino.com/index.php?title=STM32F407)
// #define BOOT_1_PORT     GPIOB
// #define BOOT_1_ENABLED  GPIO_PIN_SET // Active if this pin goes to 3.3V (Logic HIGH)
// #define LED_1_PIN       GPIO_PIN_6 //PA6 = LED D2
// #define LED_1_PORT      GPIOA

//#define BOOT_1_PIN      GPIO_PIN_4 //Arch_MAX (Button PB4, LED PB3)
//#define BOOT_1_PORT     GPIOB
//#define BOOT_1_ENABLED  GPIO_PIN_RESET
//#define LED_1_PIN       GPIO_PIN_3
//#define LED_1_PORT      GPIOB

// #define BOOT_1_PIN      GPIO_PIN_13 //Nucleo STM32F411RE board (Button PC13, LED PA5)
// #define BOOT_1_PORT     GPIOC
// #define BOOT_1_ENABLED  GPIO_PIN_RESET
// #define LED_1_PIN       GPIO_PIN_5
// #define LED_1_PORT      GPIOA

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
