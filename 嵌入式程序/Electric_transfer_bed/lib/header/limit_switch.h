#ifndef __LIMIT_SWITCH_H
#define __LIMIT_SWITCH_H
#endif
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32f10x_conf.h"
#define LIMIT_SWITCH_PORT GPIOF
#define LIMIT_SWITCH_CLK RCC_APB2Periph_GPIOF
#define LS_BACK_TOP_PIN  GPIO_Pin_0
#define LS_BACK_BOTTOM_PIN  GPIO_Pin_1
#define LS_BED_TOP_PIN  GPIO_Pin_2
#define LS_BED_BOTTOM_PIN  GPIO_Pin_3
#define LS_BED_OUTSIDE_PIN  GPIO_Pin_4
#define LS_BED_INSIDE_PIN  GPIO_Pin_5

#define LS_BACK_REACH_TOP     ((uint8_t)0x01)
#define LS_BACK_REACH_BOTTOM	((uint8_t)0x02)
#define LS_BED_REACH_TOP			((uint8_t)0x04)
#define LS_BED_REACH_BOTTOM   ((uint8_t)0x08)
#define LS_BED_REACH_OUT      ((uint8_t)0x10)
#define LS_BED_REACH_IN				((uint8_t)0x20)

extern uint8_t LS_State;
void LS_init(void);
void LS_Read_State(void);

#ifdef __cplusplus
 }
#endif
