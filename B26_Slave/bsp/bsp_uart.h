#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "stm8s.h"


#define   REV_BUF_SIZE     7
#define   Get_32Bit(x,y)     (((x<<8)|y)&0xffff)



















void  Uart_Init(void);
unsigned char UART_Recive(void);


unsigned char Rev_Select(void);
void RevData_Handle(void);

#endif

