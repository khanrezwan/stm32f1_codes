//#include "..\main\include.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "SPI.H"
extern SPI_HandleTypeDef hspi2;
extern void MX_SPI2_Init(void);
extern void MX_GPIO_Init(void);
//SPI1��ʼ��
//void SPI1_Init(void)
//{
//   SPI_InitTypeDef SPI_InitStructure;
//   GPIO_InitTypeDef GPIO_InitStructure;
//
//   /* Enable SPI1 and GPIOA clocks */
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
//
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//   GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//   GPIO_Init(GPIOD, &GPIO_InitStructure);
//
//   /* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //��������
//   GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//   /* SPI1 configuration */
//   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
//   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
//   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//   SPI_InitStructure.SPI_CRCPolynomial = 7;
//   SPI_Init(SPI1, &SPI_InitStructure);
//
//   /* Enable SPI1  */
//   SPI_Cmd(SPI1, ENABLE);
//}
//
////SPI1��дһ�ֽ����
//unsigned char SPI1_ReadWrite(unsigned char writedat)
//{
//   /* Loop while DR register in not emplty */
//   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
//
//   /* Send byte through the SPI1 peripheral */
//   SPI_SendData(SPI1, writedat);
//
//   /* Wait to receive a byte */
//   while (SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
//
//   /* Return the byte read from the SPI bus */
//   return SPI_ReceiveData(SPI1);
//}


void SPI2_Init(void)
{
	MX_GPIO_Init();
	MX_SPI2_Init();

}

//SPI2��дһ�ֽ����
uint8_t SPI2_ReadWrite(uint8_t writedat)
{
	unsigned char return_dat;
//   /* Loop while DR register in not emplty */
//   while (SPI_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET);
//
//   /* Send byte through the SPI1 peripheral */
//   SPI_SendData(SPI2, writedat);
//
//   /* Wait to receive a byte */
//   while (SPI_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET);
//
//   /* Return the byte read from the SPI bus */
//   return SPI_ReceiveData(SPI2);
	HAL_SPI_Transmit(&hspi2,&writedat,1,HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi2,&return_dat,1,HAL_MAX_DELAY);
	return return_dat;
}

