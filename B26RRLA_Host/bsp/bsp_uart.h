#ifndef _BSP_UART_H_
#define _BSP_UART_H_


#include "sc92f836xb_c.h"
#include "string.h"


#define UART1_BUF_SIZE     7
#define UART2_BUF_SIZE     7
#define Hight(x)                 (((x)>>8)&0xff)
#define Low(x)                  ((x)&0xff)
#define TX2_Hight(y)          (((y)>>8)&0xff)
#define TX2_Low(y)            ((y)&0xff)

typedef struct
{
	unsigned char ADDR;
	unsigned char ID;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM;
	unsigned char STOP1;
	unsigned char STOP2;
}
UART1_FORMAT_TX;

typedef union
{
	unsigned char UART1_Buf[UART1_BUF_SIZE];
	UART1_FORMAT_TX Uart1_Format;
}
PROTOCOL_TX;

typedef struct
{
	unsigned char TX2_ADDR;
	unsigned char TX2_ID;
	unsigned char TX2_DATA1;
	unsigned char TX2_DATA2;
	unsigned char TX2_CHECKSUM;
	unsigned char TX2_STOP1;
	unsigned char TX2_STOP2;
}
UART2_FORMAT_TX;

typedef union
{
	unsigned char UART2_Buf[UART2_BUF_SIZE];
	UART2_FORMAT_TX Uart2_Format;
}
PROTOCOL_TX2;












void Uart1_Init(unsigned char Fsystem,unsigned int BaudRate_Count);
void Uart2_Init(unsigned char Freq,unsigned long int baud);


unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int TX1_DATA);
unsigned char Protocol2_Send(unsigned char add2,unsigned char id2,unsigned int TX2_DATA);
unsigned char Rev_Data(unsigned char SLAVE);


#endif



