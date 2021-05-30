#include <REGX52.H>
#include "Delay.h"
#include "key.h"
#include "nixie.h"
#include "timer0.h"
//sbit LED=P2^0;	
sbit DA=P2^1;
unsigned char Counter,Compare;
unsigned char i;
void main()
{
	Compare=5;
	Timer0Init();
	while(1){
		for(i=0;i<100;i++){
			Compare=i;
			Delay(10);
		}
		for(i=100;i>0;i--){
			Compare=i;
			Delay(10);
		}

	}	
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0x9c;
	TH0 = 0xff;	//100us定时定时器
	Counter++;
	Counter%=100;
	if(Counter<Compare) DA=1; 	//1为转
	else	DA=0;
}