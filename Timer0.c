#include <REGX52.H>

/**
	C51定时器0触发中断模块
	STC_ISP生成定时器	！！！要自己设置中断寄存器	1ms定时
	作者：Ching
  */

/**
  * @brief  定时器0初始化
  * @param  无
  * @retval 无
  */
void Timer0Init(void)		//1@11.0592MHz
{
	//AUXR &= 0x7F;		//	该单片机没有AUXR寄存器
	TMOD &= 0xF0;		//保存除定时器以外的其他配置
	TMOD |= 0x01;		//配置定时器
	TL0 = 0x66;			//定时器计数初值低8位
	TH0 = 0xFC;			//定时器计数初值高8位
	TF0 = 0;			//清除TF0标志 定时器计数 达到最大值 TF标志位置1
	TR0 = 1;			//开始计时
	
	
	//中断处理
	ET0=1; 	
	EA=1;
	PT0=0;
}

/*
//定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;
	TH0 = 0xFC;	//1ms定时定时器
	T0Count++;
	if(T0Count==1000){	//每1s执行代码
		T0Count=0;
		
	}
}
*/