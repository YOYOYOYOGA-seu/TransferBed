#include "common.h"

char usart_test = '0'; //用于测试usart单字节接受，显示在频幕上

void USART_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_Cmd(USB1_TTL_USART_PORT,ENABLE);
	USART_InitTypeDef USB1_TTL_USART_init;
	GPIO_InitTypeDef USB1_TTL_GPIO_init;

	USB1_TTL_USART_init.USART_BaudRate = USB1_TTL_BAUDRATE;
	USB1_TTL_USART_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USB1_TTL_USART_init.USART_Mode = USB1_TTL_MODE;
	USB1_TTL_USART_init.USART_Parity = USART_Parity_No;
	USB1_TTL_USART_init.USART_StopBits = USART_StopBits_1;
	USB1_TTL_USART_init.USART_WordLength = USART_WordLength_8b;
	
	USB1_TTL_GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	USB1_TTL_GPIO_init.GPIO_Pin = USB1_TTL_TX_PIN;
	USB1_TTL_GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USB1_TTL_GPIO_PORT,&USB1_TTL_GPIO_init);
	USB1_TTL_GPIO_init.GPIO_Pin = USB1_TTL_RX_PIN;
	USB1_TTL_GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USB1_TTL_GPIO_PORT,&USB1_TTL_GPIO_init);
	
	NVIC_USB1_TTL_init();
	USART_Init(USB1_TTL_USART_PORT,&USB1_TTL_USART_init);
	USART_ITConfig(USB1_TTL_USART_PORT,USART_IT_RXNE,ENABLE);
	if(USB1_TTL_TX_DMA_FLAG)
	{
		USB1_TTL_SendDMAConfig(NULL,0);
		USART_DMACmd(USB1_TTL_USART_PORT,USART_DMAReq_Tx,ENABLE);
	}
	if(USB1_TTL_RX_DMA_FLAG)
	{
		USART_DMACmd(USB1_TTL_USART_PORT,USART_DMAReq_Rx,ENABLE);
	}
}

void USART_sendString(USART_TypeDef* USARTx,char* str,uint8_t num)
{
	uint8_t i;
	for(i = 0;i<num;i++)
	{
		if(str[i] == '\0')
			break;
		USART_SendData(USARTx,str[i]);
	}
}

