#include "key.h"

extern unsigned char count_level,TX_DATA,key_press,RevString[UART2_REVBUF_SIZE];
extern unsigned int TX1_DATA;
extern unsigned long int MyKey_Buf_Data;


unsigned long int  get_key_data,RevGetData;
unsigned int u16TimeLock;
unsigned char lock;
/******************************************************************************
*作者:PETER
*日期:190308
*描述:触摸按键处理函数
*返回:无
*******************************************************************************/
static void Key_Handle(void)
{
	if(get_key_data != 0)	//键按下
	{
			MyKey_Buf_Data = get_key_data;
			if((TK1_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				Foot_Led_Cmd();	
			  }
			}
			else if((TK2_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				Cup_Open_Cmd();			
			  }
			}
			else if((TK3_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushB_Open_Cmd();			
			  }
			}
			else if((TK4_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				Push_Reset_Cmd();			
			  }
			}
			else if(TK5_VALUE == MyKey_Buf_Data)
			{
			  if(key_press)
			  {		    
				key_press = 0;
			  }
			}
			else if((TK6_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushA_Open_Cmd();
			  }
			  
			}
			else if((TK7_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushA_Close_Cmd(); 	
			  }
			  
			}
			else if((TK8_VALUE == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushB_Close_Cmd();	
			  }
			 
			}
			else if((0X0100 == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushC_Open_Cmd();	
			  }
			  
			}
			else if((0X0200 == MyKey_Buf_Data)&&(lock))
			{
			  if(key_press)
			  {
				key_press = 0;
				PushC_Close_Cmd();			
			  }
			}
	   }
	else
	{
		MyKey_Buf_Data = 0x0000;
		if(!key_press)
		{
			key_press = 1;
		    TX_DATA = 0X55;
		    TX1_DATA = 0X00;
		}
	}
	#if 1
	if(RevData_If())
	{
		RevGetData = (unsigned long)Get32Bit(RevString[2],RevString[3]);
		memset(&RevString,0,sizeof(RevString));
		switch (RevGetData)
		{
			case ExtiLedOpenData:
						key_press = 1;
						TX_DATA = LedOpenData;	//往下发的指令
						count_level = 100;
				             break;
		       case ExtiLedCloseData:
						key_press = 1;
						TX_DATA = LedCloseData;	//往下发的指令
						count_level = 15;
					      break;
		        default:
					    break;
		}
	}
	#endif
}

void Lock_Handle(void)
{
	 static unsigned char LockTempFlag,LockTempCnt;
	 if(0X4000 == MyKey_Buf_Data)
	 {
	 	if(!LockTempFlag)
	 	{
			LockTempFlag = 1;
			++ LockTempCnt;
		}
		if(LockTempCnt & 0x01)
		{
			lock = 0;
		}
		else
		{
			lock = 1;
		}
	 	if(!lock)
	 	{
		   if(u16TimeLock < 3000)
		   {
		      u16TimeLock++;
		   }
		   else
		   {
		      u16TimeLock = 0;
			  IO_RED_LIGHT_ON;
		   }
		}
		else
		{
		   if(u16TimeLock < 3000)
		   {
		      u16TimeLock++;
		   }
		   else
		   {
		      u16TimeLock = 0;
			  IO_RED_LIGHT_OFF;
		   }
		}
	 }
	 else
	 {
	 	LockTempFlag = 0;
	 }
}

/******************************************************************************
*作者:PETER
*日期:190308
*描述:触摸按键扫描函数
*返回:无
*******************************************************************************/
void Key_Scanf(void)
{
	WDTCON|=0x10;
	if(SOCAPI_TouchKeyStatus&0x80) // 重要步骤 2: 触摸键扫描一轮标志，是否调用 TouchKeyScan() 一定要根据此标志位置起后
    {
		SOCAPI_TouchKeyStatus &= 0x7f;// 重要步骤 3:  清除标志位， 需要外部清除。
		get_key_data = TouchKeyScan();// 按键数据处理函数
		TouchKeyRestart();//启动下一轮转换
	}
	Key_Handle();
}























