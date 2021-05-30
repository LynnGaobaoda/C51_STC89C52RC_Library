#include <REGX52.H>

/**
	I2C����ͨ�Ŵ���Э�飬1ʱ����+1������
	��Ƭ����ʱ���ź�1us��500Hz �㹻I2Cʱ��ת��������ʱ ���ù�holdTime��
	���ߣ�Ching
  */

//���Ŷ���
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  *	@brief	I2C ��ʼλ ʱ��
  *	@param	��	
  *	@retval	��
  */
void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;	
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
  *	@brief	I2C ֹͣλ ʱ��
  *	@param	��	
  *	@retval	��
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
  *	@brief	I2C ��������λ ʱ�� �ȸ�λ���λ
  *	@param	Byte ���͵�����һ���ֽ�
  *	@retval	��
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}	

/**
  *	@brief	I2C ��������λ ʱ�� �ȸ�λ���λ
  *	@param	��
  *	@retval	���յ���һ���ֽ�
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i, Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++){	
		I2C_SCL=1;	//���߶�ȡSDA
		if(I2C_SDA){Byte |=(0x80>>i);}
		I2C_SCL=0;	//�½����µ������Զ�����
	}
	return Byte;	
}

/**
  *	@brief	I2C ����Ӧ�� ʱ��
  *	@param	AckBit �Ƿ�Ӧ�� 0 Ӧ��1��Ӧ��
  *	@retval	��
  */
void I2C_SendAck(unsigned char AckBit)
{//bit51��Ƭ��������������
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  *	@brief	I2C ����Ӧ�� ʱ��
  *	@param	��
  *	@retval	�Ƿ�Ӧ�� 0���ӻ��յ����ݣ�Ӧ��. 1 �ӻ���Ӧ��
  */	
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2C_SCL=1;
	AckBit=I2C_SDA;
	I2C_SCL=0;
	return AckBit;
}

