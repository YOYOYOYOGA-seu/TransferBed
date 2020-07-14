#ifndef __USART_H
#define __USART_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x_conf.h"

#define USB1_TTL_BAUDRATE 9600
#define USB1_TTL_MODE USART_Mode_Rx|USART_Mode_Tx
#define USB1_TTL_USART_PORT USART1
#define USB1_TTL_USART_CLK RCC_APB2Periph_USART1

#define USB1_TTL_RX_PIN GPIO_Pin_10
#define USB1_TTL_TX_PIN GPIO_Pin_9
#define USB1_TTL_GPIO_PORT GPIOA

#define USB1_TTL_GPIO_CLK RCC_APB2Periph_GPIOA

	 
extern char usart_test;
void USART_init(void);
void  USART_sendString(USART_TypeDef* USARTx,char* str,uint8_t num);
#ifdef __cplusplus
 }
#endif
