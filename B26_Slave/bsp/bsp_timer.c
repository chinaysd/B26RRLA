#include "bsp_timer.h"




void Timer_Init(void)
{
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);//16分频，向上计数，计数完了触发中断，如果想
  //再 1MS 触发中断，则计数器应该计数 1000 次，1MHZ/1000=1KHZ，正好就是 1ms。
  TIM1_ARRPreloadConfig(ENABLE);//使能自动重装
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);//数据更新中断
  TIM1_Cmd(ENABLE);//开定时器
}




