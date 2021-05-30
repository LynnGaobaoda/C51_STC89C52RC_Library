#include <REGX52.H>

/**
	C51 AD转换芯片 XPT2046：触摸屏芯片
	作者：Ching
  */

//引脚定义
sbit XPT204_CS=		P3^5;
sbit XPT204_DCLK=	P3^6;
sbit XPT204_DIN=	P3^4;
sbit XPT204_DOUT=	P3^7;

/**
  * @brief  读取模拟信号转成的数字信号
  * @param  Command 读取命令字，可以设置选择读取的哪个引脚模拟信号
  * @retval 数字信号
  */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue=0;
	XPT204_DCLK=0;
	XPT204_CS=0;
	
	/*发送命令字*/
	for(i=0;i<8;i++){
		XPT204_DIN=Command&(0x80>>i);
		XPT204_DCLK=1;
		XPT204_DCLK=0;
	}
	
	/*读数据*/
	for(i=0;i<16;i++){
		XPT204_DCLK=1;
		XPT204_DCLK=0;
		if(XPT204_DOUT){ADValue|=(0x8000>>i);}
	}
	
	XPT204_CS=1;
	if(Command&0x08){
		return ADValue>>8;	//8位模式取高8位即可 12位右移4即可
	}else{
		return ADValue>>4;
	}
	
}