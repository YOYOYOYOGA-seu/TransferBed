#ifndef __LED_H
#define __LED_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f10x_conf.h"

#define LED2_OFF PEout(5,1)
#define LED3_OFF PBout(5,1)
#define LED2_ON PEout(5,0)
#define LED3_ON PEout(5,0)
#define LED2_TOGGLE GPIOE->ODR^=1<<5
#define LED3_TOGGLE GPIOB->ODR^=1<<5

void led_init(void);

#ifdef __cplusplus
 }
#endif
