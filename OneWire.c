#include <REGX52.H>

/**
	单总线通讯协议时序，用于温度芯片DS18B20
	采用绝对时间，如有中断应关闭中断
	作者：Ching
  */

//引脚定义
sbit OneWire_DQ=P3^7;

/**
  * @brief  单总线初始化时序
  * @param  无
  * @retval 从机应答0表示应答
  */
unsigned char OneWire_Init(void)
{
	unsigned char i,AckBit;
	//EA=0 //关中断
	OneWire_DQ=1;
	OneWire_DQ=0;	//拉低
	i = 247;while (--i);	//delay 500us
	OneWire_DQ=1;	//释放
	i = 32;while (--i);	//delay 70us
	AckBit=OneWire_DQ;	//接收应答 低电平
	i = 247;while (--i);	//delay 500us
	//EA=1 //恢复中断
	return AckBit;
}

/**
  * @brief  单总线传输一位数据
  * @param  Bit一位数据0/1
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	//EA=0 //关中断
	OneWire_DQ=0;	//拉低
	i = 4;while (--i);	//Delay 10us
	OneWire_DQ=Bit;	//发送一位
	i = 24;while (--i);	//Delay 50us
	OneWire_DQ=1;	//释放到高电平
	//EA=1 //恢复中断
}

/**
  * @brief  单总线接收一位数据
  * @param  无
  * @retval 一位数据0/1
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i,Bit;
	OneWire_DQ=0;
	i = 2;while (--i); //5us
	OneWire_DQ=1; //释放
	i = 2;while (--i); //5us
	Bit=OneWire_DQ;
	i = 24;while (--i);	//Delay 50us
	//不用拉高释放，从机时序结束后会自动释放
	return Bit;
}

/**
  * @brief  单总线发送一个字节数据 单总线数据 先低位后高位
  * @param  Byte 数据
  * @retval 无1
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  单总线接收一个字节数据 单总线数据 先低位后高位
  * @param  无
  * @retval 一字节数据
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++){
		if(OneWire_ReceiveBit()) (Byte |= (0x01<<i));
	}
	return Byte;
}
