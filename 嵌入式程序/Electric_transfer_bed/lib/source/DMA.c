#include "common.h"

StringSizeAndPointer USART_DataQueues[USB1_TTL_TX_DMA_QUEUESSIZE]={NULL};//USB1串口DMA发送数据队列
uint8_t USART_QueuesRear = 0; //队列顶部指针
uint8_t USART_QueuesFront = 0; //队列底部指针
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//-----------------/USB1_TTL对应USART模块的DMA-------------------//

//--------------------------USART_DMA初始化-------------------------
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
//-----------------------------DMA向串口发送数据----------------------------
void USB1_TTL_DMA_Send()   
{
	while(DMA_GetCurrDataCounter(USB1_TTL_TX_DMA_CHANNEL));
	DMA_Cmd(USB1_TTL_TX_DMA_CHANNEL,DISABLE);
	USB1_TTL_TX_DMA_CHANNEL->CNDTR = USART_DataQueues[USART_QueuesFront].size;
	USB1_TTL_TX_DMA_CHANNEL->CMAR = (uint32_t)USART_DataQueues[USART_QueuesFront].BufferPoint;
	DMA_Cmd(USB1_TTL_TX_DMA_CHANNEL,ENABLE);
}

//--------------------------------向队列中输入数据-------------------------------
uint8_t USB1_TTL_Tx_DMA_Push_Data(char* buffer,uint16_t size)     
{
	if(USART_QueuesRear == USART_QueuesFront)//数据队列中无数据
	{
		USART_DataQueues[USART_QueuesRear].BufferPoint = buffer;
		USART_DataQueues[USART_QueuesRear].size = size;
		USART_QueuesRear++;
		if(USART_QueuesRear == USB1_TTL_TX_DMA_QUEUESSIZE)
			USART_QueuesRear = 0;
		USB1_TTL_DMA_Send();
	}
	else                                       //队列中有数据
	{
		if((USART_QueuesRear+1)%USB1_TTL_TX_DMA_QUEUESSIZE == USART_QueuesFront)//先判断队列是否满
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
//----------------------------------队列弹出数据--------------------------------
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
