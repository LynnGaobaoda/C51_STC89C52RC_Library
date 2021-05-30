#include <REGX52.H>
#include "intrins.h"

/**
	C51蜂鸣器模块_报警器:1000Hz
	作者：Ching
  */

//引脚定义
sbit Buzzer=P1^5;	//蜂鸣器端口

/**
  * @brief  //内部函数 延时500ms
  * @param  无
  * @retval 无
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief  蜂鸣器以1000Hz 响 ms毫秒
  * @param  ms 响时长
  * @retval 无
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++){
		Buzzer=!Buzzer;
		Buzzer_Delay500us();	//1s 2000次反转即1000Hz
		}
}
