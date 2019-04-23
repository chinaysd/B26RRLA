#include "bsp_msg.h"


unsigned int Get_Data;
extern unsigned char Rev_String[REV_BUF_SIZE];
static MSG_STATUS Msg_Status;
void (*GetValuecb)(unsigned char);

extern void Mass_HandleRe(unsigned char Mass_Status);

void Msg_Init(void)
{
	System_Init();
}

static MSG_STATUS Msg_Scanf(void)
{
	 if(Rev_Select())
	 {
	 	Get_Data = (unsigned int)Get_32Bit(Rev_String[2],Rev_String[3]);
		memset(&Rev_String,0,sizeof(Rev_String));
		switch (Get_Data)
		{
			case  Msg_NonValue:             return Msg_NonValue;          break;
			case  Msg_PushAOpen:          return Msg_PushAOpen;        break;
			case  Msg_PushAClose:          return Msg_PushAClose;       break;
			case  Msg_PushBOpen:          return Msg_PushBOpen;        break;
			case  Msg_PushBClose:         return Msg_PushBClose;         break;

                    case  Msg_PushCOpen:          return Msg_PushCOpen;        break;
			case  Msg_PushCClose:          return Msg_PushCClose;       break;
			case  Msg_PushDOpen:          return Msg_PushDOpen;        break;
			case  Msg_PushDClose:         return Msg_PushDClose;         break;
			
			case  Msg_PushRegister:       return Msg_PushRegister;       break;
			case  Msg_WarmOpen:          return Msg_WarmOpen;         break;
			case  Msg_WarmClose:          return Msg_WarmClose;        break;
			case  Msg_Led1Open:            return Msg_Led1Open;          break;
			case  Msg_Led1Close:            return Msg_Led1Close;         break;
			case  Msg_MassOpen:           return Msg_MassOpen;          break;
			case  Msg_MassClose:          return Msg_MassClose;          break;
			case  Msg_PushAStop:          return Msg_PushAStop;          break;
			case  Msg_PushBStop:          return Msg_PushBStop;          break;
			default:                              return Msg_NonValue;           break;
		}
	 }
	 else
	 {
	 	return Msg_PushAStop; 
	 }
}

void Msg_Function(unsigned char GetValue)
{
	if((0 == Key5_Down(Key5_PORT,Key5_PIN))&&(0 == Key6_Down(Key6_PORT,Key6_PIN)))
	{
		if(GetValue == Msg_NonValue)
		{
			PushControl(PUSHA_ADDR,PushStop);
			PushControl(PUSHB_ADDR,PushStop);
			PushControl(PUSHC_ADDR,PushStop);
			PushControl(PUSHD_ADDR,PushStop);
			Reset_EndHandle();
		}
		else if(GetValue == Msg_PushAOpen)
		{
			PushControl(PUSHA_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushAClose)
		{
			PushControl(PUSHA_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushBOpen)
		{
			PushControl(PUSHB_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushBClose)
		{
			PushControl(PUSHB_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushCOpen)
		{
			PushControl(PUSHC_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCClose)
		{
			PushControl(PUSHC_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushDOpen)
		{
			PushControl(PUSHD_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushDClose)
		{
			PushControl(PUSHD_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushRegister)
		{
			PushReset_Control(PushReset);
		}
		else if(GetValue == Msg_WarmOpen)
		{
			Warm_Handle(WARM_OPEN);
		}
		else if(GetValue == Msg_WarmClose)
		{
			Warm_Handle(WARM_CLOSE);
		}
		else if(GetValue == Msg_Led1Open)
		{
			LED1_SET(1);
		}
		else if(GetValue == Msg_Led1Close)
		{
			LED1_SET(0);
		}
		else if(GetValue == Msg_MassOpen)
		{
			Mass_HandleRe(Msg_MassOpen);
		}
		else if(GetValue == Msg_MassClose)
		{
			Mass_HandleRe(Msg_MassClose);
		}
		Reset_BackHandle();
		Mass_BackHandle();
	}
	else if(Key5_Down(Key5_PORT,Key5_PIN)&&Key6_Down(Key6_PORT,Key6_PIN))
	{
		if(GetValue == Msg_NonValue)
		{
			PushControl(PUSHA_ADDR,PushStop);
			PushControl(PUSHB_ADDR,PushStop);
			PushControl(PUSHC_ADDR,PushStop);
			PushControl(PUSHD_ADDR,PushStop);
			Reset_EndHandle();
		}
		else if(GetValue == Msg_PushAOpen)
		{
			PushControl(PUSHA_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushAClose)
		{
			PushControl(PUSHA_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushBOpen)
		{
			PushControl(PUSHB_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushBClose)
		{
			PushControl(PUSHB_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCOpen)
		{
			PushControl(PUSHC_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCClose)
		{
			PushControl(PUSHC_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushDOpen)
		{
			PushControl(PUSHD_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushDClose)
		{
			PushControl(PUSHD_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushRegister)
		{
			PushReset_Control(PushReset);
		}
		else if(GetValue == Msg_WarmOpen)
		{
			Warm_Handle(WARM_OPEN);
		}
		else if(GetValue == Msg_WarmClose)
		{
			Warm_Handle(WARM_CLOSE);
		}
		else if(GetValue == Msg_Led1Open)
		{
			LED1_SET(1);
		}
		else if(GetValue == Msg_Led1Close)
		{
			LED1_SET(0);
		}
		else if(GetValue == Msg_MassOpen)
		{
			Mass_HandleRe(Msg_MassOpen);
		}
		else if(GetValue == Msg_MassClose)
		{
			Mass_HandleRe(Msg_MassClose);
		}
		Reset_BackHandle();
		Mass_BackHandle();
	}
	else if((0 == Key5_Down(Key5_PORT,Key5_PIN))&&Key6_Down(Key6_PORT,Key6_PIN))
	{
		if(GetValue == Msg_NonValue)
		{
			PushControl(PUSHA_ADDR,PushStop);
			PushControl(PUSHB_ADDR,PushStop);
			PushControl(PUSHC_ADDR,PushStop);
			PushControl(PUSHD_ADDR,PushStop);
			Reset_EndHandle();
		}
		else if(GetValue == Msg_PushAOpen)
		{
			PushControl(PUSHA_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushAClose)
		{
			PushControl(PUSHA_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushBOpen)
		{
			PushControl(PUSHB_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushBClose)
		{
			PushControl(PUSHB_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushCOpen)
		{
			PushControl(PUSHC_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCClose)
		{
			PushControl(PUSHC_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushDOpen)
		{
			PushControl(PUSHD_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushDClose)
		{
			PushControl(PUSHD_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushRegister)
		{
			PushReset_Control(PushReset);
		}
		else if(GetValue == Msg_WarmOpen)
		{
			Warm_Handle(WARM_OPEN);
		}
		else if(GetValue == Msg_WarmClose)
		{
			Warm_Handle(WARM_CLOSE);
		}
		else if(GetValue == Msg_Led1Open)
		{
			LED1_SET(1);
		}
		else if(GetValue == Msg_Led1Close)
		{
			LED1_SET(0);
		}
		else if(GetValue == Msg_MassOpen)
		{
			Mass_HandleRe(Msg_MassOpen);
		}
		else if(GetValue == Msg_MassClose)
		{
			Mass_HandleRe(Msg_MassClose);
		}
		Reset_BackHandle();
		Mass_BackHandle();
	}
	else if(Key5_Down(Key5_PORT,Key5_PIN)&&(0== Key6_Down(Key6_PORT,Key6_PIN)))
	{
		if(GetValue == Msg_NonValue)
		{
			PushControl(PUSHA_ADDR,PushStop);
			PushControl(PUSHB_ADDR,PushStop);
			PushControl(PUSHC_ADDR,PushStop);
			PushControl(PUSHD_ADDR,PushStop);
			Reset_EndHandle();
		}
		else if(GetValue == Msg_PushAOpen)
		{
			PushControl(PUSHA_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushAClose)
		{
			PushControl(PUSHA_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushBOpen)
		{
			PushControl(PUSHB_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushBClose)
		{
			PushControl(PUSHB_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCOpen)
		{
			PushControl(PUSHC_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushCClose)
		{
			PushControl(PUSHC_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushDOpen)
		{
			PushControl(PUSHD_ADDR,PushOpen);
		}
		else if(GetValue == Msg_PushDClose)
		{
			PushControl(PUSHD_ADDR,PushClose);
		}
		else if(GetValue == Msg_PushRegister)
		{
			PushReset_Control(PushReset);
		}
		else if(GetValue == Msg_WarmOpen)
		{
			Warm_Handle(WARM_OPEN);
		}
		else if(GetValue == Msg_WarmClose)
		{
			Warm_Handle(WARM_CLOSE);
		}
		else if(GetValue == Msg_Led1Open)
		{
			LED1_SET(1);
		}
		else if(GetValue == Msg_Led1Close)
		{
			LED1_SET(0);
		}
		else if(GetValue == Msg_MassOpen)
		{
			Mass_HandleRe(Msg_MassOpen);
		}
		else if(GetValue == Msg_MassClose)
		{
			Mass_HandleRe(Msg_MassClose);
		}
		Reset_BackHandle();
		Mass_BackHandle();
	}
	
}

void Msg_Register(void (*Cb)(unsigned char))
{
	if(Cb)
	{
		GetValuecb = Cb;
	}
}

void Msg_Poll(void)
{
	Msg_Status = Msg_Scanf();
	if(GetValuecb)
	{
		GetValuecb(Msg_Status);
	}
}




