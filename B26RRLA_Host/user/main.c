#include "system.h"






/**************************************************
*函数名称：void Customer_IntoSleepmode_init(void)
*函数功能：进入低功耗模式前的的初始化
*入口参数：void
*出口参数：void  
**************************************************/
void Customer_IntoLowPowerMode_Init(void)
{
    //关闭耗电的外设，保持最低功耗
    //P0= P1 = P2 = 0;
}
/**************************************************
*函数名称：void Customer_OutoffSleepmode_init(void)
*函数功能：退出低功耗模式后的的初始化
*入口参数：void
*出口参数：void  
**************************************************/
void Customer_QuitLowPowerMode_Init(void)
{
   //恢复低功耗前设置
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


