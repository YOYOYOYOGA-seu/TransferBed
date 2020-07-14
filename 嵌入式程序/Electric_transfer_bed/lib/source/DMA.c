#include "common.h"

StringSizeAndPointer USART_DataQueues[USB1_TTL_TX_DMA_QUEUESSIZE]={NULL};//USB1����DMA�������ݶ���
uint8_t USART_QueuesRear = 0; //���ж���ָ��
uint8_t USART_QueuesFront = 0; //���еײ�ָ��
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//-----------------/USB1_TTL��ӦUSARTģ���DMA-------------------//

//--------------------------USART_DMA��ʼ��-------------------------
void USB1_TTL_SendDMAConfig(char* sendBuff,uint16_t size)
{
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(USB1_TTL_TX_DMA_CHANNEL);
	DMA_InitTypeDef USB1_TTL_tx_DMA;
	
	USB1_TTL_tx_DMA.DMA_PeripheralBaseAddr = (uint32_t)&(USB1_TTL_USART_PORT->DR);
	USB1_TTL_tx_DMA.DMA_MemoryBaseAddr = (uint32_t)sendBuff;
	USB1_TTL_tx_DMA.DMA_DIR = DMA_DIR_PeripheralDST;
	USB1_TTL_tx_DMA.DMA_BufferSize = size;
	USB1_TTL_tx_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	USB1_TTL_tx_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable;
	USB1_TTL_tx_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	USB1_TTL_tx_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	USB1_TTL_tx_DMA.DMA_Mode = DMA_Mode_Normal;
	USB1_TTL_tx_DMA.DMA_Priority = DMA_Priority_Medium;
	USB1_TTL_tx_DMA.DMA_M2M = DMA_M2M_Disable;
	
	NVIC_DMA1_Channel4_init();
	DMA_Init(USB1_TTL_TX_DMA_CHANNEL,&USB1_TTL_tx_DMA);
	DMA_ITConfig(USB1_TTL_TX_DMA_CHANNEL,DMA_IT_TC,ENABLE);
	
	
}
//-----------------------------DMA�򴮿ڷ�������----------------------------
void USB1_TTL_DMA_Send()   
{
	while(DMA_GetCurrDataCounter(USB1_TTL_TX_DMA_CHANNEL));
	DMA_Cmd(USB1_TTL_TX_DMA_CHANNEL,DISABLE);
	USB1_TTL_TX_DMA_CHANNEL->CNDTR = USART_DataQueues[USART_QueuesFront].size;
	USB1_TTL_TX_DMA_CHANNEL->CMAR = (uint32_t)USART_DataQueues[USART_QueuesFront].BufferPoint;
	DMA_Cmd(USB1_TTL_TX_DMA_CHANNEL,ENABLE);
}

//--------------------------------���������������-------------------------------
uint8_t USB1_TTL_Tx_DMA_Push_Data(char* buffer,uint16_t size)     
{
	if(USART_QueuesRear == USART_QueuesFront)//���ݶ�����������
	{
		USART_DataQueues[USART_QueuesRear].BufferPoint = buffer;
		USART_DataQueues[USART_QueuesRear].size = size;
		USART_QueuesRear++;
		if(USART_QueuesRear == USB1_TTL_TX_DMA_QUEUESSIZE)
			USART_QueuesRear = 0;
		USB1_TTL_DMA_Send();
	}
	else                                       //������������
	{
		if((USART_QueuesRear+1)%USB1_TTL_TX_DMA_QUEUESSIZE == USART_QueuesFront)//���ж϶����Ƿ���
			return FULL;
		else
		{
			USART_DataQueues[USART_QueuesRear].BufferPoint = buffer;
			USART_DataQueues[USART_QueuesRear].size = size;
			USART_QueuesRear = (USART_QueuesRear+1)%USB1_TTL_TX_DMA_QUEUESSIZE;
		}
	}
	return INSERTCMPLETE;
}
//----------------------------------���е�������--------------------------------
uint8_t USB1_TTL_Tx_DMA_Pop_Data(void)        
{
	if(USART_QueuesFront == USART_QueuesRear)
		return EMPTY;
	USART_QueuesFront = (USART_QueuesFront+1)%USB1_TTL_TX_DMA_QUEUESSIZE;
	if(USART_QueuesFront == USART_QueuesRear)
		return EMPTY;
	return POPCMPLETE;
}
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
