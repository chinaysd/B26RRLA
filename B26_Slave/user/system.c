#include "system.h"


void System_Init(void)
{
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	TimeOutDet_Init();
	Pushrod_Init();
	Led_Init();
	Warm_Init();
	Timer_Init();
	Uart_Init();
	Mass_Init();
	Key_Init();
	Mass_Deinit();
	Msg_Register(Msg_Function);
	enableInterrupts(); //¿ªÆôÖÐ¶Ï
}

#if 0
MSG_STATUS System_Handle(void)
{
	 
}
#endif




