#ifndef __DELAY_H
#define __DELAY_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(uint32_t nTime);	  //单位10us
void TimingDelay_Decrement(void);
#define Delay_ms(x) Delay_us(1000*x)//单位ms

#endif 
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
#ifdef __cplusplus
 }
#endif
