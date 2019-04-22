#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "sc92f836xb_c.h"
#include "SensorMethod.h"



#define TK3_VALUE      0X00000008
#define TK4_VALUE      0X00000010
#define TK5_VALUE      0X00000020
#define TK12_VALUE    0X00001000
#define TK14_VALUE    0X00004000
#define TK15_VALUE    0X00008000
#define TK18_VALUE    0X00040000
#define TK19_VALUE    0X00080000

#define LightData        0x01
#define CupData          0x02
#define HomeData       0x03
#define OpenData        0x04
#define CloseData       0x05
#define HeadUpData    0x06
#define HeadDownData  0x07
#define LockData           0x08
















void Key_Init(void);
void Key_Handle(void);

#endif

