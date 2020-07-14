#include "led.h"
void led_init()
{
	GPIO_InitTypeDef LED2_init;
	GPIO_InitTypeDef LED3_init;
	LED2_init.GPIO_Mode = GPIO_Mode_Out_PP;
	LED2_init.GPIO_Pin = GPIO_Pin_5;
	LED2_init.GPIO_Speed = GPIO_Speed_10MHz;
	LED3_init.GPIO_Mode = GPIO_Mode_Out_PP;
	LED3_init.GPIO_Pin = GPIO_Pin_5;
	LED3_init.GPIO_Speed = GPIO_Speed_10MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_Init(GPIOB,&LED3_init);
	GPIO_Init(GPIOE,&LED2_init);
}
