
/**
	C51单片机延时
	作者：Ching
  */
  
/**
  *	@brief	STC89C52单片机延时函数
  *	@param	xms 延时时长 单位ms	
  *	@retval	无
  */
void Delay(unsigned int xms)		//@11.0592Hz 1ms
{
	unsigned char i, j;

	while(xms){
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
	
}

