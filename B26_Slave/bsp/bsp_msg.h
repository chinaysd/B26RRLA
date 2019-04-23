#ifndef _BSP_MSG_H_
#define _BSP_MSG_H_

#include "stm8s.h"
#include "system.h"




typedef enum
{
	Msg_NonValue,
       Msg_PushAOpen,
       Msg_PushAClose,
       Msg_PushBOpen,
       Msg_PushBClose,
       Msg_PushCOpen,
       Msg_PushCClose,
       Msg_PushDOpen,
       Msg_PushDClose,
       Msg_PushRegister,
       Msg_WarmOpen,
       Msg_WarmClose,
       //Msg_Led1Close,
       Msg_MassOpen,
       Msg_MassClose,
       Msg_PushAStop,
       Msg_PushBStop,
       Msg_Led1Open = 0X11,
       Msg_Led1Close = 0X22
       
}
MSG_STATUS;





void Msg_Init(void);
void Msg_Function(unsigned char GetValue);
void Msg_Register(void (*Cb)(unsigned char));
void Msg_Poll(void);



#endif

