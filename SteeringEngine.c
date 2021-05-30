#include <REGX52.H>

/**
	C51舵机
	占用timer1
	
	经测试矫正，有如下定义STC89C52RC中：
	Compare/200：占空比、200为20ms周期
	0/200：占空比为0:135°
	最小转角: 0°：2/200	大于0小于2会顺时针旋转（逆弧度旋转）
	最大转角: 180°：21/200	大于21会逆时针旋转（顺弧度旋转）
	几个典型角度占空比：
	45°-	5/200 
	90°-	10/200 
	135°-	13/200 
	180°-	18/200
	215°-	21/200
	作者：Ching
  */

//引脚定义
sbit SE_Pwm=P1^0;
unsigned char Compare;  //占空比=Compare/200   5=<compare<=25


/**
  * @brief  舵机初始化
  * @param  无
  * @retval 无
  */
void Se_Init()
{
	//采用定时器1：16位，100us定时
	TMOD &= 0x0F;	
	TMOD |= 0x10;	
	TL1 = 0xA4;		
	TH1 = 0xFF;		
	TF1 = 0;	
	TR1 = 1;	
	
	//中断处理
	ET1=1; 	
	EA=1;
	PT1=0;
}

/**
  * @brief  舵机转向角度
  * @param  Angle 转向角度2-21 等比例0-215°
  * @retval 无
  */
void Set_Angle(unsigned char Angle)
{

	Compare=Angle;
}

/**
  * @brief  舵机输入pwm波
  * @param  无
  * @retval 无
  */
void Timer1_Routine() interrupt 3
{
	static unsigned int T0Count=0;
	TL1 = 0xA4;			//100us定时器
	TH1 = 0xFF;			
	T0Count++;
	T0Count=T0Count%200; //pwm 周期 20ms	
	if(T0Count<Compare) SE_Pwm=1;
	else SE_Pwm=0;
	
}