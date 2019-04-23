#ifndef _FUNCTION_H_
#define _FUNCTION_H_


#include "SC92F836xB_C.H"
#include "INIT.H"
#include "UART.h"






void Foot_Led_Cmd(void);           //脚灯指令
void Cup_Open_Cmd(void);         //杯子升降指令
void PushB_Open_Cmd(void);      //推杆B打开指令
void PushB_Close_Cmd(void);      //推杆B收回指令
void PushA_Close_Cmd(void);      //推杆A收回指令
void PushA_Open_Cmd(void);                //推杆A打开指令
void PushC_Open_Cmd(void);             //推杆C打开指令
void PushC_Close_Cmd(void);            //推杆C收回指令
void Push_Reset_Cmd(void);              //推杆复位指令
void Heat_Status(void) ;            //发热布状态指令
void Mass_Status(void) ;
void Cup_Full_Status(void);




#endif



