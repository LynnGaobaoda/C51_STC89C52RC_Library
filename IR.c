#include <REGX52.H>
#include "timer0Counter.h"
#include "int0.h"

/**
	C51�����źŽ���ʱ�� 
	����NEC����
	48KHZΪһ���͵�ƽ������״̬Ϊ�ߵ�ƽ
	���ߣ�Ching
  */

//ʱ��״̬�����ݽ��ջ���
unsigned int IR_Time;			//�����½��صļ��ʱ��
unsigned char IR_State;			//0���иߵ�λ 1�͵�ƽ 2��������
unsigned char IR_Data[4];		//���������ź� 4�ֽ�	���ݻ���
unsigned char IR_pData;			//IR_Data�ڼ�λ
unsigned char IR_DataFlag;		//�Ƿ�õ���������
unsigned char IR_RepeatFlag;	//���ⳤ���ź�
unsigned char IR_Address;		//��ַ��
unsigned char IR_Command;		//������

/**
  * @brief  ����������ó�ʼ��
  * @param  ��
  * @retval ��
  */
void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();	//�½��ش���
}

/**
  * @brief  �Ƿ�õ���������
  * @param  ��
  * @retval 1���յ�
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
  * @brief	�Ƿ���յ��ظ������ź�
  * @param  ��
  * @retval 1 ��
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
  * @brief  ��ȡNEC�����ַ����
  * @param  ��
  * @retval ��ַ��
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

/**
  * @brief  ��ȡ��������������
  * @param  ��
  * @retval ��������
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

/**
  * @brief  ����ת�����ź� �½����жϺ���
  * @param  ��
  * @retval ��
  */
void Int0_Routine(void)	interrupt 0	//�ⲿ�жϣ��½���
{
	if(IR_State==0){
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State=1;
	}
	
	//�ɿ���תΪ��ʼ �� repeat
	else if(IR_State==1){	
		IR_Time=Timer0_GetCounter();	//��¼��һ���½��ص�����½��ص�ʱ�� 
		Timer0_SetCounter(0);	//���¼�ʱ
		
		if(IR_Time>12500-500 && IR_Time<12500+500){	//��ʼ�ź�
			IR_State=2; 
		}
		else if(IR_Time>10250-500 && IR_Time<10250+500){	//repeat �ź�
			IR_RepeatFlag=1; 
			//P2=0;//test code
			Timer0_Run(0);	//����ʱ�䲻�ü�ʱ
			IR_State=0;
		}
		else{
			IR_State=1;
		}
	}
	
	//��ȡdata
	else if(IR_State==2){	
		IR_Time=Timer0_GetCounter();	//��¼��һ���½��ص�����½��ص�ʱ�� 
		Timer0_SetCounter(0);
		if(IR_Time>1102-500 && IR_Time<1120+500){	//0 �ź�
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));//��ȡһλ0�ź�
			IR_pData++;
		}
		else if(IR_Time>2250-500 && IR_Time<2250+500){	//1 �ź�
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));//��ȡһλ1�ź�
			IR_pData++;
		}
		else{	//���ݴ���
			IR_pData=0;
			IR_pData=1;
		}
		if(IR_pData>=32){	//�������
			IR_pData=0;
			if(IR_Data[0] == ~IR_Data[1] &&(IR_Data[2] == ~IR_Data[3])){	//�ɹ��յ���ȷ����
				IR_Address=IR_Data[0];
				IR_Command=IR_Data[2];
				IR_DataFlag=1;
			}
			IR_State=0;
			Timer0_Run(0);	//���ݽ�����ϣ�ֹͣ��ʱ,�ص�����״̬
		}
	}
}
