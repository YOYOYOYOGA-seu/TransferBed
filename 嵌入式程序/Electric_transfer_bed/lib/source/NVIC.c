#include "nvic.h"
#include "dma.h"
void NVIC_config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}


void NVIC_TIM6_init(void)
{
	NVIC_InitTypeDef TIM6_NVIC_init;
	TIM6_NVIC_init.NVIC_IRQChannel = TIM6_IRQn;
	TIM6_NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	TIM6_NVIC_init.NVIC_IRQChannelPreemptionPriority = TIM6_NVIC_PreemptionPriority;
	TIM6_NVIC_init.NVIC_IRQChannelSubPriority = TIM6_NVIC_SubPriority;
	NVIC_Init(&TIM6_NVIC_init);
	
}

void NVIC_RTC_init(void)
{
	NVIC_InitTypeDef RTC_NVIC_init;
	RTC_NVIC_init.NVIC_IRQChannel = RTC_IRQn;
	RTC_NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	RTC_NVIC_init.NVIC_IRQChannelPreemptionPriority = RTC_NVIC_PreemptionPriority;
	RTC_NVIC_init.NVIC_IRQChannelSubPriority = RTC_NVIC_SubPriority;
	NVIC_Init(&RTC_NVIC_init);
}

void NVIC_USB1_TTL_init(void)
{
	NVIC_InitTypeDef USB1_TTL_NVIC_init;
	USB1_TTL_NVIC_init.NVIC_IRQChannel = USART1_IRQn;
	USB1_TTL_NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	USB1_TTL_NVIC_init.NVIC_IRQChannelPreemptionPriority = USART1_NVIC_PreemptionPriority;
	USB1_TTL_NVIC_init.NVIC_IRQChannelSubPriority = USART1_NVIC_SubPriority;
	NVIC_Init(&USB1_TTL_NVIC_init);

}

void NVIC_DMA1_Channel4_init(void)
{
	NVIC_InitTypeDef USB1_TTL_tx_DMA_NIVC;
	USB1_TTL_tx_DMA_NIVC.NVIC_IRQChannel = USB1_TTL_TX_DMA_CHANNEL_IRQn;
	USB1_TTL_tx_DMA_NIVC.NVIC_IRQChannelCmd = ENABLE;
	USB1_TTL_tx_DMA_NIVC.NVIC_IRQChannelPreemptionPriority = DMA1_CHANNEL4_NVIC_PreemptionPriority;
	USB1_TTL_tx_DMA_NIVC.NVIC_IRQChannelSubPriority = DMA1_CHANNEL4_NVIC_SubPriority;
	NVIC_Init(&USB1_TTL_tx_DMA_NIVC);
}

void NVIC_SDIO_init(void)
{
	NVIC_InitTypeDef SDIO_NVIC; 
	SDIO_NVIC.NVIC_IRQChannel = SDIO_IRQn;
	SDIO_NVIC.NVIC_IRQChannelCmd = ENABLE;
	SDIO_NVIC.NVIC_IRQChannelPreemptionPriority = SDIO_NVIC_PreemptionPriority;
	SDIO_NVIC.NVIC_IRQChannelSubPriority = SDIO_NVIC_SubPriority;
	NVIC_Init(&SDIO_NVIC);
}
