/**
  ******************************************************************************
	WeAct Î¢ÐÐ´´ÐÂ 
	>> ±ê×¼¿â TIM
  ******************************************************************************
  */

#include "tim.h"
/**
  * @brief  Configures the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  uint16_t PrescalerValue = 0;
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1; // 1Mhz

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 100;  // 0.1ms
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
  
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE); 
}


void TIM3_IT_Update_Callback()
{
#if !soft_pwm
	/* C13 ºôÎüµÆ²âÊÔ */
	static uint8_t pwmset;
	static uint16_t time;
	static uint8_t timeflag;
	static uint8_t timecount;

	 /* ºôÎüµÆ */
	if(timeflag == 0)
	{
		time ++;
		if(time >= 16000) timeflag = 1;
	}
	else
	{
		time --;
		if(time == 0) timeflag = 0;
	}

	/* Õ¼¿Õ±ÈÉèÖÃ */
	pwmset = time/320;

	/* 5ms Âö¿í */
	if(timecount > 50) timecount = 0;
	else timecount ++;

	if(timecount >= pwmset ) GPIO_SetBits(LED_C13_PORT,LED_C13_PIN);
	else GPIO_ResetBits(LED_C13_PORT,LED_C13_PIN);
	//GPIO_ToggleBits(LED_C13_PORT,LED_C13_PIN);
#endif
}

