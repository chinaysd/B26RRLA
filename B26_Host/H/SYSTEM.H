#ifndef _SYSTEM_H_
#define _SYSTEM_H_



#include "SC92F836xB_C.H"
#include "SensorMethod.h"
#include "UART.H"
#include "INIT.H"
#include "key.h"
#include "TimeOut.h"



#define   OnLine_Time     10//100




void System_Init(void);
void System_Handle(void);

#endif
