#include "system.h"

TIMEOUT_PARA TimeOut_Para[2];
unsigned char TX_DATA;
unsigned int TX1_DATA;
extern unsigned char count_level,lock;
/******************************************************************************
*����:PETER
*����:190308
*����:ϵͳ������ʼ��
*����:��
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
    TouchKeyInit(); // ���ذ�����ʼ��
    WDTCON |= 0x10;
    EA = 1;
}

/******************************************************************************
*����:PETER
*����:190308
*����:ϵͳ��������
*����:��
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

