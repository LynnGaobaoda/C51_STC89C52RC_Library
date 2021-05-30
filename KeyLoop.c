#include <REGX52.H>
#include "Delay.h"

/**
	C51��ʱ��ɨ�谴��ģ�壬ģ�³���������Ӱ�������� 
	���ߣ�Ching
  */
  

unsigned char Key_KeyNum;	//����λ�û���

/**
  *	@brief	��ȡ�������� ����
  *	@param	��	
  *	@retval	����λ�� 0 ��ʾδ����
  */
unsigned char Key(void)
{
	unsigned char Temp=0;
	Temp=Key_KeyNum;
	Key_KeyNum=0;	//��0��ֹ����null���������ֵ
	return Temp;
}

/**
  *	@brief	��ȡ�������� ��ǰ״̬
  *	@param	��	
  *	@retval	����λ�� 0 ��ʾδ����
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
  *	@brief	ɨ�水��״̬���ڶ�ʱ���ж�������ɨ��ļ�� ��¼��̬����̬��������ģ�ⳤ��
  *	@param	��	
  *	@retval	��
  */
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	//������Чʱ�� ������Чʱ�򣬽���̬����̬�ߵ�
	if(LastState==1 && NowState==0) Key_KeyNum=1;
	if(LastState==2 && NowState==0) Key_KeyNum=2;
	if(LastState==3 && NowState==0) Key_KeyNum=3;
	if(LastState==4 && NowState==0) Key_KeyNum=4;
}

/*��ʱ��ɨ�谴���жϺ���ģ��
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