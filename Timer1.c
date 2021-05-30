#include <REGX52.H>
//STC_ISP生成定时器	！！！要自己设置中断寄存器	1ms定时
void Timer1_Init(void)		//1??@11.0592MHz
{
	//AUXR &= 0x7F;		//?????12T??	该单片机没有AUXR寄存器
	TMOD &= 0x0F;		//???????
	TMOD |= 0x10;		//???????
	TL1 = 0x9c;		//??????
	TH1 = 0xff;		//??????
	TF1 = 0;		//??TF0??
	TR1 = 1;		//???0????
	
	//中断处理
	ET1=1; 	
	EA=1;
	PT1=0;
}

/*
//定时器中断函数模板
void Timer1_Routine() interrupt 3
{
	static unsigned int T0Count;
	TL1 = 0x18;
	TH1 = 0xFC;	//1ms定时定时器
	T0Count++;
	if(T0Count==1000){	//每1s执行代码
		T0Count=0;
		
	}
}
*/