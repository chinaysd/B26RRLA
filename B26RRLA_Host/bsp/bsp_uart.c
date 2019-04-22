#include "bsp_uart.h"


unsigned char Uart1SendFlag,Uart1ReceiveFlag;



void Uart1_Init(unsigned char Fsystem,unsigned int BaudRate_Count)
{
	P1CON &= 0xF3;   //TX/RX设置为输入带上拉
	P1PH  |= 0x0C;
	
	SCON  |= 0X50;   //设置通信方式为模式一，允许接收
	TMCON |= 0X02;
	TMOD  |= 0X20;
	PCON  |= 0X80;	//SMOD=1
	TH1 = (Fsystem*1000000/BaudRate_Count)>>8;	  //波特率为T1的溢出时间；
	TL1 = Fsystem*1000000/BaudRate_Count;
	TR1 = 0;
	ET1 = 0;
	EUART = 0;     //开启Uart0中断
}

void Uart2_Init(unsigned char Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
	P2PH  |= 0x03;
	
	OTCON = 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = Freq*1000000/baud;   //波特率低位控制
	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
	IE1 = 0x01;      //开启SSI中断
}

/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口0发送函数
*返回:无
*******************************************************************************/
static void UART_TX_byte(unsigned char DATA)
{
   TI = 0;
   SBUF = DATA;
   while(!TI);
}

static unsigned char  Uart1_SendData(PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0; i < UART1_BUF_SIZE; i ++)
	{
		UART_TX_byte(p->UART1_Buf[i]);
	}
	return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int TX1_DATA)
{
	PROTOCOL_TX buf;
	memset(&buf,0,sizeof(buf));
	buf.Uart1_Format.ADDR = addr;
	buf.Uart1_Format.ID      = id;
	buf.Uart1_Format.DATA1 = Hight(TX1_DATA);
	buf.Uart1_Format.DATA2 = Low(TX1_DATA);
	buf.Uart1_Format.CHECKSUM = (unsigned char)(buf.Uart1_Format.ADDR+buf.Uart1_Format.ID+buf.Uart1_Format.DATA1+buf.Uart1_Format.DATA2);
	buf.Uart1_Format.STOP1 = 0x0d;
	buf.Uart1_Format.STOP2 = 0x0a;
	return Uart1_SendData(&buf);
}
/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口1发送函数
*返回:无
*******************************************************************************/

static void Uart1_Tx_Byte(unsigned char Uart1_Data)
{
	SSDAT = Uart1_Data;
	//while(!Uart1SendFlag);
	Uart1SendFlag = 0;
}

static unsigned char Send2_Data(PROTOCOL_TX2 *p)
{
	static unsigned char i;
	for(i = 0; i < UART2_BUF_SIZE; i ++)
	{
		Uart1_Tx_Byte(p->UART2_Buf[i]);
	}
	return 0;
}

unsigned char Protocol2_Send(unsigned char add2,unsigned char id2,unsigned int TX2_DATA)
{
	PROTOCOL_TX2 TX2_Buf;
	memset(&TX2_Buf,0,sizeof(TX2_Buf));
	TX2_Buf.Uart2_Format.TX2_ADDR = add2;
	TX2_Buf.Uart2_Format.TX2_ID = id2;
	TX2_Buf.Uart2_Format.TX2_DATA1 = TX2_Hight(TX2_DATA);
	TX2_Buf.Uart2_Format.TX2_DATA2 = TX2_Low(TX2_DATA);
	TX2_Buf.Uart2_Format.TX2_CHECKSUM = (unsigned char)(TX2_Buf.Uart2_Format.TX2_ADDR+TX2_Buf.Uart2_Format.TX2_ID+TX2_Buf.Uart2_Format.TX2_DATA1+TX2_Buf.Uart2_Format.TX2_DATA2);
	TX2_Buf.Uart2_Format.TX2_STOP1 = 0x0d;
	TX2_Buf.Uart2_Format.TX2_STOP2 = 0x0a;
       return Send2_Data(&TX2_Buf);
}


/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口1接收函数
*返回:无
*******************************************************************************/
unsigned char Rev_Data(unsigned char SLAVE)
{
    SLAVE = SSDAT;
    return SLAVE;
}

/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口1中断处理函数
*返回:无
*******************************************************************************/

void Uart1_Int() interrupt 7   //Uart1中断函数
{
	if(SSCON0&0x02)    //发送标志位判断
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if((SSCON0&0x01))  //接收标志位判断
	{
		SSCON0 &= 0xFE;
		Uart1ReceiveFlag = 1;
	}	
}






