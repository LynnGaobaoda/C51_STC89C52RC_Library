#include <REGX52.H>
#include "Delay.h"

/**
	C51独立按键模块，不采用定时器扫描按键，仅模拟按键时序
	作者：Ching
  */

/**
  *	@brief	获取独立按键键码
  *	@param	无	
  *	@retval	按键位置 0 表示未按下
  */

unsigned char Key()
{
	unsigned char KeyNumber=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNumber=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNumber=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=4;}
	return KeyNumber;
}
