#ifndef __TIM_H
#define __TIM_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"
#include "nvic.h"

#define TIM6_PERIOD_TIME_MS 10 //TIM6 intrrupt period time
#define TIM6_PRESCALER 64  //TIM6 CLK DIV   ������ʱҪ���ǵ�������Ϊ16λ�����ڳ�����Ҫ�Ӵ��Ƶϵ��
extern uint16_t Period_Divide_Counter;
void TIM6_init(void);

#ifdef __cplusplus
 }
#endif
