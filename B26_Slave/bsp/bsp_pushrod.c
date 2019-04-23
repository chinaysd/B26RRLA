#include "bsp_pushrod.h"
#include "TimeOut.h"



TIMEOUT_PARA TimeOut_Para[2];
unsigned char OnlyOneInputFlag,PushResetFlag;


unsigned char Pushrod_Init(void)
{
	 GPIO_Init(PUSHRODA_OPEN_PORT,PUSHRODA_OPEN_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 GPIO_Init(PUSHRODA_CLOSE_PORT,PUSHRODA_CLOSE_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 GPIO_Init(PUSHRODB_OPEN_PORT,PUSHRODB_OPEN_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 GPIO_Init(PUSHRODB_CLOSE_PORT,PUSHRODB_CLOSE_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 GPIO_Init(PUSHRODC_OPEN_PORT,PUSHRODC_OPEN_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 GPIO_Init(PUSHRODC_CLOSE_PORT,PUSHRODC_CLOSE_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	 PushrodA1Set(0);
	 PushrodA2Set(0);
	 PushrodB1Set(0);
	 PushrodB2Set(0);
	 PushrodC1Set(0);
	 PushrodC2Set(0);
	 return 0;
}



void PushControl(unsigned char addr,PUSH_STATUS Push_Status)
{
	if(addr == PUSHA_ADDR)
	{
		if(Push_Status == PushOpen)
		{
			PushrodA1Set(1);
			PushrodA2Set(0);
		}
		else if(Push_Status == PushClose)
		{
			PushrodA2Set(1);
			PushrodA1Set(0);
		}
		else if(Push_Status == PushStop)
		{
			PushrodA2Set(0);
			PushrodA1Set(0);
		}
	}
	else if(addr == PUSHB_ADDR)
	{
		if(Push_Status == PushOpen)
		{
			PushrodB1Set(1);
			PushrodB2Set(0);
		}
		else if(Push_Status == PushClose)
		{
			PushrodB1Set(0);
			PushrodB2Set(1);
		}
		else if(Push_Status == PushStop)
		{
			PushrodB1Set(0);
			PushrodB2Set(0);
		}
	}
	else if(addr == PUSHC_ADDR)
	{
		if(Push_Status == PushOpen)
		{
			PushrodC1Set(1);
			PushrodC2Set(0);
		}
		else if(Push_Status == PushClose)
		{
			PushrodC1Set(0);
			PushrodC2Set(1);
		}
		else if(Push_Status == PushStop)
		{
			PushrodC1Set(0);
			PushrodC2Set(0);
		}
	}
	else if(addr == PUSHD_ADDR)
	{
		if(Push_Status == PushOpen)
		{
			PushrodA1Set(1);
			PushrodA2Set(0);
		}
		else if(Push_Status == PushClose)
		{
			PushrodA1Set(0);
			PushrodA2Set(1);
		}
		else if(Push_Status == PushStop)
		{
			PushrodA1Set(0);
			PushrodA2Set(0);
		}
	}
}

unsigned char PushReset_Control(PUSH_STATUS Push_Status)
{
	if(Push_Status == PushReset)
	{
		PushResetFlag = ResetTrue;
		return 0;
	}
	else if(Push_Status == PushStop)
	{
		PushResetFlag = ResetFalse;
		return 0;
	}
	else
	{
		return 1;
	}
}

void Reset_BackHandle(void)
{
	if(PushResetFlag)
	{
		if(!OnlyOneInputFlag)
		{
			OnlyOneInputFlag = ResetTrue;
			PushrodA2Set(1);
			TimeOut_Record(&TimeOut_Para[0] ,50);//100ms
		}
	       if(TimeOutDet_Check(&TimeOut_Para[0]))
		{
	             PushrodB2Set(1);
		}
	}
}

void Reset_EndHandle(void)
{
	PushrodA2Set(0);
	PushrodB2Set(0);
	OnlyOneInputFlag = ResetFalse;
	PushResetFlag = ResetFalse;
}

