#include <REGX52.H>

/**
	C51�ⲿ�ж�0
	���ߣ�Ching
  */

/**
  * @brief  ��Ӧ�ⲿ�жϼĴ�������
  * @param  ��
  * @retval ��
  */
void Int0_Init(void)
{
	IT0=1;	//1�½��ش�����0�͵�ƽ����
	IE0=0; //���Բ���
	EX0=1;	//INT0�жϿ���
	EA=1;		//���ж�
	PX0=1; //���ȼ������
}
	
/*
void Int0_Routine(void)	interrupt 0
{
	Num++;
}
*/