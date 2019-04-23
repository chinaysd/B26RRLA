#include "bsp_led.h"





void Led_Init(void)
{
     GPIO_Init(LED1_PORT,LED1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}



