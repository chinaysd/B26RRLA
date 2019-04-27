#include "bsp_led.h"




void Led_Init(void)
{
      P2CON |= 0X20;
      P2PH    &= ~0X20;
}



