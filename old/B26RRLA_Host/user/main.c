#include "system.h"






/**************************************************
*�������ƣ�void Customer_IntoSleepmode_init(void)
*�������ܣ�����͹���ģʽǰ�ĵĳ�ʼ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void Customer_IntoLowPowerMode_Init(void)
{
    //�رպĵ�����裬������͹���
    //P0= P1 = P2 = 0;
}
/**************************************************
*�������ƣ�void Customer_OutoffSleepmode_init(void)
*�������ܣ��˳��͹���ģʽ��ĵĳ�ʼ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void Customer_QuitLowPowerMode_Init(void)
{
   //�ָ��͹���ǰ����
}

void Customer_BTM_Dispose(void)
{
	;
}

void main(void)
{
	System_Init();
	while(1)
	{
		System_Handle();
	}
}


