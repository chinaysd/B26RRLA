#include "bsp_key.h"

unsigned long Get_Data;
unsigned char SendData1,SendData2;

void Key_Init(void)
{
	TouchKeyInit(); // 触控按键初始化
}

void Key_Handle(void)
{
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



