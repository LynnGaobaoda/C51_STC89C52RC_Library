#include <REGX52.H>
//STC_ISP���ɶ�ʱ��	������Ҫ�Լ������жϼĴ���	1ms��ʱ
void Timer1_Init(void)		//1??@11.0592MHz
{
	//AUXR &= 0x7F;		//?????12T??	�õ�Ƭ��û��AUXR�Ĵ���
	TMOD &= 0x0F;		//???????
	TMOD |= 0x10;		//???????
	TL1 = 0x9c;		//??????
	TH1 = 0xff;		//??????
	TF1 = 0;		//??TF0??
	TR1 = 1;		//???0????
	
	//�жϴ���
	ET1=1; 	
	EA=1;
	PT1=0;
}

/*
//��ʱ���жϺ���ģ��
void Timer1_Routine() interrupt 3
{
	static unsigned int T0Count;
	TL1 = 0x18;
	TH1 = 0xFC;	//1ms��ʱ��ʱ��
	T0Count++;
	if(T0Count==1000){	//ÿ1sִ�д���
		T0Count=0;
		
	}
}
*/