#ifndef _BSP_WARM_H_
#define _BSP_WARM_H_


#include "stm8s.h"



typedef enum
{
	WARM_CLOSE,
	WARM_OPEN
}
WARM_STATUS;

#define WARM_PORT        GPIOD
#define WARM_PIN          GPIO_PIN_4
#define WARM_SET(X)      ((X)?(GPIO_WriteHigh(WARM_PORT,WARM_PIN)):(GPIO_WriteLow(WARM_PORT,WARM_PIN)))








unsigned char Warm_Init(void);
unsigned char Warm_Handle(WARM_STATUS Warm_Status);



#endif

