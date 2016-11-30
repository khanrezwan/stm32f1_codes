//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"

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

void init_GPIO()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_6;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init_struct);

	gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
}

void init_ADC()
{
	ADC_InitTypeDef adc_init_struct;
	adc_init_struct.ADC_Mode =ADC_Mode_Independent;
	adc_init_struct.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init_struct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc_init_struct.ADC_NbrOfChannel = 1;
	adc_init_struct.ADC_ContinuousConvMode = ENABLE;
	adc_init_struct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &adc_init_struct);

	ADC_Cmd(ADC1,ENABLE);
	////calibration
	 ADC_ResetCalibration(ADC1);
	while ( ADC_GetResetCalibrationStatus (ADC1));
	ADC_StartCalibration (ADC1);
	while ( ADC_GetCalibrationStatus (ADC1));
}

uint16_t readADC1_Polling(uint8_t channel)
{
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET)
	{

	}
	return ADC_GetConversionValue (ADC1);
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	init_GPIO();
	init_ADC();
	uint16_t ain;
  // Infinite loop
  while (1)
    {
       // Add your code here.
	  ain = readADC1_Polling(6);
	  trace_printf("%d \n",ain);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
