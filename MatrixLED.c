#include <REGX52.H>
#include "Delay.h"


/**
	LED点阵屏模块 类似共阴极数码管
	每一列的数据通过74HC595 移位芯片输入 串转并
	作者：Ching
  */

#define MATRIX_LED_PORT	P0

//引脚定义
sbit RCK=P3^5; // 等于 =P3_5 RCLK
sbit SCK=P3^6;	//SRCLK
sbit SER=P3^4;	//SER

/**
  * @brief  点阵LED初始化：配置74HC595引脚信号
  * @param  无
  * @retval 无
  */
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}

/**
  * @brief  74HC595写入数据
  * @param  Byte 写入的一个字节
  * @retval	无
  */
void _74HC595_writeByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++){
		SER=Byte&(0x80>>i);	//非0即1 取出Byte最高位
		SCK=1;	//上升沿写入
		SCK=0;
	}
	RCK=1; 	//上升沿锁存74HC595输出寄存器
	RCK=0;
}

/**
  * @brief  LED列的数据显示
  * @param  Column 选择列数
  * @param  Data 一列数据
  * @retval	无
  */
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
	_74HC595_writeByte(Data);	//一列的数据
	MATRIX_LED_PORT=~(0x80>>Column);	//选择列
	Delay(1);
	MATRIX_LED_PORT=0xFF;	//消影
}

