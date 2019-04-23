#include "bsp_key.h"


void Key_Init(void)
{
	GPIO_Init(Key5_PORT,Key5_PIN,GPIO_MODE_IN_PU_NO_IT);
       GPIO_Init(Key6_PORT,Key6_PIN,GPIO_MODE_IN_PU_NO_IT);
}


unsigned char Key5_Down(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
   if(GPIO_ReadInputPin(GPIOx,GPIO_Pin) == 0){
      return 1;
   }else{
      return 0;
   }
}

unsigned char Key6_Down(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
   if(GPIO_ReadInputPin(GPIOx,GPIO_Pin) == 0){
   return 1;
   }else{
   return 0;
   }

}



