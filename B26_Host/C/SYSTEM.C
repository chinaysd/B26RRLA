#include "system.h"

TIMEOUT_PARA TimeOut_Para[2];
unsigned char TX_DATA;
unsigned int TX1_DATA;
extern unsigned char count_level,lock;
/******************************************************************************
*作者:PETER
*日期:190308
*描述:系统函数初始化
*返回:无
*******************************************************************************/


void System_Init(void)
{
    TimeOutDet_Init();
    uart_init(Fsys,BaudRate);
    Uart1_Init(Fsys,BaudRate);
    GPIO_INIT();
    Timer0_Init();
    lock = 1;
    count_level = 15;
    TouchKeyInit(); // 触控按键初始化
    WDTCON |= 0x10;
    EA = 1;
}

/******************************************************************************
*作者:PETER
*日期:190308
*描述:系统处理函数
*返回:无
*******************************************************************************/


void System_Handle(void)
{
	WDTCON |= 0x10;
    Key_Scanf();
	if(TimeOutDet_Check(&TimeOut_Para[0]))      
	{
		TimeOut_Record( &TimeOut_Para[0],OnLine_Time);
		Uart1_ProtocolSend(0xfa,0xfb,TX_DATA);
		Uart2_ProtocolSend(0xfa,0xfb,TX1_DATA);
	}
}
/******************************************************************************/


