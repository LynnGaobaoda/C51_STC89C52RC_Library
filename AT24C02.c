#include "I2C.h"
#include <REGX52.H>

/**
	AT24C02 存储器，全称： ATMTC.98 24C02N SU27 D
	采用I2C数据传输协议
	作者：Ching
  */

#define AT24C02_ADDRESS	0xA0 //写数据控制字（程序地址） 读数据控制字| 0x01即可 详见AT24C02芯片手册

/**
  *	@brief	AT24C02存储芯片写数据 数据帧
  *	@param	WordAddress 要写入的数据所在地址	
  *	@retval	无
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)	//AT24C02写入数据时序
{
	//第一帧 发送 写数据控制字（程序地址）
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);	
	I2C_ReceiveAck();
	//if(Ack==0) P2=0x00;	//LCD点亮 测试是否应答
	
	//第二帧 发送 字地址（数据地址）
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	
	//第三帧 发送 数据
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();	//可以注释，详细见复合格式数据帧
}

/**
  *	@brief	AT24C02存储芯片读数据 数据帧
  *	@param	WordAddress 要读取的数据所在地址	
  *	@retval	WordAddress处存储的一个字节
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)//AT24C02读出数据时序
{
	unsigned char Data;
	
	//第一帧 发送 写数据控制字（程序地址）
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);	
	I2C_ReceiveAck();
	
	//第二帧 发送 字地址（数据地址）
	I2C_SendByte(WordAddress);	
	I2C_ReceiveAck();
	
	//第三帧 发送 读数据控制字（程序地址）
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	
	//第四帧 接收 数据
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);	//不接受应答
	I2C_Stop();	
	
	return Data;
}
