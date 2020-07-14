#include "common.h"

KEY key[KEY_NUM]={0};


void key_struct_init()
{
	int i=0;
	for(i=0;i<KEY_NUM;i++)
	{
		//////////////////key_GPIO init_strcut 
		key[i].key_GPIO_port = GPIOE;
		key[i].key_GPIO_init.GPIO_Mode = GPIO_Mode_IPU;
		key[i].key_GPIO_init.GPIO_Speed = GPIO_Speed_2MHz;
	   ///////////////key_EXTI init_strcut init
		key[i].key_EXTI_init.EXTI_LineCmd= ENABLE;
		key[i].key_EXTI_init.EXTI_Mode = EXTI_Mode_Interrupt;
		key[i].key_EXTI_init.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
		////////////////key_NVIC init_strcut init
		key[i].key_NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	}
	////////////////////////////////key0_GPIO init_strcut 
	key[0].key_GPIO_port = GPIOA;
	key[0].key_GPIO_init.GPIO_Mode = GPIO_Mode_IPD;
	
	key[0].key_GPIO_init.GPIO_Pin = GPIO_Pin_0;
	key[1].key_GPIO_init.GPIO_Pin = GPIO_Pin_4;
	key[2].key_GPIO_init.GPIO_Pin = GPIO_Pin_3;
	key[3].key_GPIO_init.GPIO_Pin = GPIO_Pin_2;
	
	key[0].GPIO_Por = GPIO_PortSourceGPIOA;
	key[1].GPIO_Por = GPIO_PortSourceGPIOE;
	key[2].GPIO_Por = GPIO_PortSourceGPIOE;
	key[3].GPIO_Por = GPIO_PortSourceGPIOE;
	
	key[0].GPIO_pin = GPIO_PinSource0;
	key[1].GPIO_pin = GPIO_PinSource4;
	key[2].GPIO_pin = GPIO_PinSource3;
	key[3].GPIO_pin = GPIO_PinSource2;
	
	///////////////////////////////key_EXTI init_strcut 
	key[0].key_EXTI_init.EXTI_Line = EXTI_Line0;
	key[1].key_EXTI_init.EXTI_Line = EXTI_Line4;
	key[2].key_EXTI_init.EXTI_Line = EXTI_Line3;
	key[3].key_EXTI_init.EXTI_Line = EXTI_Line2;
	
	/////////////////////////////////key_NVIC init_strcut init
	key[0].key_NVIC_init.NVIC_IRQChannel = EXTI0_IRQn;
	key[1].key_NVIC_init.NVIC_IRQChannel = EXTI4_IRQn;
	key[2].key_NVIC_init.NVIC_IRQChannel = EXTI3_IRQn;
	key[3].key_NVIC_init.NVIC_IRQChannel = EXTI2_IRQn;
	
	key[0].key_NVIC_init.NVIC_IRQChannelPreemptionPriority = key0_NVIC_PreemptionPriority;
	key[1].key_NVIC_init.NVIC_IRQChannelPreemptionPriority = key1_NVIC_PreemptionPriority;
	key[2].key_NVIC_init.NVIC_IRQChannelPreemptionPriority = key2_NVIC_PreemptionPriority;
	key[3].key_NVIC_init.NVIC_IRQChannelPreemptionPriority = key3_NVIC_PreemptionPriority;
	
	key[0].key_NVIC_init.NVIC_IRQChannelSubPriority = key0_NVIC_SubPriority;
	key[1].key_NVIC_init.NVIC_IRQChannelSubPriority = key1_NVIC_SubPriority;
	key[2].key_NVIC_init.NVIC_IRQChannelSubPriority = key2_NVIC_SubPriority;
	key[3].key_NVIC_init.NVIC_IRQChannelSubPriority = key3_NVIC_SubPriority;
}

void key_init()
{
	int i=0;
	key_struct_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	for(i=0;i<KEY_NUM;i++)
	{
		
		GPIO_Init(key[i].key_GPIO_port,&key[i].key_GPIO_init);
		GPIO_EXTILineConfig(key[i].GPIO_Por,key[i].GPIO_pin);
		EXTI_Init(&key[i].key_EXTI_init);
		NVIC_Init(&key[i].key_NVIC_init);
		
	}
	
	
}
