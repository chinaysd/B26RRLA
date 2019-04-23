#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "stm8s.h"

#define LED1_PORT    GPIOA
#define LED1_PIN      GPIO_PIN_3
#define LED1_SET(X)  ((X)?(GPIO_WriteHigh(LED1_PORT,LED1_PIN)):(GPIO_WriteLow(LED1_PORT,LED1_PIN)))




void Led_Init(void);


#endif



