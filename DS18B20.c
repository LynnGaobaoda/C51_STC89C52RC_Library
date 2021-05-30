#include <REGX52.H>
#include "OneWire.h"

/**
	DS18B20温度传感器芯片 采用 单总线OneWire 协议传输数据
	如程序有中断，则应在OneWire.c中传输数据时：
		关闭总中断 EA 保证 单总线的绝对时间不被打断 
		随后开启中断
	DS18B0控制流程见芯片手册
	作者：Ching
  */

#define	DS18B20_SKIP_ROM		0xcc		//跳过ROM 控制字	详见DS18B20芯片手册
#define	DS18B20_CONVERT_T		0x44		//开始温度变换	控制字
#define	DS18B20_READ_SCRATCHPAD	0xbe		//读暂存器	控制字

/**
  *	@brief	将当前温度转为数据存在DS18B20暂存器中
  *	@param	无
  *	@retval	无
  */
void DS18B20_ConverT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
  *	@brief	读取DS18B20暂存器的温度数据
  *	@param	无
  *	@retval	温度数据
  */
float DS18B20_ReadT(void)	
{
	/**
	  * DS18B20采用两个8位暂存器TLSB，TMSB存放温度数据
	  * BCD编码
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
	T=Temp/16.0; //将低四位转换为小数点以后	缩小16倍 四位（16进制）	.0 不丢失精度保留小数后的数字
	return T;
}