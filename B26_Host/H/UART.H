#ifndef _UART_H_
#define _UART_H_

#include "string.h"

#define	Fsys		2
#define	BaudRate  9600

#define       NoData                    0x00
#define       OpenData                 0x01
#define       CloseData                 0x02
#define       HeadUpData              0x03
#define       HeadDownData          0x04
#define       LumbarOpenData       0x05
#define       LumbarCloseData       0x06
#define       TableOpenData          0x07       
#define       TableCloseData         0x08
#define       HomeData                0x09

#define       LedOpenData            0x11
#define       LedCloseData            0x22

#define       ExtiLedOpenData       0x0033
#define       ExtiLedCloseData       0x0044


#define UART1_BUF_SIZE     7
#define UART1_Hight(x)       ((x>>8)&0xff)
#define UART1_Low(x)         ((x)&0xff)

#define UART2_BUF_SIZE     7
#define UART2_Hight(x)       (((x)>>8)&0xff)
#define UART2_Low(x)         ((x)&0xff)

#define UART2_REVBUF_SIZE       7

#define Get32Bit(x,y)          (((x<<8)|y)&0xffff)

typedef struct
{
	unsigned char ADDR1;
	unsigned char ID1;
	unsigned char DATA1;
	unsigned char DATA2;
	unsigned char CHECKSUM1;
	unsigned char STOP1;
	unsigned char STOP2;
}
UART1_FORMAT_TX;

typedef union
{
	unsigned char Uart1_Buf[UART1_BUF_SIZE];
	UART1_FORMAT_TX Uart1_Format;
}
UART1_PROTOCOL_TX;

typedef struct
{
	unsigned char UART2_ADDR2;
	unsigned char UART2_ID2;
	unsigned char UART2_DATA1;
	unsigned char UART2_DATA2;
	unsigned char UART2_CHECKSUM2;
	unsigned char UART2_STOP1;
	unsigned char UART2_STOP2;
}
UART2_FORMAT_TX;

typedef union
{
    unsigned char Uart2_Buf[UART2_BUF_SIZE];
    UART2_FORMAT_TX Uart2_Format;
}
UART2_PROTOCOL_TX;



void uart_init(unsigned char Fsystem,unsigned int BaudRate_Count);
void Uart1_Init(unsigned char Freq,unsigned long int baud);
unsigned char Uart1_ProtocolSend(unsigned char addr1,unsigned char id1,unsigned int uart1data);
unsigned char Uart2_ProtocolSend(unsigned char addr2,unsigned char id2,unsigned int uart2data);
void Uart1_Tx_Byte(unsigned char Test2Data);
void UART_TX_byte(unsigned char Test1Data);

unsigned char RevData_If(void);
unsigned char Rev_Data(void);


#endif
