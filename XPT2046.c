#include <REGX52.H>

/**
	C51 ADת��оƬ XPT2046��������оƬ
	���ߣ�Ching
  */

//���Ŷ���
sbit XPT204_CS=		P3^5;
sbit XPT204_DCLK=	P3^6;
sbit XPT204_DIN=	P3^4;
sbit XPT204_DOUT=	P3^7;

/**
  * @brief  ��ȡģ���ź�ת�ɵ������ź�
  * @param  Command ��ȡ�����֣���������ѡ���ȡ���ĸ�����ģ���ź�
  * @retval �����ź�
  */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue=0;
	XPT204_DCLK=0;
	XPT204_CS=0;
	
	/*����������*/
	for(i=0;i<8;i++){
		XPT204_DIN=Command&(0x80>>i);
		XPT204_DCLK=1;
		XPT204_DCLK=0;
	}
	
	/*������*/
	for(i=0;i<16;i++){
		XPT204_DCLK=1;
		XPT204_DCLK=0;
		if(XPT204_DOUT){ADValue|=(0x8000>>i);}
	}
	
	XPT204_CS=1;
	if(Command&0x08){
		return ADValue>>8;	//8λģʽȡ��8λ���� 12λ����4����
	}else{
		return ADValue>>4;
	}
	
}