#include "limit_switch.h"

uint8_t LS_State = 0;
void LS_init()
{
	GPIO_InitTypeDef LS_GPIO_init;
	LS_GPIO_init.GPIO_Mode = GPIO_Mode_IPD;
	LS_GPIO_init.GPIO_Pin = LS_BACK_TOP_PIN|LS_BACK_BOTTOM_PIN|LS_BED_TOP_PIN|LS_BED_BOTTOM_PIN|
														LS_BED_OUTSIDE_PIN|LS_BED_INSIDE_PIN;
	LS_GPIO_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LIMIT_SWITCH_PORT,&LS_GPIO_init);
}

void LS_Read_State(void)
{
	LS_State = LIMIT_SWITCH_PORT->IDR&0x3F;
}
