#include <REGX52.H>
#include "timer0Counter.h"
#include "int0.h"

/**
	C51红外信号接收时序 
	采用NEC编码
	48KHZ为一个低电平，空闲状态为高电平
	作者：Ching
  */

//时序状态与数据接收缓存
unsigned int IR_Time;			//两个下降沿的间隔时间
unsigned char IR_State;			//0空闲高电位 1低电平 2解码数据
unsigned char IR_Data[4];		//红外数据信号 4字节	数据缓存
unsigned char IR_pData;			//IR_Data第几位
unsigned char IR_DataFlag;		//是否得到红外数据
unsigned char IR_RepeatFlag;	//红外长按信号
unsigned char IR_Address;		//地址码
unsigned char IR_Command;		//命令码

/**
  * @brief  红外接收配置初始化
  * @param  无
  * @retval 无
  */
void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();	//下降沿触发
}

/**
  * @brief  是否得到红外数据
  * @param  无
  * @retval 1接收到
  */
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag){
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief	是否接收到重复长按信号
  * @param  无
  * @retval 1 是
  */
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag){
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  获取NEC红外地址编码
  * @param  无
  * @retval 地址码
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

/**
  * @brief  获取红外命令字数据
  * @param  无
  * @retval 命令数据
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

/**
  * @brief  红外转数字信号 下降沿中断函数
  * @param  无
  * @retval 无
  */
void Int0_Routine(void)	interrupt 0	//外部中断，下降沿
{
	if(IR_State==0){
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State=1;
	}
	
	//由空闲转为开始 或 repeat
	else if(IR_State==1){	
		IR_Time=Timer0_GetCounter();	//记录上一个下降沿到这个下降沿的时间 
		Timer0_SetCounter(0);	//重新计时
		
		if(IR_Time>12500-500 && IR_Time<12500+500){	//开始信号
			IR_State=2; 
		}
		else if(IR_Time>10250-500 && IR_Time<10250+500){	//repeat 信号
			IR_RepeatFlag=1; 
			//P2=0;//test code
			Timer0_Run(0);	//空闲时间不用计时
			IR_State=0;
		}
		else{
			IR_State=1;
		}
	}
	
	//读取data
	else if(IR_State==2){	
		IR_Time=Timer0_GetCounter();	//记录上一个下降沿到这个下降沿的时间 
		Timer0_SetCounter(0);
		if(IR_Time>1102-500 && IR_Time<1120+500){	//0 信号
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));//读取一位0信号
			IR_pData++;
		}
		else if(IR_Time>2250-500 && IR_Time<2250+500){	//1 信号
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));//读取一位1信号
			IR_pData++;
		}
		else{	//数据错误，
			IR_pData=0;
			IR_pData=1;
		}
		if(IR_pData>=32){	//接收完毕
			IR_pData=0;
			if(IR_Data[0] == ~IR_Data[1] &&(IR_Data[2] == ~IR_Data[3])){	//成功收到正确数据
				IR_Address=IR_Data[0];
				IR_Command=IR_Data[2];
				IR_DataFlag=1;
			}
			IR_State=0;
			Timer0_Run(0);	//数据接收完毕，停止计时,回到空闲状态
		}
	}
}
