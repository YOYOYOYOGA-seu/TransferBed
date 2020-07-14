#ifndef __NVIC_H
#define __NVIC_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_conf.h"
// key interrupt priority
#define key0_NVIC_PreemptionPriority 2
#define key1_NVIC_PreemptionPriority 2
#define key2_NVIC_PreemptionPriority 2
#define key3_NVIC_PreemptionPriority 2
#define key0_NVIC_SubPriority 0
#define key1_NVIC_SubPriority 1
#define key2_NVIC_SubPriority 2
#define key3_NVIC_SubPriority 3

#define RTC_NVIC_PreemptionPriority 1
#define RTC_NVIC_SubPriority 0

#define TIM6_NVIC_PreemptionPriority 1
#define TIM6_NVIC_SubPriority 1

#define USART1_NVIC_PreemptionPriority 1
#define USART1_NVIC_SubPriority 2


#define DMA1_CHANNEL4_NVIC_PreemptionPriority 0
#define DMA1_CHANNEL4_NVIC_SubPriority 2

#define SDIO_NVIC_PreemptionPriority 0
#define SDIO_NVIC_SubPriority 0

void NVIC_config(void);
void NVIC_TIM6_init(void);
void NVIC_RTC_init(void);
void NVIC_USB1_TTL_init(void);
void NVIC_DMA1_Channel4_init(void);
void NVIC_SDIO_init(void);
#ifdef __cplusplus
 }
#endif


