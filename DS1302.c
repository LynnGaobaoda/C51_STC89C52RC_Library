#include <REGX52.H>

/**
	DS1302时钟芯片，有自动计时，精度高，支持涓细电流充电
	设置和读取时间
	作者：Ching
  */

//引脚定义
sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

//写日期数据地址0结尾，|=0x01即为读的地址 （控制字）
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

//默认时间/时间缓冲区
unsigned char DS1302_Time[]={19,44,16,12,59,55,6};//2019年 月 日 时 分 秒 星期

/**
  *	@brief	DS1302传输数据初始化引脚设置
  *	@param	无	
  *	@retval	无
  */
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

/**
  *	@brief	DS1302设置（芯片配置、时间） 写时序
  *	@param	Command 命令地址\控制字	
  *	@param	Data 写入的数据，如果是时间则是BCD编码
  *	@retval	无
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
	//时序见芯片手册
	unsigned char i;
	DS1302_CE=1;	
	for(i=0;i<8;i++){
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;	//查看芯片手册的四个参数 setuptime holdtime 及单片机指令周期 等来判断是否需要延时
		DS1302_SCLK=0;
	}
		for(i=0;i<8;i++){
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;	//查看芯片手册的四个参数 setuptime holdtime 等来判断是否需要延时
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}

/**
  *	@brief	DS1302读数据（芯片配置、时间） 读时序
  *	@param	Command 命令字、时间数据地址
  *	@retval	DS1302配置、或时间数据
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command |=0x01;
	DS1302_CE=1;	
	for(i=0;i<8;i++){	//写命令字
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;	//先0后1 保证最后停在命令字最后一位高电位，方便后续读取数据 模拟芯片读时序
		DS1302_SCLK=1;
	}
		
	for(i=0;i<8;i++){
		DS1302_SCLK=1;	//读数据到IO口 下降沿有效 
		DS1302_SCLK=0;	//后0可以少一个时钟周期，15个，可以使得SLCK以0结尾
		if(DS1302_IO){Data|=(0x01<<i);}	//为真则读0到data，否则data默认位0
	}
	DS1302_CE=0;
	
	DS1302_IO=0;	//建议读完数据后置0
	return Data;
}

/**
  *	@brief	DS1302设置时间为DS1302_Time数组内数据
  *	@param	无
  *	@retval	无
  */
void DS1302_SetTime(void)
{
	//使用BCD编码存入时间数据，如：53s=0x53BCD
	DS1302_WriteByte(DS1302_WP,0x00); 	//解除写保护包
	DS1302_WriteByte(DS1302_YEAR,		DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,		DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,		DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,		DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,		DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,		DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,		DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);	//设置写保护
}

/**
  *	@brief	读取DS1302时间数据到 DS1302_Time
  *	@param	无
  *	@retval	无
  */
void DS1302_ReadTime(void)
{
	//BCD解码
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);		DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MONTH);		DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);		DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);		DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);		DS1302_Time[6]=Temp/16*10+Temp%16;
}