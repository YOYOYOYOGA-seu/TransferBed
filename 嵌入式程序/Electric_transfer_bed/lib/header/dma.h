#ifndef __DMA_H
#define __DMA_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif 
#include "stm32f10x_conf.h"

//---------------------USART_DMA����-----------------------------------
#define USB1_TTL_TX_DMA_FLAG 1     //USB1�ڶ�Ӧ�Ĵ���DMA���䷽ʽʹ��
#define USB1_TTL_RX_DMA_FLAG 0
#define USB1_TTL_TX_DMA_QUEUESSIZE 20
#define USB1_TTL_TX_DMA_CHANNEL DMA1_Channel4
#define USB1_TTL_TX_DMA_CHANNEL_IRQn DMA1_Channel4_IRQn

//-------------------------USB1�������ݶ��ж���---------------------
#define FULL 0
#define INSERTCMPLETE 1
#define EMPTY 2
#define POPCMPLETE 3
typedef struct {
	uint16_t size;
	char* BufferPoint;
	
}StringSizeAndPointer;//USB1����DMA��������ջԪ��
extern StringSizeAndPointer USART_DataQueues[USB1_TTL_TX_DMA_QUEUESSIZE];
extern uint8_t USART_QueuesRear; 
extern uint8_t USART_QueuesFront;
//-----------------------------------------------------


void USB1_TTL_SendDMAConfig(char* sendBuff,uint16_t size);
void USB1_TTL_DMA_Send(void);
uint8_t USB1_TTL_Tx_DMA_Push_Data(char* buffer,uint16_t size);
uint8_t USB1_TTL_Tx_DMA_Pop_Data(void);

#ifdef __cplusplus
 }
#endif
