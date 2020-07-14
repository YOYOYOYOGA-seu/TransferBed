#ifndef __RTC_H
#define __RTC_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"
#include "NVIC.h"
#define LSE 0
#define LSI 1
#define HSE 2
#define RTC_CLK  LSE

enum
{
	sec=0,
	min,
	hour,
	date,
	month,
	year,
	week
};
extern uint16_t time_and_date[7];
extern char weeks[7][6];

void time_config(void);
void RTC_init(void);
uint32_t counter_IncrementCalculate(void);
void time_IncrementCalculate(void);

#ifdef __cplusplus
 }
#endif
