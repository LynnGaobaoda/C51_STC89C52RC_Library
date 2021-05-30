#include <REGX52.H>
#include "delay.h"

/**
	C51�����ģ�� 
	�����������
	�޶�ʱ��ɨ�蹦�� 
	������74HC138����������
	������74HC245 ���ݻ���������
	���ߣ�Ching
  */
  
 
//��װ��ʾ  �ĸ�λ���ϵ��ĸ����ֵĺ���	�磺Nixie_Arr[2] ��ʾ��ʾ����2 0x4F��ʾ �����abcdefgh��ѡ��
unsigned char Nixie_Arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

/**
  * @brief  �����������ʾ����
  * @param  Location���ڼ��������1-8
  * @param	NumberҪ��ʾ������
  * @retval ��
  */
void Nixie(unsigned char Location, Number)
{
	switch(Location){	//�������ʾ��λ�� 38����
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
	
	Delay(1);	//��ʾ1ms
	P0=0x00;//��Ӱ��λѡ ��ѡ �����㣩λѡ ��ѡ
}