#include <REGX52.H>

/**
	C51计数器
	占用timer0
	作者：Ching
  */

/**
  * @brief  配置定时器0为计数器
  * @param  无
  * @retval 无
  */
void Timer0_Init(void)		//1??@11.0592MHz
{
	//AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x66;		//无所谓
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 0;		
	
	//不开中断
}

/**
  * @brief  重置计数初值
  * @param  无
  * @retval 无
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/**
  * @brief  获取计数 us
  * @param  无
  * @retval 时间 us
  */
unsigned int Timer0_GetCounter(void)	//获取微秒数
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  启动关闭计时器
  * @param  无
  * @retval 无
  */
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}
