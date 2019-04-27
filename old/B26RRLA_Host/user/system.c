#include "system.h"


TIMEOUT_PARA TimeOut_Para[2];
extern unsigned char SendData1,SendData2;

extern unsigned long Get_Data;
unsigned char Flag;

void System_Init(void)
{
	if(Flag)
	{
		WDTCON |= 0x10;		    //清看门狗
		 OPERCON = 0X00;         //CHKSUM运算
		 _nop_();
		 TimeOutDet_Init();
		 Led_Init();
		 Timer_Init();
		 Uart1_Init(2,9600);
		 Uart2_Init(2,9600);
		 Key_Init();
		 Btm_Test();
		 //EA = 1;
	}
       TouchKeyInit(); // 触控按键初始化
        EA = 1;
}


void System_Handle(void)
{
	WDTCON |= 0x10;		    //清看门狗
	#if 0
	if(TimeOutDet_Check(&TimeOut_Para[0]))
	{
		TimeOut_Record(&TimeOut_Para[0],500);
		Protocol_Send(0XFA,0XFB,0X01);
		Protocol2_Send(0xfa,0xfb,0x02);
	}     
	#else
	if(Flag)
	{
		Key_Handle();
		if(TimeOutDet_Check(&TimeOut_Para[0]))
		{
			TimeOut_Record(&TimeOut_Para[0],500);
			Protocol_Send(0XFA,0XFB,SendData1);
			Protocol2_Send(0xfa,0xfb,SendData2);
		}  
	}
	#endif
	
       if(SOCAPI_TouchKeyStatus&0x80) // 重要步骤 2: 触摸键扫描一轮标志，是否调用 TouchKeyScan() 一定要根据此标志位置起后
	{
		SOCAPI_TouchKeyStatus &= 0x7f;// 重要步骤 3:  清除标志位， 需要外部清除。
		Get_Data = TouchKeyScan();// 按键数据处理函数
		TouchKeyRestart();// 启动下一轮转换
	}
	while(Get_Data != 0x00)
	{
		while(1);
	}
	
}





