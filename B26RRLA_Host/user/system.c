#include "system.h"


TIMEOUT_PARA TimeOut_Para[2];
extern unsigned char SendData1,SendData2;

extern unsigned long Get_Data;
unsigned char Flag;

void System_Init(void)
{
	if(Flag)
	{
		WDTCON |= 0x10;		    //�忴�Ź�
		 OPERCON = 0X00;         //CHKSUM����
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
       TouchKeyInit(); // ���ذ�����ʼ��
        EA = 1;
}


void System_Handle(void)
{
	WDTCON |= 0x10;		    //�忴�Ź�
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
	
       if(SOCAPI_TouchKeyStatus&0x80) // ��Ҫ���� 2: ������ɨ��һ�ֱ�־���Ƿ���� TouchKeyScan() һ��Ҫ���ݴ˱�־λ�����
	{
		SOCAPI_TouchKeyStatus &= 0x7f;// ��Ҫ���� 3:  �����־λ�� ��Ҫ�ⲿ�����
		Get_Data = TouchKeyScan();// �������ݴ�����
		TouchKeyRestart();// ������һ��ת��
	}
	while(Get_Data != 0x00)
	{
		while(1);
	}
	
}





