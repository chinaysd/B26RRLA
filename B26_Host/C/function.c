#include "function.h"

#define HEAT_ENABLE    1
#define HEAT_DISABLE   0

#define MASS_ENABLE     1
#define MASS_DISBALE    0

#define CUP_FULL_ENABLE 1
#define CUP_FULL_DISABLE 0


static unsigned char MOTRO_FLAG;
extern unsigned char count_level,lock,TX_DATA;
extern unsigned int TX1_DATA;

unsigned long int MyKey_Buf_Data;

unsigned char key_press,up_flag,down_flag,heat_red_flag,auto_close_heat,auto_close_mass,rev_flag;
	             
unsigned int motro_count0,motro_count1,auto_close_heat_cnt,auto_close_mass_cnt,u16TimeLock;


void Foot_Led_Cmd(void)   //�ŵ�ָ��
{
	if(count_level == 15)
	{
	  count_level = 100;
	   TX_DATA = LedOpenData;    //���·���ָ��
	   TX1_DATA = ExtiLedOpenData;
	}
	else if(count_level == 100)
	{
	  count_level = 15; 
	   TX_DATA = LedCloseData;    //���·���ָ��
	   TX1_DATA = ExtiLedCloseData;
	}
}

void Cup_Open_Cmd(void)          //��������ָ��
{
	if(MOTRO_FLAG == 0)
	{
	  MOTRO_FLAG = 1;
	  P0 &= 0Xf9;
	  P0 |= 1 << 1;
	  motro_count0 = 0;
	  motro_count1 = 0;
	  up_flag = 1;
	  down_flag = 0;
	}
	else
	{
	  MOTRO_FLAG = 0;
	  P0 &= 0Xf9;
	  P0 |= 1 << 2;
	  motro_count0 = 0;
	  motro_count1 = 0;
	  up_flag = 0;
	  down_flag = 1;
	}
}

void PushB_Open_Cmd(void)    //�Ƹ�B��ָ��
{
	TX_DATA = HeadUpData;
}

void PushB_Close_Cmd(void)        //�Ƹ�B�ջ�ָ��
{
	TX_DATA = HeadDownData;
}

void PushA_Close_Cmd(void)       //�Ƹ�A�ջ�ָ��
{
	TX_DATA = CloseData;
}

void PushA_Open_Cmd(void)                //�Ƹ�A��ָ��
{
	TX_DATA = OpenData;
}

void PushC_Open_Cmd(void)              //�Ƹ�C��ָ��
{
	TX_DATA = LumbarOpenData;
}

void PushC_Close_Cmd(void)            //�Ƹ�C�ջ�ָ��
{
	TX_DATA = LumbarCloseData;
}

void Push_Reset_Cmd(void)              //�Ƹ˸�λָ��
{
	TX_DATA = HomeData;
}

#if 0

#if HEAT_DISABLE
void Heat_Status(void)       //���Ȳ�״ָ̬��
{
	if(heat_red_flag == 0)
	{
	  heat_red_flag = 1;
	  IO_RED_LIGHT_ON;
	  auto_close_heat = 1;
	  auto_close_heat_cnt = 0;
	}
	else
	{
	  heat_red_flag = 0;
	  IO_RED_LIGHT_OFF;
	  auto_close_heat = 0;
	  auto_close_heat_cnt = 0;
	}
	TX_DATA = 0x20;
}
#endif

#if MASS_ENABLE
void Mass_Status(void)                //��﹤��״̬
{
	#if 0
	rev_flag = ~rev_flag;
	if(rev_flag)
	{
	   auto_close_mass = 1;
	   auto_close_mass_cnt = 0;
	}
	else
	{
	   auto_close_mass = 0;
	   auto_close_mass_cnt = 0;
	}
	#endif
	TX_DATA = 0x21;
}
#endif

#endif










