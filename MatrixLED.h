#ifndef __MATRIXLED_H_
#define __MATRIXLED_H_

void 	_74HC595_writeByte(unsigned char Byte);
void 	MatrixLED_ShowColumn(unsigned char Column, Data);
void 	MatrixLED_Init();

#endif