#ifndef _FUNCTION_H_
#define _FUNCTION_H_


#include "SC92F836xB_C.H"
#include "INIT.H"
#include "UART.h"






void Foot_Led_Cmd(void);           //�ŵ�ָ��
void Cup_Open_Cmd(void);         //��������ָ��
void PushB_Open_Cmd(void);      //�Ƹ�B��ָ��
void PushB_Close_Cmd(void);      //�Ƹ�B�ջ�ָ��
void PushA_Close_Cmd(void);      //�Ƹ�A�ջ�ָ��
void PushA_Open_Cmd(void);                //�Ƹ�A��ָ��
void PushC_Open_Cmd(void);             //�Ƹ�C��ָ��
void PushC_Close_Cmd(void);            //�Ƹ�C�ջ�ָ��
void Push_Reset_Cmd(void);              //�Ƹ˸�λָ��
void Heat_Status(void) ;            //���Ȳ�״ָ̬��
void Mass_Status(void) ;
void Cup_Full_Status(void);




#endif



