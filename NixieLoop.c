#include <REGX52.H>
#include "delay.h"

/**
	C51数码管定时器扫描功能
	作者：Ching
  */
  
//每个数码管显示的信息（数字），0预留位置
unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10,}; //10= Nixie_Arr[10]	//初始化什么都不显示

//封装显示  哪个位置上的哪个数字的函数
unsigned char Nixie_Arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40}; //10：null 11：- 


/**
  * @brief  哪个数码管显示哪个数加载到 Nixie_Buf
  * @param  Location，数码管位置
  * @param  Number 现实的数字
  * @retval 无
  */
void Nixie_SetBuf(unsigned char Location, Number)
{
		Nixie_Buf[Location]=Number;
}

/**
  * @brief  哪个数码管显示哪个数
  * @param  Location，数码管位置
  * @param  Number 现实的数字
  * @retval 无
  */
void Nixie_Scan(unsigned char Location, Number)
{
		P0=0x00;//消影：位选 段选 （清零）位选 段选
		switch(Location){	//数码管显示的位置
		case 1:P2_4=1; P2_3=1; P2_2=1;break;
		case 2:P2_4=1; P2_3=1; P2_2=0;break;
		case 3:P2_4=1; P2_3=0; P2_2=1;break;
		case 4:P2_4=1; P2_3=0; P2_2=0;break;
		case 5:P2_4=0; P2_3=1; P2_2=1;break;
		case 6:P2_4=0; P2_3=1; P2_2=0;break;
		case 7:P2_4=0; P2_3=0; P2_2=1;break;
		case 8:P2_4=0; P2_3=0; P2_2=0;break;
		

	}
	//P0 = 0x7D; //test code
	P0=Nixie_Arr[Number];
	
	//Delay(1);	//显示1ms

}
/**
  * @brief  定时器扫描数码管
  * @param 无
  * @retval 无
  */
void Nixie_Loop()
{
	static unsigned char i=1;
	Nixie_Scan(i,Nixie_Buf[i]);
	i++;
	if(i>=9) i=1;
}

/*
void Sec_Loop(void)
{
	if(RunFlag){
		MiniSec++;
		if(MiniSec>=100){
			MiniSec=0;
			Sec++;
			if(Sec>=60){
				Sec=0;
				Min++;
				if(Min>=60){
					Min=0;
				}
			}
		}
	}

}

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