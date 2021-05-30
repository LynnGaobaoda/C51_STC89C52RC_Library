#include <REGX52.H>

/**
	C51���
	ռ��timer1
	
	�����Խ����������¶���STC89C52RC�У�
	Compare/200��ռ�ձȡ�200Ϊ20ms����
	0/200��ռ�ձ�Ϊ0:135��
	��Сת��: 0�㣺2/200	����0С��2��˳ʱ����ת���满����ת��
	���ת��: 180�㣺21/200	����21����ʱ����ת��˳������ת��
	�������ͽǶ�ռ�ձȣ�
	45��-	5/200 
	90��-	10/200 
	135��-	13/200 
	180��-	18/200
	215��-	21/200
	���ߣ�Ching
  */

//���Ŷ���
sbit SE_Pwm=P1^0;
unsigned char Compare;  //ռ�ձ�=Compare/200   5=<compare<=25


/**
  * @brief  �����ʼ��
  * @param  ��
  * @retval ��
  */
void Se_Init()
{
	//���ö�ʱ��1��16λ��100us��ʱ
	TMOD &= 0x0F;	
	TMOD |= 0x10;	
	TL1 = 0xA4;		
	TH1 = 0xFF;		
	TF1 = 0;	
	TR1 = 1;	
	
	//�жϴ���
	ET1=1; 	
	EA=1;
	PT1=0;
}

/**
  * @brief  ���ת��Ƕ�
  * @param  Angle ת��Ƕ�2-21 �ȱ���0-215��
  * @retval ��
  */
void Set_Angle(unsigned char Angle)
{

	Compare=Angle;
}

/**
  * @brief  �������pwm��
  * @param  ��
  * @retval ��
  */
void Timer1_Routine() interrupt 3
{
	static unsigned int T0Count=0;
	TL1 = 0xA4;			//100us��ʱ��
	TH1 = 0xFF;			
	T0Count++;
	T0Count=T0Count%200; //pwm ���� 20ms	
	if(T0Count<Compare) SE_Pwm=1;
	else SE_Pwm=0;
	
}