#include <REGX52.H>

/**
	C51������
	ռ��timer0
	���ߣ�Ching
  */

/**
  * @brief  ���ö�ʱ��0Ϊ������
  * @param  ��
  * @retval ��
  */
void Timer0_Init(void)		//1??@11.0592MHz
{
	//AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x66;		//����ν
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 0;		
	
	//�����ж�
}

/**
  * @brief  ���ü�����ֵ
  * @param  ��
  * @retval ��
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/**
  * @brief  ��ȡ���� us
  * @param  ��
  * @retval ʱ�� us
  */
unsigned int Timer0_GetCounter(void)	//��ȡ΢����
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  �����رռ�ʱ��
  * @param  ��
  * @retval ��
  */
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}
