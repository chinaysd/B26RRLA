#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "stm8s.h"

#define  Key5_PIN        GPIO_PIN_3
#define  Key5_PORT     GPIOD

#define  Key6_PIN        GPIO_PIN_2
#define  Key6_PORT     GPIOD




















void Key_Init(void);
unsigned char Key5_Down(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
unsigned char Key6_Down(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin);

#endif

