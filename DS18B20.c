#include <REGX52.H>
#include "OneWire.h"

/**
	DS18B20�¶ȴ�����оƬ ���� ������OneWire Э�鴫������
	��������жϣ���Ӧ��OneWire.c�д�������ʱ��
		�ر����ж� EA ��֤ �����ߵľ���ʱ�䲻����� 
		������ж�
	DS18B0�������̼�оƬ�ֲ�
	���ߣ�Ching
  */

#define	DS18B20_SKIP_ROM		0xcc		//����ROM ������	���DS18B20оƬ�ֲ�
#define	DS18B20_CONVERT_T		0x44		//��ʼ�¶ȱ任	������
#define	DS18B20_READ_SCRATCHPAD	0xbe		//���ݴ���	������

/**
  *	@brief	����ǰ�¶�תΪ���ݴ���DS18B20�ݴ�����
  *	@param	��
  *	@retval	��
  */
void DS18B20_ConverT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
  *	@brief	��ȡDS18B20�ݴ������¶�����
  *	@param	��
  *	@retval	�¶�����
  */
float DS18B20_ReadT(void)	
{
	/**
	  * DS18B20��������8λ�ݴ���TLSB��TMSB����¶�����
	  * BCD����
	  */
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);	
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();	
	TMSB=OneWire_ReceiveByte();
	
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0; //������λת��ΪС�����Ժ�	��С16�� ��λ��16���ƣ�	.0 ����ʧ���ȱ���С���������
	return T;
}