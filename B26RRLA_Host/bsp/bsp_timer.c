#include "bsp_timer.h"
#include "system.h"




void Timer_Init(void)
{
   	TMCON = 0X07;    //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys
	
	//T0设置
	TMOD |= 0x01;                 //0000 0001;Timer0设置工作方式1
	TL0 = (65536 - 10)%256;    //溢出时间：时钟为Fsys，则24000*（1/Fsys）=2ms;
	TH0 = (65536 - 10)/256;
	TR0 = 0;
	ET0 = 1;//定时器0允许
	TR0 = 1;//打开定时器0
	#if 0
	//T1设置
	TMOD |= 0x20;            //0010 0000;Timer1设置工作方式2
	TL1 = 256 - 240;   //溢出时间：时钟为Fsys，则240*（1/Fsys）=20us;
	TH1 = 256 - 240;
	TR1 = 0;
	ET1 = 1;//定时器1允许
	TR1 = 1;//打开定时器1
	
	//T2设置
	T2MOD = 0x00;
	T2CON = 0x00;	 //设置为16位重载寄存器
	RCAP2H = (65536-48000)/256;     //溢出时间：时钟为Fsys，则48000*（1/Fsys）=4ms;
	RCAP2L = (65536-48000)%256;
	TR2 = 0;
	ET2 = 1;//定时器2允许
	TR2 = 1;//打开定时器2  	
	#endif
}


/**************************************************
*函数名称：void timer0/1/2() interrupt 1/3/5
*函数功能：定时器中断产生方波
*入口参数：void
*出口参数：void
**************************************************/
void timer0() interrupt 1    //200us
{
    TL0 = (65536 - 10)%256;
    TH0 = (65536 - 10)/256;
    TimeOutDet_DecHandle();
	//P02 = ~P02;	
	//P25 =!P25;
}

void timer1() interrupt 3
{
	//P03 = ~P03;
}

void Timer2Int(void) interrupt 5
{		
	TF2 = 0;   //溢出清零
    //P04 = ~P04;
}





