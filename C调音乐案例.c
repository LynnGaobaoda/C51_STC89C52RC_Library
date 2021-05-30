#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit Buzzer=P1^5;
#define SPEED	500	//4分音符时长 ms

#define P	0		//休止符
#define L1	1		//低音1
#define L1_	2		//低音1升半音 1#
#define L2	3
#define L2_	4
#define L3	5	//3 7 无半音
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12

#define M1	13		
#define M1_	14	
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24

#define H1	25		
#define H1_	26	
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

//C调音符频率转定时器装载表
unsigned int code FreqTable[]={
	0, //休止符
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283
};


//小星星乐谱
/*unsigned char Music[]={	//音符，音符时长	以8分音符为基准
	13,4,
	13,4,
	20,4,
	20,4,
	22,4,
	22,4,
	20,4+4,	//两个4分音符，不松手
	18,4,
	18,4,
	17,4,
	17,4,
	15,4,
	13,4+4,
	0xff
};*/

//天空之城乐谱
unsigned char code Music[]={
	P,4,
	P,4,
	P,4,
	M6,2,
	M7,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	M7,4+4+4,
	M3,2,
	M3,2,
	
	0xFF
};

/*//青花瓷
unsigned char code Music[]={
	//1
	P,4+2,
	H6,2,
	H5,2,
	H3,2,
	H2,2,
	H3,2,
	
	H2,2,
	H1,2,
	M6,4+4,
	H2,2,
	H3,2,
	
	H2,2,
	H1,2,
	M5,4+4,
	H2,2,
	H3,2,
	//2
	H2,2,
	H1,2,
	M6,4,
	H1,2,
	H2,2,
	M6,2,
	
	H3,4+4,
	H1,2,
	H2,2,
	H3,2,
	H5,2,
	
	H5,2,
	H3,2,
	H3,4,
	H2,4,
	H1,4,
	//3
	H3,4,
	M7,4,
	M3,4,
	P,4,
	
	L1,4,
	L5,4,
	M1,4,
	P,4,
	
	L6,3,
	L3,4,
	L6,4,
	P,4,
	
	0xff
	
};*/

/*unsigned char code Music[]={
	L5,4+4,
	M1,4,
	
	M3,4+2,
	M1,2,
	M2,4,
	
	M1,4+4+4,
	M1,4+4+4,
	
	L5,4+4,
	M1,4,
	
	M3,4+2,
	M1,2,
	M3,4,
	
	M2,4+4+4,
	M2,4+4+4,
	
	0xff
};*/


unsigned char FreqSelect,MusicSelect;
void main()
{
	Timer0Init();
	while(1){
		if(Music[MusicSelect] !=0xff){
			FreqSelect=Music[MusicSelect];
			MusicSelect++;
			Delay(SPEED/4*Music[MusicSelect]);	//播方几分音符时长
			MusicSelect++;
			TR0=0;	//关闭-打开定时器 模仿抬手
			Delay(5);
			TR0=1;
		}else{
			TR0=0;
			while(1);
		}
		
	}	
}

//以特定音符频率播放
void Timer0_Routine() interrupt 1
{
	if(FreqTable[FreqSelect]){	//不为0不是休止符
		TL0 = FreqTable[FreqSelect]%256;
		TH0 =  FreqTable[FreqSelect]/256;	
		Buzzer =!Buzzer;	
	}

}
