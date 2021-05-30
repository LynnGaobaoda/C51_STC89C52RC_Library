#include <REGX52.H>

/**
	C51��ʱ��0�����ж�ģ��
	STC_ISP���ɶ�ʱ��	������Ҫ�Լ������жϼĴ���	1ms��ʱ
	���ߣ�Ching
  */

/**
  * @brief  ��ʱ��0��ʼ��
  * @param  ��
  * @retval ��
  */
void Timer0Init(void)		//1@11.0592MHz
{
	//AUXR &= 0x7F;		//	�õ�Ƭ��û��AUXR�Ĵ���
	TMOD &= 0xF0;		//�������ʱ���������������
	TMOD |= 0x01;		//���ö�ʱ��
	TL0 = 0x66;			//��ʱ��������ֵ��8λ
	TH0 = 0xFC;			//��ʱ��������ֵ��8λ
	TF0 = 0;			//���TF0��־ ��ʱ������ �ﵽ���ֵ TF��־λ��1
	TR0 = 1;			//��ʼ��ʱ
	
	
	//�жϴ���
	ET0=1; 	
	EA=1;
	PT0=0;
}

/*
//��ʱ���жϺ���ģ��
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;
	TH0 = 0xFC;	//1ms��ʱ��ʱ��
	T0Count++;
	if(T0Count==1000){	//ÿ1sִ�д���
		T0Count=0;
		
	}
}
*/