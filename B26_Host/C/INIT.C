#include "INIT.H"
#include "SC92F836xB_C.H"
#include "bsp_io_data.h"
#include "TimeOut.h"

unsigned char count_250us_time,count_level,lock = 1;
unsigned int   count_1ms_time;
extern unsigned int motro_count0,
	                     motro_count1,
	                     auto_close_heat_cnt,
	                     auto_close_mass_cnt,
	                     u16TimeLock;

extern unsigned char TX_DATA;

extern unsigned char up_flag,
	                       down_flag,
	                       auto_close_heat,
	                       auto_close_mass;

extern unsigned long MyKey_Buf_Data;



void GPIO_INIT(void)
{
  P0CON |= 7 << 0;			   //����P00,P01,P02Ϊǿ����IO
  P2CON |= 1 << 5;		       //����P25Ϊǿ����IO

  IO_LED_FOOT_LIGHT_OFF;	     //�ŵƹر�
  IO_RED_LIGHT_OFF;           //��ƹر�
  IO_MOTOR_ONE_OFF;			 //��������1�ر�
  IO_MOTOR_TWO_OFF;			 //��������2�ر�
}

void Timer0_Init(void)
{ 

	TMCON = 0X07;    //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys
	
	//T0����
	TMOD |= 0x01;                 //0000 0001;Timer0���ù�����ʽ1
	TL0 = (65536 - 350)%256;    //���ʱ�䣺ʱ��ΪFsys����24000*��1/Fsys��=2ms;
	TH0 = (65536 - 350)/256;
	TR0 = 0;
	ET0 = 1;//��ʱ��0����
	TR0 = 1;//�򿪶�ʱ��0
}

#if 1
void timer0() interrupt 1         //2MS
{
    TL0 = (65536 - 350)%256;     //1090      2080
    TH0 = (65536 - 350)/256;     //100us     2080
    #if 1
    TimeOutDet_DecHandle();
        count_250us_time++;
	 if(count_250us_time > 100)
	 {
	   count_250us_time = 0;
	 }
	 if(count_250us_time >= count_level)
	 {
	   IO_LED_FOOT_LIGHT_OFF;
	 }
	 else
	 {
	   IO_LED_FOOT_LIGHT_ON;
	 }	
	 /*****************************������ʱ��************************/
     if((0X4000 == MyKey_Buf_Data)&&(1 == lock))
	 {
	   MyKey_Buf_Data = 0x1111;
	   if(u16TimeLock < 1000)
	   {
	      u16TimeLock++;
	   }
	   else
	   {
	         u16TimeLock = 0;
		  IO_RED_LIGHT_ON;
		  lock = 0;
	   }
	 }
	 else if((0X4000 == MyKey_Buf_Data)&&(0 == lock))
	 {
	   MyKey_Buf_Data = 0x1111;
	   if(u16TimeLock < 1000)
	   {
	      u16TimeLock++;
	   }
	   else
	   {
	        u16TimeLock = 0;
		  IO_RED_LIGHT_OFF;
		  lock = 1;
	   }
	 }

/***************************************************************/
	if(up_flag)
	{
	   motro_count0++;
	   if(motro_count0>1500)
	   {
	      motro_count0 = 0;
		  up_flag = 0;
		  down_flag = 1;
		  P0 &= 0Xf9;
	   }
	}
	if(down_flag)
	{
	   motro_count1++;
	   if(motro_count1>1500)
	   {
	     motro_count1 = 0;
		 up_flag = 1;
		 down_flag = 0;
		 P0 &= 0Xf9;
	   }
	}
	  if(auto_close_mass)
	  {
	    if(auto_close_mass_cnt++ > auto_close_mass_time)//1800
		{
		   auto_close_mass_cnt = 0;
		   auto_close_mass = 0;
		   //��������ر�ָ��
		   TX_DATA = 0x21;

		}
	  }
	  if(auto_close_heat)
	  {
	    if(auto_close_heat_cnt++ > auto_close_heat_time)//3600
		{
		   auto_close_heat_cnt = 0;
		   auto_close_heat = 0;
		   //���ͷ��Ȳ��ر�ָ��
		   IO_RED_LIGHT_OFF;
		   TX_DATA = 0x20;
		}
	  }
	 #endif
}

#endif
void Timer2Int(void) interrupt 5
{		
	TF2 = 0;   //�������
	
}
void timer1() interrupt 3
{
	//P03 = ~P03;
}



