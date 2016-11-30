//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
// ----------------------------------------------------------------------------
//
// STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


void init_GPIO()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_0;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);

//Timer2 CH2
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_1;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio_init_struct);
}

void init_NVIC()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitTypeDef nvic_init_struct;
	nvic_init_struct.NVIC_IRQChannel = TIM2_IRQn;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_struct);
}

void init_PWM_Channel_2()
{
	TIM_OCInitTypeDef TIM_OCInitStructure ;
	TIM_OCStructInit (& TIM_OCInitStructure );
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init (TIM2 , &TIM_OCInitStructure );
}

void init_Timer()
{
		TIM_TimeBaseInitTypeDef Time_2_base_struct;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		TIM_TimeBaseStructInit(&Time_2_base_struct);
		Time_2_base_struct.TIM_CounterMode = TIM_CounterMode_Up;
		Time_2_base_struct.TIM_Prescaler = SystemCoreClock/100 -1;
		Time_2_base_struct.TIM_Period = 1000-1;
		TIM_TimeBaseInit(TIM2, &Time_2_base_struct);
		//init_GPIO_A_1(); // GPIO A1 is TIM2_CH2
		init_PWM_Channel_2();
		TIM_ITConfig (TIM2,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM2, ENABLE);

}

void TIM2_IRQHandler(void)
{
	static int i = 0;
	static int j =10;
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0)==SET)
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
	TIM_SetCompare2 (TIM2 , i);
	i+=j;
	if ((i==0)||(i==1000))
	{
		j = -j;
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

  // Infinite loop
	init_GPIO();
	init_NVIC();
	init_Timer();
  while (1)
    {
       // Add your code here.
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
