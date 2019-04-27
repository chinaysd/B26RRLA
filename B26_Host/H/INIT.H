#ifndef _init_h_
#define _init_h_

#include "UART.h"

/*********************************************************************/

/*********IO �궨��***************************************************/
#define   IO_LED_FOOT_LIGHT_PIN     P00//P0.0�ŵ�
#define   IO_RED_LIGHT_PIN          P25//P2.5���
#define   IO_MOTOR_ONE_PIN          P01//P0.1��������ONE
#define   IO_MOTOR_TWO_PIN          P02//P0.1��������TWO

#define   auto_close_heat_time      (3600)
#define   auto_close_mass_time      (1800)
/*********************************************************************/

/*********IO ����*****************************************************/
#define   IO_LED_FOOT_LIGHT_ON     IO_LED_FOOT_LIGHT_PIN=1;//�ŵƴ�
#define   IO_LED_FOOT_LIGHT_OFF    IO_LED_FOOT_LIGHT_PIN=0;//�ŵƹر�
 
#define   IO_RED_LIGHT_ON          IO_RED_LIGHT_PIN=1;//��ƴ�
#define   IO_RED_LIGHT_OFF         IO_RED_LIGHT_PIN=0;//��ƹر�

#define   IO_MOTOR_ONE_ON          IO_MOTOR_ONE_PIN=1;//��������1��
#define   IO_MOTOR_ONE_OFF         IO_MOTOR_ONE_PIN=0;//��������1�ر�

#define   IO_MOTOR_TWO_ON          IO_MOTOR_TWO_PIN=1;//��������2��
#define   IO_MOTOR_TWO_OFF         IO_MOTOR_TWO_PIN=0;//��������2�ر�
/*********************************************************************/

void GPIO_INIT(void);
void Timer0_Init(void);

     
#endif
