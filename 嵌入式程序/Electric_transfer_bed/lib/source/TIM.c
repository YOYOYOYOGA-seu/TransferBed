#include "common.h"

uint32_t TIM6_Period = TIM6_PERIOD_TIME_MS*(TIM_CLK/(TIM6_PRESCALER*1000));
uint16_t Period_Divide_Counter = 0;  //用于计数，在mian函数while循环里划分周期时段（线程）

void TIM6_init()
{
	NVIC_TIM6_init();
	TIM_TimeBaseInitTypeDef TIM6_init_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //the max frequence of APB1's clock PCLK1 is 36MHZ,but TIM_CLK don't from PCLK1
	TIM6_init_struct.TIM_Period = TIM6_Period-1;
	TIM6_init_struct.TIM_Prescaler = TIM6_PRESCALER-1;
	TIM_TimeBaseInit(TIM6,&TIM6_init_struct);
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
}
