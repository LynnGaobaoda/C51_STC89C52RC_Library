#include <REGX52.H>
#include "delay.h"

/**
	C51数码管模块 
	共阴极数码管
	无定时器扫描功能 
	阴极与74HC138译码器相连
	阳极与74HC245 数据缓冲器相连
	作者：Ching
  */
  
 
//封装显示  哪个位置上的哪个数字的函数	如：Nixie_Arr[2] 表示显示数字2 0x4F表示 数码管abcdefgh的选择
unsigned char Nixie_Arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

/**
  * @brief  在数码管上显示数字
  * @param  Location，第几个数码管1-8
  * @param	Number要显示的数字
  * @retval 无
  */
void Nixie(unsigned char Location, Number)
{
	switch(Location){	//数码管显示的位置 38译码
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
	
	Delay(1);	//显示1ms
	P0=0x00;//消影：位选 段选 （清零）位选 段选
}