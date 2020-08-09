/**
  ******************************************************************************
	WeAct 微行创新 
	>> 标准库实例例程
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

// 全局定义 STM32F411xE 或者 STM32F401xx
// 当前定义 STM32F401xx

// STM32F411 外部晶振25Mhz，考虑到USB使用，内部频率设置为96Mhz
// 需要100mhz,自行修改system_stm32f4xx.c

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
 /*
  *power by WeAct Studio
  *The board with `WeAct` Logo && `version number` is our board, quality guarantee. 
  *For more information please visit: https://github.com/WeActTC/MiniF4-STM32F4x1
  *更多信息请访问：https://gitee.com/WeActTC/MiniF4-STM32F4x1
  */
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	// For APP Setting
	// Project IROM1 ADDR Start 0x8004000
	SCB->VTOR = FLASH_BASE | 0x4000; 
	
	/* Enable Clock Security System(CSS): this will generate an NMI exception
     when HSE clock fails *****************************************************/
  RCC_ClockSecuritySystemCmd(ENABLE);
	
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */
	SystemCoreClockUpdate();
  RCC_GetClocksFreq(&RCC_Clocks);
  /* SysTick end of count event each 1ms */
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  /* End SysTick end of count event each 1ms */
	
  /* Add your application code here */
  /* Insert 50 ms delay test */
  STD_Delay(50);
	
  GPIO_Config();
  TIM_Config(); 
  
  /* Infinite loop */
  while (1)
  {
		// 1ms Task
		static uint32_t tick;
		if((STD_GetTick() - tick >= 1 ))
	  {
		   tick = STD_GetTick();
			
       /* 一键下载 */			
			 /* 实现长按进入bootloader下载 */
			 static uint32_t timecount = 0;
			 if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN) == 0)
			 {
				 timecount ++;
				 if(timecount >= 500)
				 {
					 // 复位MCU
					 NVIC_SystemReset();
					 // 由于<KEY>一直按下，复位检测到<KEY>按下，留在Bootloader，等待上位机烧录命令
					 // 此时bootloader 快速闪烁，松开<KEY>即可
				 }
			 }
			 else
				 timecount = 0;
			 /* END 一键下载 */
		}
		
#if soft_pwm
		
		// 1ms Task
		static uint32_t tick1;
		if((STD_GetTick() - tick1 >= 1 ))
	  {
			tick1 = STD_GetTick();
			
			/* C13 呼吸灯测试 */
			static uint8_t pwmset;
			static uint16_t time;
			static uint8_t timeflag;
			static uint8_t timecount;

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

			if(timecount >= pwmset ) GPIO_SetBits(LED_C13_PORT,LED_C13_PIN);
			else GPIO_ResetBits(LED_C13_PORT,LED_C13_PIN);
			
		}
		
#endif
	}
}

#define STD_MAX_DELAY      0xFFFFFFFFU
static __IO uint32_t uwTimingDelay = 0;

__weak uint32_t STD_GetTick(void)
{
  return uwTimingDelay;
}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void STD_Delay(__IO uint32_t Delay)
{ 
	
	uint32_t tickstart = STD_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < STD_MAX_DELAY)
  {
    wait += (uint32_t)(1);
  }

  while((STD_GetTick() - tickstart) < wait)
  {
  }
}
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void STD_TimingDelay_Iecrement(void)
{
    uwTimingDelay++;
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
