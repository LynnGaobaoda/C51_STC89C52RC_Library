#include <REGX52.H>
#include "Delay.h"

/**
	C51驱动步进电机模块
	电机速度1-3
	作者Ching
  */
	

//引脚定义
sfr							PHASE=0x90;
unsigned char 	TurnFlag;
unsigned char 	Motor_Speed;
//unsigned char AnticClk[]={0xFE,0xFD,0xFB,0xF7};	什么拍子法，没学会以后再说
//unsigned char NoAnticClk[]={0xFB,0xF7,0xFE,0xFD};


/**
  * @brief  电机初始化，占用定时器1
  * @param  无
  * @retval 无
  */
void Stepmotor_Init(void)
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x66;		//设置定时初值 1ms
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	//TR1 = 1;		//定时器1开始计时
	
	ET1=1;
	EA=1;
	PT1=0;
}

/**
	* @brief  设置电机速度
  * @param  Speed	电机速度 1-3
  * @retval 无
  */
void Set_Speed(unsigned char Speed)
{
	if(Speed){
		unsigned temp=TR1;	//保存电机之前的 是否运行状态
		TR1=0;
		if(Speed==1)	Motor_Speed=10;
		if(Speed==2)	Motor_Speed=5;
		if(Speed==3)	Motor_Speed=2;
		Delay(10);
		TR1|=temp;
	}
	else {TR1=0;PHASE=0xFF;}	//设置速度为0 0xFF防止电流一直有
}

/**
	* @brief  启动和暂停电机
  * @param  无
  * @retval 无
  */
void Motor_RunStop()
{
	if(TR1){TR1=0;PHASE=0xFF;}
	else	TR1=1;
}


/**
	* @brief  电机转向反转
  * @param  无
  * @retval 无
  */
void Motor_Reverses(void)
{
	unsigned temp=TR1;
	TR1=0;
	Delay(10);
	TurnFlag=~TurnFlag;
	TR1|=temp;
}

/**
	* @brief  电机中断函数，改变电机相位
  * @param  无
  * @retval 无
  */
void Timer1_Interrupt(void)		interrupt 3
{
	static unsigned Count=0,i=0;
	TL1 = 0x66;		//设置定时初值 1ms
	TH1 = 0xFC;
	Count++;
	if(Count>Motor_Speed){
		Count=0;
		if(i>3) i=0;
		if(TurnFlag) PHASE=~(0x01<<i);//PHASE=AnticClk[i]; //正转
		else	PHASE=~(0x08>>i);//PHASE=NoAnticClk[i]; //反转
		i++;
	}
}