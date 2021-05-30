#include <REGX52.H>
#include "Timer1.h"

/**
	C51步进电机模块
	采用PWM 信号调速
	自己配置定时器100us
	作者：Ching
  */

//引脚定义
sbit Motor=P1^0;
//pwm变量
unsigned char Counter,Compare;

/**
  * @brief  电机初始化，采用定时器1产生pwm波
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
	Timer1_Init();
}

/**
  * @brief  设置电机速度
  * @param  速度：占空比
  * @retval 无
  */
void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}

/**
  * @brief  发射pwm波定时器中断函数
  * @param  无
  * @retval 无
  */
void Timer1_Routine() interrupt 3
{
	TL1 = 0x9c;
	TH1 = 0xff;	//100us定时定时器
	Counter++;
	Counter%=100;
	if(Counter<Compare) Motor=1; 	//1为转
	else	Motor=0;
}