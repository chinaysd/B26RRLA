#ifndef _BSP_PUSHROD_H_
#define _BSP_PUSHROD_H_

#include "stm8s.h"


#define PUSHRODA_OPEN_PORT         GPIOC
#define PUSHRODA_OPEN_PIN            GPIO_PIN_4
#define PushrodA1Set(x)                      ((x)?(GPIO_WriteHigh(PUSHRODA_OPEN_PORT,PUSHRODA_OPEN_PIN)):(GPIO_WriteLow(PUSHRODA_OPEN_PORT,PUSHRODA_OPEN_PIN)))                   

#define PUSHRODA_CLOSE_PORT        GPIOC
#define PUSHRODA_CLOSE_PIN           GPIO_PIN_5
#define PushrodA2Set(x)                    ((x)?(GPIO_WriteHigh(PUSHRODA_CLOSE_PORT,PUSHRODA_CLOSE_PIN)):(GPIO_WriteLow(PUSHRODA_CLOSE_PORT,PUSHRODA_CLOSE_PIN)))                    


#define PUSHRODB_OPEN_PORT         GPIOC
#define PUSHRODB_OPEN_PIN            GPIO_PIN_6
#define PushrodB1Set(x)                    ((x)?(GPIO_WriteHigh(PUSHRODB_OPEN_PORT,PUSHRODB_OPEN_PIN)):(GPIO_WriteLow(PUSHRODB_OPEN_PORT,PUSHRODB_OPEN_PIN)))                     

#define PUSHRODB_CLOSE_PORT        GPIOC
#define PUSHRODB_CLOSE_PIN          GPIO_PIN_7
#define PushrodB2Set(x)                    ((x)?(GPIO_WriteHigh(PUSHRODB_CLOSE_PORT,PUSHRODB_CLOSE_PIN)):(GPIO_WriteLow(PUSHRODB_CLOSE_PORT,PUSHRODB_CLOSE_PIN)))                    

#define PUSHRODC_OPEN_PORT         GPIOC
#define PUSHRODC_OPEN_PIN           GPIO_PIN_3
#define PushrodC1Set(x)                   ((x)?(GPIO_WriteHigh(PUSHRODC_OPEN_PORT,PUSHRODC_OPEN_PIN)):(GPIO_WriteLow(PUSHRODC_OPEN_PORT,PUSHRODC_OPEN_PIN)))

#define PUSHRODC_CLOSE_PORT       GPIOD
#define PUSHRODC_CLOSE_PIN          GPIO_PIN_5
#define PushrodC2Set(x)                   ((x)?(GPIO_WriteHigh(PUSHRODC_CLOSE_PORT,PUSHRODC_CLOSE_PIN)):(GPIO_WriteLow(PUSHRODC_CLOSE_PORT,PUSHRODC_CLOSE_PIN)))

#define PUSHA_ADDR    0X01
#define PUSHB_ADDR    0X02
#define PUSHC_ADDR    0X03
#define PUSHD_ADDR    0X04

#define ResetTrue       1
#define ResetFalse      0

typedef enum
{
	PushStop,
	PushOpen,
	PushClose,
	PushReset
}
PUSH_STATUS;



unsigned char Pushrod_Init(void);
void PushControl(unsigned char addr,PUSH_STATUS Push_Status);
unsigned char PushReset_Control(PUSH_STATUS Push_Status);
void Reset_BackHandle(void);
void Reset_EndHandle(void);


#endif



