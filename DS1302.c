#include <REGX52.H>

/**
	DS1302ʱ��оƬ�����Զ���ʱ�����ȸߣ�֧���ϸ�������
	���úͶ�ȡʱ��
	���ߣ�Ching
  */

//���Ŷ���
sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

//д�������ݵ�ַ0��β��|=0x01��Ϊ���ĵ�ַ �������֣�
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

//Ĭ��ʱ��/ʱ�仺����
unsigned char DS1302_Time[]={19,44,16,12,59,55,6};//2019�� �� �� ʱ �� �� ����

/**
  *	@brief	DS1302�������ݳ�ʼ����������
  *	@param	��	
  *	@retval	��
  */
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

/**
  *	@brief	DS1302���ã�оƬ���á�ʱ�䣩 дʱ��
  *	@param	Command �����ַ\������	
  *	@param	Data д������ݣ������ʱ������BCD����
  *	@retval	��
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
	//ʱ���оƬ�ֲ�
	unsigned char i;
	DS1302_CE=1;	
	for(i=0;i<8;i++){
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;	//�鿴оƬ�ֲ���ĸ����� setuptime holdtime ����Ƭ��ָ������ �����ж��Ƿ���Ҫ��ʱ
		DS1302_SCLK=0;
	}
		for(i=0;i<8;i++){
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;	//�鿴оƬ�ֲ���ĸ����� setuptime holdtime �����ж��Ƿ���Ҫ��ʱ
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}

/**
  *	@brief	DS1302�����ݣ�оƬ���á�ʱ�䣩 ��ʱ��
  *	@param	Command �����֡�ʱ�����ݵ�ַ
  *	@retval	DS1302���á���ʱ������
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command |=0x01;
	DS1302_CE=1;	
	for(i=0;i<8;i++){	//д������
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;	//��0��1 ��֤���ͣ�����������һλ�ߵ�λ�����������ȡ���� ģ��оƬ��ʱ��
		DS1302_SCLK=1;
	}
		
	for(i=0;i<8;i++){
		DS1302_SCLK=1;	//�����ݵ�IO�� �½�����Ч 
		DS1302_SCLK=0;	//��0������һ��ʱ�����ڣ�15��������ʹ��SLCK��0��β
		if(DS1302_IO){Data|=(0x01<<i);}	//Ϊ�����0��data������dataĬ��λ0
	}
	DS1302_CE=0;
	
	DS1302_IO=0;	//����������ݺ���0
	return Data;
}

/**
  *	@brief	DS1302����ʱ��ΪDS1302_Time����������
  *	@param	��
  *	@retval	��
  */
void DS1302_SetTime(void)
{
	//ʹ��BCD�������ʱ�����ݣ��磺53s=0x53BCD
	DS1302_WriteByte(DS1302_WP,0x00); 	//���д������
	DS1302_WriteByte(DS1302_YEAR,		DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,		DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,		DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,		DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,		DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,		DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,		DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);	//����д����
}

/**
  *	@brief	��ȡDS1302ʱ�����ݵ� DS1302_Time
  *	@param	��
  *	@retval	��
  */
void DS1302_ReadTime(void)
{
	//BCD����
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);		DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MONTH);		DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);		DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);		DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);		DS1302_Time[6]=Temp/16*10+Temp%16;
}