#include "bsp_timer.h"




void Timer_Init(void)
{
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);//16��Ƶ�����ϼ������������˴����жϣ������
  //�� 1MS �����жϣ��������Ӧ�ü��� 1000 �Σ�1MHZ/1000=1KHZ�����þ��� 1ms��
  TIM1_ARRPreloadConfig(ENABLE);//ʹ���Զ���װ
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);//���ݸ����ж�
  TIM1_Cmd(ENABLE);//����ʱ��
}




