//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//#include "diag/Trace.h"
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
//SET HSE_VALUE to 8000000
// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
//#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"




void Rcc_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

void init_GPIO()
{
	GPIO_InitTypeDef GPIO_Init_structure;
	GPIO_StructInit(&GPIO_Init_structure);
	//USART_1_Tx
	GPIO_Init_structure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init_structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_structure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_Init_structure);
	//USART_1_Rx
	GPIO_Init_structure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Init_structure);
}
void init_USART_1()
{
	USART_InitTypeDef Usart_Init_structure;
	Rcc_Configuration();
	init_GPIO();
	USART_StructInit(&Usart_Init_structure);
	Usart_Init_structure.USART_BaudRate = 9600;
	Usart_Init_structure.USART_StopBits = USART_StopBits_1;
	Usart_Init_structure.USART_Parity = USART_Parity_No;
	Usart_Init_structure.USART_WordLength = USART_WordLength_8b;
	Usart_Init_structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	Usart_Init_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &Usart_Init_structure);
	USART_Cmd(USART1, ENABLE);


}



int putChar(int c)
{


	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET)
		;
	USART_SendData(USART1, c&0xff);

	return 0;
}
int getChar()
{
	while ( USART_GetFlagStatus (USART1 , USART_FLAG_RXNE ) == RESET);
	return USART_ReceiveData(USART1);
	//return USART1 ->DR & 0xff;
}


int main(int argc, char* argv[])
{


	init_USART_1();
	float i=2.1;

  while (1)
    {
	  char buffer[1024];
	  //putChar(getChar());
	  printf("Enter an string \t");
	  scanf("%s",buffer);
	  printf("You have entered %s\n",buffer);
	  //printf("Hello world %d\n",i);

    }
}

//#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
