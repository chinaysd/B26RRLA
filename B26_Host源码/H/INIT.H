#ifndef _init_h_
#define _init_h_

#include "UART.h"

/*********************************************************************/

/*********IO 宏定义***************************************************/
#define   IO_LED_FOOT_LIGHT_PIN     P00//P0.0脚灯
#define   IO_RED_LIGHT_PIN          P25//P2.5红灯
#define   IO_MOTOR_ONE_PIN          P01//P0.1升降马达ONE
#define   IO_MOTOR_TWO_PIN          P02//P0.1升降马达TWO

#define   auto_close_heat_time      (3600)
#define   auto_close_mass_time      (1800)
/*********************************************************************/

/*********IO 处理*****************************************************/
#define   IO_LED_FOOT_LIGHT_ON     IO_LED_FOOT_LIGHT_PIN=1;//脚灯打开
#define   IO_LED_FOOT_LIGHT_OFF    IO_LED_FOOT_LIGHT_PIN=0;//脚灯关闭
 
#define   IO_RED_LIGHT_ON          IO_RED_LIGHT_PIN=1;//红灯打开
#define   IO_RED_LIGHT_OFF         IO_RED_LIGHT_PIN=0;//红灯关闭

#define   IO_MOTOR_ONE_ON          IO_MOTOR_ONE_PIN=1;//升降马达1打开
#define   IO_MOTOR_ONE_OFF         IO_MOTOR_ONE_PIN=0;//升降马达1关闭

#define   IO_MOTOR_TWO_ON          IO_MOTOR_TWO_PIN=1;//升降马达2打开
#define   IO_MOTOR_TWO_OFF         IO_MOTOR_TWO_PIN=0;//升降马达2关闭
/*********************************************************************/

void GPIO_INIT(void);
void Timer0_Init(void);

     
#endif

