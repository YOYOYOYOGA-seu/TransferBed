#ifndef __COMMON_H
#define __COMMON_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif


#include <stm32f10x_conf.h>
#include <stdio.h> 
#include "led.h"
#include "key.h"
#include "nvic.h"
#include "tim.h"
#include "lcd.h"
#include "delay.h"
//#include "usart.h"
#include "flash.h"
#include "rtc.h"
//#include "spi_flash.h"
//#include "dma.h"
#include "touch_screen.h"
#include "sdio_sdcard.h"
#include "ff.h"
#include "sd_operate.h"
#include "bmp.h"
#include "interface.h"
#include "motor_control.h"
#include "limit_switch.h"
#include "trans_bed.h"
	 
#define SYSTEM_CLK SYSCLK_FREQ_72MHz
#define TIM_CLK 72000000

#define PAout(a,b) GPIOA->BSRR|=1<<(a+(!b)*16)
#define PBout(a,b) GPIOB->BSRR|=1<<(a+(!b)*16)
#define PCout(a,b) GPIOC->BSRR|=1<<(a+(!b)*16)
#define PDout(a,b) GPIOD->BSRR|=1<<(a+(!b)*16)
#define PEout(a,b) GPIOE->BSRR|=1<<(a+(!b)*16)
#define PFout(a,b) GPIOF->BSRR|=1<<(a+(!b)*16)
#define PGout(a,b) GPIOA->BSRR|=1<<(a+(!b)*16)

#define PAin(a) (GPIOA->IDR&=1<<a)
#define PBin(a) (GPIOB->IDR&=1<<a)
#define PCin(a) (GPIOC->IDR&=1<<a)
#define PDin(a) (GPIOD->IDR&=1<<a)
#define PEin(a) (GPIOE->IDR&=1<<a)
#define PFin(a) (GPIOF->IDR&=1<<a)
#define PGin(a) (GPIOG->IDR&=1<<a)

extern char temp[30];
extern uint16_t Period_Divide_Counter;
extern char usart_test;

extern void (*appProgramPtr)(void);

#ifdef __cplusplus
 }
#endif
