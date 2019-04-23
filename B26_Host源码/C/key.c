#include "key.h"

extern unsigned char count_level;
extern unsigned char lock;

extern unsigned char TX_DATA;
extern unsigned int TX1_DATA;

unsigned long int  get_key_data;
extern unsigned long int MyKey_Buf_Data;

extern unsigned char    key_press;

extern unsigned char RevString[UART2_REVBUF_SIZE];
unsigned long RevGetData;


/******************************************************************************
*����:PETER
*����:190308
*����:��������������
*����:��
*******************************************************************************/
static void Key_Handle(void)
{
	if(get_key_data!=0)	//������
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
						TX_DATA = LedOpenData;	//���·���ָ��
						count_level = 100;
				             break;
		       case ExtiLedCloseData:
						key_press = 1;
						TX_DATA = LedCloseData;	//���·���ָ��
						count_level = 15;
					      break;
		        default:
					    break;
		}
	}
	#endif
}

/******************************************************************************
*����:PETER
*����:190308
*����:��������ɨ�躯��
*����:��
*******************************************************************************/
void Key_Scanf(void)
{
	WDTCON|=0x10;
	if(SOCAPI_TouchKeyStatus&0x80) // ��Ҫ���� 2: ������ɨ��һ�ֱ�־���Ƿ���� TouchKeyScan() һ��Ҫ���ݴ˱�־λ�����
      {
		SOCAPI_TouchKeyStatus &= 0x7f;// ��Ҫ���� 3:  �����־λ�� ��Ҫ�ⲿ�����
		get_key_data = TouchKeyScan();// �������ݴ�����
		TouchKeyRestart();// ������һ��ת��
	}
	Key_Handle();
}



















