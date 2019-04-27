#include "bsp_key.h"

unsigned long Get_Data;
unsigned char SendData1,SendData2;

void Key_Init(void)
{
	TouchKeyInit(); // ���ذ�����ʼ��
}

void Key_Handle(void)
{
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
	#if 0
	switch (Get_Data)
	{
		case TK3_VALUE:
			                 if(SendData1 != LightData){
						SendData1 = LightData;
						SendData2 = LightData;
					    }
			                 break;
	       case TK4_VALUE:
		   	                 if(SendData1 != CupData){
						SendData1 = CupData;	
						SendData2 = CupData;
					    }
		   	                 break;
	       case TK5_VALUE:
		   	                 if(SendData1 != HomeData){
						SendData1 = HomeData;
						SendData2 = HomeData;
					    }
		   	                 break;
		case TK12_VALUE:
			                 if(SendData1 != OpenData){
						SendData1 = OpenData;
						SendData2 = OpenData;
					    }
			                 break;
		case TK14_VALUE:
			                 if(SendData1 != CloseData){
						SendData1 = CloseData;
						SendData2 = CloseData;
					    }
			                 break;
		case TK15_VALUE:
			                  if(SendData1 != HeadUpData){
						SendData1 = HeadUpData;	
						SendData2 = HeadUpData;
					    }
			                 break;
		case TK18_VALUE:
			                 if(SendData1 != HeadDownData){
						SendData1 = HeadDownData;
						SendData2 = HeadDownData;
					    }
			                 break;
		case TK19_VALUE:
			                 if(SendData1 != LockData){
						SendData1 = LockData;	
						SendData2 = LockData;	
					    }
			                 break;
		default:
			                 break;
	}
	#endif
}



