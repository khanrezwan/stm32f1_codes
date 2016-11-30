//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f10x.h"
#include"stm32f10x_gpio.h"
#include"stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x_rcc.h"

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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_0;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&gpio_init_struct);

	gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_0;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);

}

void init_EXTI0()
{
	GPIO_EXTILineConfig ( GPIO_PortSourceGPIOC , GPIO_PinSource0 );
	EXTI_InitTypeDef exti_init_struct;
	exti_init_struct.EXTI_Line = EXTI_Line0;
	exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init_struct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init_struct);

}
void init_NVIC_EXTI0()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef nvic_init_struct;
	nvic_init_struct.NVIC_IRQChannel = EXTI0_IRQn;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 3;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_struct);

}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0)==SET)
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		else
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

	init_GPIO();
	init_EXTI0();
	init_NVIC_EXTI0();


	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
  // Infinite loop
  while (1)
    {
       // Add your code here.
//	  if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0))
//	  {
//		  GPIO_SetBits(GPIOB,GPIO_Pin_0);
//		  trace_printf("High\n");
//	  }
//	  else
//	  {
//		  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//		  trace_printf("Low\n");
//	  }

    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
