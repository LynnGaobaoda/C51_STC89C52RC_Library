#include <REGX52.H>
#include "Timer1.h"

/**
	C51�������ģ��
	����PWM �źŵ���
	�Լ����ö�ʱ��100us
	���ߣ�Ching
  */

//���Ŷ���
sbit Motor=P1^0;
//pwm����
unsigned char Counter,Compare;

/**
  * @brief  �����ʼ�������ö�ʱ��1����pwm��
  * @param  ��
  * @retval ��
  */
void Motor_Init(void)
{
	Timer1_Init();
}

/**
  * @brief  ���õ���ٶ�
  * @param  �ٶȣ�ռ�ձ�
  * @retval ��
  */
void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}

/**
  * @brief  ����pwm����ʱ���жϺ���
  * @param  ��
  * @retval ��
  */
void Timer1_Routine() interrupt 3
{
	TL1 = 0x9c;
	TH1 = 0xff;	//100us��ʱ��ʱ��
	Counter++;
	Counter%=100;
	if(Counter<Compare) Motor=1; 	//1Ϊת
	else	Motor=0;
}