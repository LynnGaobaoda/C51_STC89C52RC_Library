#include <REGX52.H>
#include "intrins.h"

/**
	C51������ģ��_������:1000Hz
	���ߣ�Ching
  */

//���Ŷ���
sbit Buzzer=P1^5;	//�������˿�

/**
  * @brief  //�ڲ����� ��ʱ500ms
  * @param  ��
  * @retval ��
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief  ��������1000Hz �� ms����
  * @param  ms ��ʱ��
  * @retval ��
  */
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++){
		Buzzer=!Buzzer;
		Buzzer_Delay500us();	//1s 2000�η�ת��1000Hz
		}
}
