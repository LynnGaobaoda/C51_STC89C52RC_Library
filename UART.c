#include <REGX52.H>

/**
	C51TTLת����ͨ���ж�ģ��
	�����ʿɲ���STC_ISP����
	����ռ�ö�ʱ��1
	���ߣ�Ching
  */

/**
  * @brief  ���ڳ�ʼ���Ĵ�������
  * @param  ��
  * @retval ��
  */
void UART_Init()
{
	PCON |= 0x80;		//����ģʽ1 �ڵ�Դ���ƼĴ�������
	SCON = 0x50;		//���ڹ���ģʽ �Ĵ���
	//AUXR &= 0xBF;		
	//AUXR &= 0xFE;	
	TMOD &= 0x0F;		//
	TMOD |= 0x20;		//��ʱ��1��8λ�Զ�����ģʽ
	TL1 = 0xF4;			//���س�ֵ ��Ӧ������
	TH1 = 0xF4;		
	ET1 = 0;		//��ֹ��ʱ��1 �ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	
	EA=1;	//�����ж�
	ES=1;	//�򿪴����ж�
}

/**
  * @brief  ���ڷ�������
  * @param  Byte ����
  * @retval ��
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0); //�ȴ�Ӳ����Ϊ1
	TI=0;	//�ֶ���Ϊ
}

/*//�����жϺ���ģ��
void UART_Routine(void) interrupt 4
{
	if(RI==1){//���գ������ж�	���ͺͽ��ն�������жϣ�ֻʶ������ж�
		//TODO
		Data=SBUF;
		RI=0; //���ձ�־λ��0
	}
}*/