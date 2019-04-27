#ifndef _SYSTEM_H_
#define _SYSTEM_H_




#include "sc92f836xb_c.h"
#include "SensorMethod.h"
#include "bsp_led.h"
#include "bsp_timer.h"
#include "TimeOut.h"
#include "bsp_uart.h"
#include "bsp_btm.h"
#include "intrins.h"
#include "bsp_key.h"





















void System_Init(void);
void System_Handle(void);


#endif

