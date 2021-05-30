#include <REGX52.H>
#include "Delay.h"

/**
	C51定时器扫描按键模板，模仿长按按键不影响主程序 
	作者：Ching
  */
  

unsigned char Key_KeyNum;	//按键位置缓存

/**
  *	@brief	获取独立按键 键码
  *	@param	无	
  *	@retval	按键位置 0 表示未按下
  */
unsigned char Key(void)
{
	unsigned char Temp=0;
	Temp=Key_KeyNum;
	Key_KeyNum=0;	//清0防止返回null或其他随机值
	return Temp;
}

/**
  *	@brief	获取独立按键 当前状态
  *	@param	无	
  *	@retval	按键位置 0 表示未按下
  */
unsigned char Key_GetState()
{
	unsigned char KeyState=0;
	if(P3_1==0){KeyState=1;}
	if(P3_0==0){KeyState=2;}
	if(P3_2==0){KeyState=3;}
	if(P3_3==0){KeyState=4;}
	return KeyState;
}

/**
  *	@brief	扫面按键状态，在定时器中断中设置扫描的间隔 记录往态，现态，消抖，模拟长按
  *	@param	无	
  *	@retval	无
  */
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	//松手有效时序 按下有效时序，将往态，现态颠倒
	if(LastState==1 && NowState==0) Key_KeyNum=1;
	if(LastState==2 && NowState==0) Key_KeyNum=2;
	if(LastState==3 && NowState==0) Key_KeyNum=3;
	if(LastState==4 && NowState==0) Key_KeyNum=4;
}

/*定时器扫描按键中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;
	TH0 = 0xFC;	//1ms定时定时器
	T0Count1++;
	T0Count2++;
	T0Count3++;
	if(T0Count1==20){	//每20ms扫描一次按键
		T0Count1=0;
		Key_Loop();	//耦合度一定要高，里面尽量不要有耗时操作
	}
	
	if(T0Count2==2){	//每2ms扫描一次数码管
		T0Count2=0;
		Nixie_Loop();
	}
	if(T0Count3==10){	//每10ms扫描一次计数器
		T0Count3=0;
		Sec_Loop();
	}
}

*/