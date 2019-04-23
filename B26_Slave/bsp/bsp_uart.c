#include "bsp_uart.h"



unsigned char Rev_Num,Rev_Data,Rev_String[REV_BUF_SIZE];


unsigned char UART_Recive(void)
{
     unsigned char UART1_Re_Buf;
     while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);//接受数据寄存器非空
     UART1_Re_Buf=UART1_ReceiveData8();
     return  UART1_Re_Buf;
}

unsigned char Rev_Select(void)
{
	if(Rev_Num & 0x80)
	{
		Rev_Num &= 0x00;
		return 1;
	}
	else
	{
		return 0;
	}
}

void RevData_Handle(void)
{
	Rev_Data = UART1_ReceiveData8();//UART_Recive();
	if((Rev_Num & 0x80) == 0x00)
	{
		if(Rev_Num == 0x40)
		{
			if(Rev_Data == 0x0A)
			{
				Rev_Num = 0x80;
			}
			else
			{
				Rev_Num &= 0x00;
			}
		}
		else
		{
			if(Rev_Data == 0x0D)
			{
				Rev_Num = 0x40;
			}
			else
			{
				Rev_String[Rev_Num] = Rev_Data;
			       Rev_Num ++;
				if(Rev_String[0] != 0xfa)
				{
					Rev_Num &= 0x00;
				}
				if(Rev_Num > REV_BUF_SIZE)
				{
					Rev_Num &= 0x00;
				}
			}
		}
	}
}

void Uart_Init(void)
{
    #if 0
    UART1_DeInit();
    UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
    UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , UART1_MODE_RX_ENABLE);//波特率，字节数，1个停止位，无奇偶效验位，非同步模式，允许接受和发送
    UART1_ITConfig(UART1_IT_IDLE,ENABLE);//配置成接收中断
    //UART1_ITConfig(UART1_IT_RXNE,ENABLE);//配置成接收中断
    //UART1_ITConfig(UART1_IT_IDLE,ENABLE);//配置成接收中断
    UART1_Cmd(ENABLE );
    //return 0;
    #else
      UART1_DeInit();  
	UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,\
	UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);  
	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);   
	UART1_Cmd(ENABLE); 
    #endif
}




