#include "UART.h"
#include "SC92F836xB_C.H"

unsigned char Uart1SendFlag,Uart1ReceiveFlag,SLAVE,RevData,RevNum,RevString[UART2_REVBUF_SIZE];

/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口0初始化
*返回:无
*******************************************************************************/
void uart_init(unsigned char Fsystem,unsigned int BaudRate_Count)
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

/*****************************************************
*函数名称：void Uart1_Init(uint Freq,unsigned long int baud)
*函数功能：Uart1中断初始化
*入口参数：Freq-主频，baud-波特率
*出口参数：Freq,baud
*****************************************************/
void Uart1_Init(unsigned char Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
	P2PH  |= 0x03;
	OTCON = 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = Freq*1000000/baud;   //波特率低位控制
	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
	IE1 = 0x01;      //开启SSI中断
       EA = 1;	
}

/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口0发送函数
*返回:无
*******************************************************************************/
static void UART_TX_byte(unsigned char Test1Data)
{
   TI = 0;
   SBUF = Test1Data;
   while(!TI);
}

static unsigned char Uart1_SendData(UART1_PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0; i < UART1_BUF_SIZE;i ++)
	{
		UART_TX_byte(p->Uart1_Buf[i]);
	}
	return 0;
}
#if 1
unsigned char Uart1_ProtocolSend(unsigned char addr1,unsigned char id1,unsigned int uart1data)
{
	UART1_PROTOCOL_TX Uart1_buf;
	memset(&Uart1_buf,0,sizeof(Uart1_buf));
	Uart1_buf.Uart1_Format.ADDR1 = addr1;
	Uart1_buf.Uart1_Format.ID1      = id1; 
	Uart1_buf.Uart1_Format.DATA1  = UART1_Hight(uart1data);
	Uart1_buf.Uart1_Format.DATA2 = UART1_Low(uart1data);
	Uart1_buf.Uart1_Format.CHECKSUM1 = (unsigned char)(Uart1_buf.Uart1_Format.ADDR1+Uart1_buf.Uart1_Format.ID1+Uart1_buf.Uart1_Format.DATA1+Uart1_buf.Uart1_Format.DATA2);
	Uart1_buf.Uart1_Format.STOP1 = 0x0d;
	Uart1_buf.Uart1_Format.STOP2 = 0x0a;
	return Uart1_SendData(&Uart1_buf);
}
#endif
/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口1发送函数
*返回:无
*******************************************************************************/

static void Uart1_Tx_Byte(unsigned char Test2Data)
{
	SSDAT = Test2Data;
	while(!Uart1SendFlag);
	Uart1SendFlag = 0;
}

static unsigned char Uart2_SendData(UART2_PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0 ;i < UART2_BUF_SIZE;i ++)
	{
		Uart1_Tx_Byte(p->Uart2_Buf[i]);
	}
	return 0;
}

#if 1
unsigned char Uart2_ProtocolSend(unsigned char addr2,unsigned char id2,unsigned int uart2data)
{
	UART2_PROTOCOL_TX Uart2_buf;
	memset(&Uart2_buf,0,sizeof(Uart2_buf));
	Uart2_buf.Uart2_Format.UART2_ADDR2 = addr2;
	Uart2_buf.Uart2_Format.UART2_ID2      = id2;
	Uart2_buf.Uart2_Format.UART2_DATA1 = UART2_Hight(uart2data);
	Uart2_buf.Uart2_Format.UART2_DATA2 = UART2_Low(uart2data);
	Uart2_buf.Uart2_Format.UART2_CHECKSUM2 = (unsigned char)(Uart2_buf.Uart2_Format.UART2_ADDR2+Uart2_buf.Uart2_Format.UART2_ID2+Uart2_buf.Uart2_Format.UART2_DATA1+Uart2_buf.Uart2_Format.UART2_DATA2);
	Uart2_buf.Uart2_Format.UART2_STOP1 = 0x0d;
	Uart2_buf.Uart2_Format.UART2_STOP2 = 0x0a;
	return Uart2_SendData(&Uart2_buf);
}
#endif
/******************************************************************************
*作者:PETER
*日期:190308
*描述:串口1接收函数
*返回:无
*******************************************************************************/
unsigned char Rev_Data(void)
{
    SLAVE = SSDAT;
    return SLAVE;
}

unsigned char RevData_If(void)
{
	if(RevNum & 0x80)
	{
		RevNum = 0x00;
		return 1;
	}
	else
	{
		return 0;
	}
}

static void RevData_Handle(void)
{
	RevData = Rev_Data();
	if(0 == (RevNum & 0x80))
	{
		if(RevNum & 0x40)
		{
			if(RevData == 0x0a)
			{
				RevNum = 0x80;
			}
			else
			{
				RevNum = 0x00;
			}
		}
		else
		{
			if(RevData == 0x0d)
			{
				RevNum = 0x40;
			}
			else
			{
				RevString[RevNum]=RevData;
				RevNum ++;
				if(RevString[0] != 0xfa)
				{
					RevNum = 0;
				}
				if(RevNum > UART2_REVBUF_SIZE)
				{
					RevNum = 0;
				}
			}
		}
	}
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
	RevData_Handle();
}



