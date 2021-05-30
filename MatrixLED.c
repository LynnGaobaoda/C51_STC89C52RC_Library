#include <REGX52.H>
#include "Delay.h"


/**
	LED������ģ�� ���ƹ����������
	ÿһ�е�����ͨ��74HC595 ��λоƬ���� ��ת��
	���ߣ�Ching
  */

#define MATRIX_LED_PORT	P0

//���Ŷ���
sbit RCK=P3^5; // ���� =P3_5 RCLK
sbit SCK=P3^6;	//SRCLK
sbit SER=P3^4;	//SER

/**
  * @brief  ����LED��ʼ��������74HC595�����ź�
  * @param  ��
  * @retval ��
  */
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}

/**
  * @brief  74HC595д������
  * @param  Byte д���һ���ֽ�
  * @retval	��
  */
void _74HC595_writeByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		SER=Byte&(0x80>>i);	//��0��1 ȡ��Byte���λ
		SCK=1;	//������д��
		SCK=0;
	}
	RCK=1; 	//����������74HC595����Ĵ���
	RCK=0;
}

/**
  * @brief  LED�е�������ʾ
  * @param  Column ѡ������
  * @param  Data һ������
  * @retval	��
  */
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
	_74HC595_writeByte(Data);	//һ�е�����
	MATRIX_LED_PORT=~(0x80>>Column);	//ѡ����
	Delay(1);
	MATRIX_LED_PORT=0xFF;	//��Ӱ
}

