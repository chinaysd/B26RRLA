#include "bsp_btm.h"


void Btm_Test(void)
{
	BTMCON = 0x00;  //不开启
//	BTMCON = 0x80;  //每15.6ms产生一个中断
//	BTMCON = 0x81;	//每31.3ms产生一个中断
//	BTMCON = 0x82;	//每62.5ms产生一个中断
//	BTMCON = 0x83;	//每125ms产生一个中断
//	BTMCON = 0x84;	//每0.25s产生一个中断
//	BTMCON = 0x85;	//每0.5s产生一个中断
//	BTMCON = 0x86;	//每1s产生一个中断
//	BTMCON = 0x87;	//每2s产生一个中断
//	BTMCON = 0x88;	//每4s产生一个中断
       IE1 |= 0x04;       //开启BTM中断
	EA = 1;           //开启总中断
}


#if 1
/*****************************************************
*函数名称：void BTM_Int(void) interrupt 9
*函数功能：中断函数
*入口参数：void
*出口参数：void
*****************************************************/
void BTM_Int1_Test(void) interrupt 9
{
	if(!(BTMCON&0X40))		//中断标志位判断
	{
		//P25=!P25;
	}
}

#endif


