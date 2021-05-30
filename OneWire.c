#include <REGX52.H>

/**
	������ͨѶЭ��ʱ�������¶�оƬDS18B20
	���þ���ʱ�䣬�����ж�Ӧ�ر��ж�
	���ߣ�Ching
  */

//���Ŷ���
sbit OneWire_DQ=P3^7;

/**
  * @brief  �����߳�ʼ��ʱ��
  * @param  ��
  * @retval �ӻ�Ӧ��0��ʾӦ��
  */
unsigned char OneWire_Init(void)
{
	unsigned char i,AckBit;
	//EA=0 //���ж�
	OneWire_DQ=1;
	OneWire_DQ=0;	//����
	i = 247;while (--i);	//delay 500us
	OneWire_DQ=1;	//�ͷ�
	i = 32;while (--i);	//delay 70us
	AckBit=OneWire_DQ;	//����Ӧ�� �͵�ƽ
	i = 247;while (--i);	//delay 500us
	//EA=1 //�ָ��ж�
	return AckBit;
}

/**
  * @brief  �����ߴ���һλ����
  * @param  Bitһλ����0/1
  * @retval ��
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	//EA=0 //���ж�
	OneWire_DQ=0;	//����
	i = 4;while (--i);	//Delay 10us
	OneWire_DQ=Bit;	//����һλ
	i = 24;while (--i);	//Delay 50us
	OneWire_DQ=1;	//�ͷŵ��ߵ�ƽ
	//EA=1 //�ָ��ж�
}

/**
  * @brief  �����߽���һλ����
  * @param  ��
  * @retval һλ����0/1
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i,Bit;
	OneWire_DQ=0;
	i = 2;while (--i); //5us
	OneWire_DQ=1; //�ͷ�
	i = 2;while (--i); //5us
	Bit=OneWire_DQ;
	i = 24;while (--i);	//Delay 50us
	//���������ͷţ��ӻ�ʱ���������Զ��ͷ�
	return Bit;
}

/**
  * @brief  �����߷���һ���ֽ����� ���������� �ȵ�λ���λ
  * @param  Byte ����
  * @retval ��1
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  �����߽���һ���ֽ����� ���������� �ȵ�λ���λ
  * @param  ��
  * @retval һ�ֽ�����
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++){
		if(OneWire_ReceiveBit()) (Byte |= (0x01<<i));
	}
	return Byte;
}
