#include "sccb.h"

void SCCB_init(void)
{
	RCC_APB2PeriphClockCmd(SCCB_SCL_CLK|SCCB_SDA_CLK,ENABLE);
	GPIO_InitTypeDef SCCB_GPIO_Init;
	SCCB_GPIO_Init.GPIO_Pin = SCCB_SCL_PIN;
	SCCB_GPIO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	SCCB_GPIO_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCCB_SCL_POART,&SCCB_GPIO_Init);
	
	SCCB_GPIO_Init.GPIO_Pin = SCCB_SDA_PIN;
	GPIO_Init(SCCB_SDA_POART,&SCCB_GPIO_Init);
	
}

void SCCB_Start(void)
{
	SCCB_SCL_HIGH;
	SCCB_SDA_HIGH;
	Delay_us(20);
	SCCB_SDA_LOW;
	Delay_us(20);
	SCCB_SCL_LOW;
}


void SCCB_Stop(void)
{
	SCCB_SDA_LOW;
	SCCB_SCL_HIGH;
	Delay_us(20);
	SCCB_SDA_HIGH;
	Delay_us(20);
}

void SCCB_Ack(void)
{
	Delay_us(20);
	SCCB_SDA_HIGH;
	SCCB_SCL_HIGH;
	Delay_us(20);
	SCCB_SCL_LOW;
	SCCB_SDA_LOW;
}

SCCB_RES SCCB_SendByte(uint8_t data)
{
	uint16_t i;
	for(i = 0;i<8;i++)
	{
		
		if(data&(1<<i))
			SCCB_SDA_HIGH;
		else
			SCCB_SDA_LOW;
		Delay_us(20);
		SCCB_SCL_HIGH;
		Delay_us(20);
		SCCB_SCL_LOW;
	}
	//校验数据发送是否成功
	SCCB_SDA_IN();//读数据
	Delay_us(20);
	SCCB_SCL_HIGH;
	Delay_us(20);
	SCCB_SCL_LOW;
	SCCB_SDA_OUT();
	if(SCCB_SDA_READ)
		return SCCB_BYTE_WRITE_ERROR;
	else
		return SCCB_OK;
}

uint8_t SCCB_ReadByte(void)
{
	SCCB_SDA_IN();
	uint8_t temp = 0;
	uint16_t i;
	for(i = 0;i<8;i++)
	{
		Delay_us(20);
		SCCB_SCL_HIGH;
		temp|=(SCCB_SDA_READ << i);
		Delay_us(20);
		SCCB_SCL_LOW;
	}
	SCCB_SDA_OUT();
}

SCCB_RES SCCB_Write_Reg(uint8_t addr,uint8_t data)
{
	SCCB_RES res;
	if(SCCB_SendByte(SCCB_ID_WRITE))
}
uint8_t SCCB_Read_Reg(uint8_t addr);
