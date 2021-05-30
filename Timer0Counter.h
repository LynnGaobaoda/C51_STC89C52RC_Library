#ifndef _TIMER0COUNTER_H_
#define _TIMER0COUNTER_H_

void 			Timer0_Init(void);
void 			Timer0_SetCounter(unsigned int Value);
unsigned int 	Timer0_GetCounter(void);
void 			Timer0_Run(unsigned char Flag);
#endif