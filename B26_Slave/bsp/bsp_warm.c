#include "bsp_warm.h"


unsigned char Warm_Init(void)
{
      GPIO_Init(WARM_PORT,WARM_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
	return 0;
}

unsigned char Warm_Handle(WARM_STATUS Warm_Status)
{
	if(Warm_Status == WARM_CLOSE)
	{
		WARM_SET(0);
		return 0;
	}
	else if(Warm_Status == WARM_OPEN)
	{
             WARM_SET(1);
		return 0;
	}
	else
	{
		return 1;
	}
}







