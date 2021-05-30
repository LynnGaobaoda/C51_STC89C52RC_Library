#include <REGX52.H>

/**
	C51外部中断0
	作者：Ching
  */

/**
  * @brief  响应外部中断寄存器配置
  * @param  无
  * @retval 无
  */
void Int0_Init(void)
{
	IT0=1;	//1下降沿触发，0低电平触发
	IE0=0; //可以不管
	EX0=1;	//INT0中断开关
	EA=1;		//总中断
	PX0=1; //优先级，最高
}
	
/*
void Int0_Routine(void)	interrupt 0
{
	Num++;
}
*/