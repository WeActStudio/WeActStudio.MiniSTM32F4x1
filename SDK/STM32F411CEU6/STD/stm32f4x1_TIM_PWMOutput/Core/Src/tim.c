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
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  GPIO_InitTypeDef GPIO_InitStructure;
	
  uint16_t PrescalerValue = 0;
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
  /* GPIOB Configuration: TIM3 CH1 (PB4) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);	
	
  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1; // 1Mhz

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 100-1;  // 0.1ms
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
  
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  
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

