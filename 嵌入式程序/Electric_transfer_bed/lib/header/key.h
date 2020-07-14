#ifndef __LED_H
#define __LED_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"
#include "NVIC.h"


//----------------------将按键顺序与key[]数组对齐,用户调用---------------------

//--------------------------------------------------------
#define KEY_NUM 4
#define IF_KEY0_DOWN GPIO_ReadInputDataBit(key[0].key_GPIO_port,key[0].key_GPIO_init.GPIO_Pin)==1
#define IF_KEY1_DOWN GPIO_ReadInputDataBit(key[1].key_GPIO_port,key[1].key_GPIO_init.GPIO_Pin)==0
#define IF_KEY2_DOWN GPIO_ReadInputDataBit(key[2].key_GPIO_port,key[2].key_GPIO_init.GPIO_Pin)==0
#define IF_KEY3_DOWN GPIO_ReadInputDataBit(key[3].key_GPIO_port,key[3].key_GPIO_init.GPIO_Pin)==0

#define LONG_PRESS_COUNTER_VALUE 1000/TIM6_PERIOD_TIME_MS  //TIM6 Period 单位为 1ms
#define INVALID_PRESS_COUNTER_VLAUE 20/TIM6_PERIOD_TIME_MS     //TIM6 Period 单位为 1ms

#define S1 1
#define S2 2
#define S3 3
#define S4 0

typedef struct 
{
	uint32_t press_flag;
	uint32_t short_press;
	uint32_t long_press;
	uint32_t long_press_action;
	uint32_t counter;
	
	uint32_t Pres_counter;
	
	EXTI_InitTypeDef key_EXTI_init;
	GPIO_InitTypeDef key_GPIO_init;
	NVIC_InitTypeDef key_NVIC_init;
	GPIO_TypeDef* key_GPIO_port;
	uint8_t GPIO_Por;
	uint8_t GPIO_pin;
}KEY;

extern KEY key[KEY_NUM];


void delay_nms(void);
void key_struct_init(void);
void key_init(void);

#ifdef __cplusplus
 }
#endif
