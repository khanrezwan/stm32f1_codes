#ifndef __SPI_H
#define __SPI_H


//����Ķ���3.50��3.22�Ŀⲻһ��
//----------------------------------------------
//#define SPI_FLAG_RXNE           SPI_I2S_FLAG_RXNE
//#define SPI_FLAG_TXE            SPI_I2S_FLAG_TXE
////#define SPI_FLAG_CRCERR                    ((u16)0x0010)
////#define SPI_FLAG_MODF                      ((u16)0x0020)
//#define SPI_FLAG_OVR            SPI_I2S_FLAG_OVR
//#define SPI_FLAG_BSY            SPI_I2S_FLAG_BSY
////----------------------------------------------
//#define SPI_GetFlagStatus       SPI_I2S_GetFlagStatus
//#define SPI_SendData            SPI_I2S_SendData
//#define SPI_ReceiveData         SPI_I2S_ReceiveData


#define  SPInet_ReadWrite  SPI2_ReadWrite
#define  SPInet_Init   SPI2_Init

////SPI1��ʼ��
//void SPI1_Init(void);
////SPI1��дһ�ֽ����
//uint8_t SPI1_ReadWrite(uint8_t writedat);


//SPI2��ʼ��
void SPI2_Init(void);
//SPI2��дһ�ֽ����
uint8_t SPI2_ReadWrite(uint8_t writedat);

#endif
