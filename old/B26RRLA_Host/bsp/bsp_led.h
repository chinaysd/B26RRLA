#ifndef _BSP_LED_H_
#define _BSP_LED_H_


#include "sc92f836xb_c.h"

#define LED1_PORT      P2
#define LED1_PIN         P25
#define LED1_SET(X)     ((X)?(LED1_PIN=1):(LED1_PIN=0))








void Led_Init(void);

#endif
