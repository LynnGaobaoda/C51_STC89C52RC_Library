#include <REGX52.H>

/**
	I2C串行通信传输协议，1时钟线+1数据线
	单片机的时钟信号1us，500Hz 足够I2C时序翻转，不用延时 不用管holdTime等
	作者：Ching
  */

//引脚定义
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  *	@brief	I2C 起始位 时序
  *	@param	无	
  *	@retval	无
  */
void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;	
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
  *	@brief	I2C 停止位 时序
  *	@param	无	
  *	@retval	无
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
  *	@brief	I2C 发送数据位 时序 先高位后低位
  *	@param	Byte 发送的数据一个字节
  *	@retval	无
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
  *	@brief	I2C 接收数据位 时序 先高位后低位
  *	@param	无
  *	@retval	接收到的一个字节
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i, Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++){	
		I2C_SCL=1;	//拉高读取SDA
		if(I2C_SDA){Byte |=(0x80>>i);}
		I2C_SCL=0;	//下降沿新的数据自动跟新
	}
	return Byte;	
}

/**
  *	@brief	I2C 发送应答 时序
  *	@param	AckBit 是否应答 0 应答，1非应答
  *	@retval	无
  */
void I2C_SendAck(unsigned char AckBit)
{//bit51单片机特有数据类型
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  *	@brief	I2C 接收应答 时序
  *	@param	无
  *	@retval	是否应答 0，从机收到数据，应答. 1 从机不应答
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

