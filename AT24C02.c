#include "I2C.h"
#include <REGX52.H>

/**
	AT24C02 �洢����ȫ�ƣ� ATMTC.98 24C02N SU27 D
	����I2C���ݴ���Э��
	���ߣ�Ching
  */

#define AT24C02_ADDRESS	0xA0 //д���ݿ����֣������ַ�� �����ݿ�����| 0x01���� ���AT24C02оƬ�ֲ�

/**
  *	@brief	AT24C02�洢оƬд���� ����֡
  *	@param	WordAddress Ҫд����������ڵ�ַ	
  *	@retval	��
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)	//AT24C02д������ʱ��
{
	//��һ֡ ���� д���ݿ����֣������ַ��
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);	
	I2C_ReceiveAck();
	//if(Ack==0) P2=0x00;	//LCD���� �����Ƿ�Ӧ��
	
	//�ڶ�֡ ���� �ֵ�ַ�����ݵ�ַ��
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	
	//����֡ ���� ����
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();	//����ע�ͣ���ϸ�����ϸ�ʽ����֡
}

/**
  *	@brief	AT24C02�洢оƬ������ ����֡
  *	@param	WordAddress Ҫ��ȡ���������ڵ�ַ	
  *	@retval	WordAddress���洢��һ���ֽ�
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)//AT24C02��������ʱ��
{
	unsigned char Data;
	
	//��һ֡ ���� д���ݿ����֣������ַ��
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);	
	I2C_ReceiveAck();
	
	//�ڶ�֡ ���� �ֵ�ַ�����ݵ�ַ��
	I2C_SendByte(WordAddress);	
	I2C_ReceiveAck();
	
	//����֡ ���� �����ݿ����֣������ַ��
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	
	//����֡ ���� ����
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);	//������Ӧ��
	I2C_Stop();	
	
	return Data;
}
