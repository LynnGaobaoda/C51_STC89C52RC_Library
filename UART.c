#include <REGX52.H>

/**
	C51TTL转串口通信中断模块
	波特率可采用STC_ISP计算
	本列占用定时器1
	作者：Ching
  */

/**
  * @brief  串口初始化寄存器设置
  * @param  无
  * @retval 无
  */
void UART_Init()
{
	PCON |= 0x80;		//工作模式1 在电源控制寄存器设置
	SCON = 0x50;		//串口工作模式 寄存器
	//AUXR &= 0xBF;		
	//AUXR &= 0xFE;	
	TMOD &= 0x0F;		//
	TMOD |= 0x20;		//定时器1：8位自动重载模式
	TL1 = 0xF4;			//重载初值 对应波特率
	TH1 = 0xF4;		
	ET1 = 0;		//禁止定时器1 中断
	TR1 = 1;		//定时器1开始计时
	
	EA=1;	//打开总中断
	ES=1;	//打开串口中断
}

/**
  * @brief  串口发送数据
  * @param  Byte 数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0); //等待硬件置为1
	TI=0;	//手动置为
}

/*//串口中断函数模板
void UART_Routine(void) interrupt 4
{
	if(RI==1){//接收（读）中断	发送和接收都会产生中断，只识别接收中断
		//TODO
		Data=SBUF;
		RI=0; //接收标志位清0
	}
}*/