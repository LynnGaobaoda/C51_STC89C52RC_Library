#include <REGX52.H>
#include "delay.h"

/**
	C51����ܶ�ʱ��ɨ�蹦��
	���ߣ�Ching
  */
  
//ÿ���������ʾ����Ϣ�����֣���0Ԥ��λ��
unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10,}; //10= Nixie_Arr[10]	//��ʼ��ʲô������ʾ

//��װ��ʾ  �ĸ�λ���ϵ��ĸ����ֵĺ���
unsigned char Nixie_Arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40}; //10��null 11��- 


/**
  * @brief  �ĸ��������ʾ�ĸ������ص� Nixie_Buf
  * @param  Location�������λ��
  * @param  Number ��ʵ������
  * @retval ��
  */
void Nixie_SetBuf(unsigned char Location, Number)
{
		Nixie_Buf[Location]=Number;
}

/**
  * @brief  �ĸ��������ʾ�ĸ���
  * @param  Location�������λ��
  * @param  Number ��ʵ������
  * @retval ��
  */
void Nixie_Scan(unsigned char Location, Number)
{
		P0=0x00;//��Ӱ��λѡ ��ѡ �����㣩λѡ ��ѡ
		switch(Location){	//�������ʾ��λ��
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
	
	//Delay(1);	//��ʾ1ms

}
/**
  * @brief  ��ʱ��ɨ�������
  * @param ��
  * @retval ��
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
	TH0 = 0xFC;	//1ms��ʱ��ʱ��
	T0Count1++;
	T0Count2++;
	T0Count3++;
	if(T0Count1==20){	//ÿ20msɨ��һ�ΰ���
		T0Count1=0;
		Key_Loop();	//��϶�һ��Ҫ�ߣ����澡����Ҫ�к�ʱ����
	}
	
	if(T0Count2==2){	//ÿ2msɨ��һ�������
		T0Count2=0;
		Nixie_Loop();
	}
	if(T0Count3==10){	//ÿ10msɨ��һ�μ�����
		T0Count3=0;
		Sec_Loop();
	}
}
*/