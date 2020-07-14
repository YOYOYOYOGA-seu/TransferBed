#ifndef __SCCB_H
#define __SCCB_H
#ifdef __cplusplus
 extern "C" {
#endif 

#include "common.h"
#define SCCB_SCL_PIN GPIO_Pin_3
#define SCCB_SCL_POART GPIOD
#define SCCB_SCL_CLK	RCC_APB2Periph_GPIOD 
#define SCCB_SDA_PIN GPIO_Pin_13
#define SCCB_SDA_POART GPIOG
#define SCCB_SDA_CLK  RCC_APB2Periph_GPIOD
//----------------SCL和SDA操作指令------------------------
#define SCCB_SCL_HIGH PDout(3,1)
#define SCCB_SCL_LOW PDout(3,0) 
	 
#define SCCB_SDA_HIGH PGout(13,1)
#define SCCB_SDA_LOW PGout(13,0) 
#define SCCB_SDA_READ PGin(13)
#define SCCB_SDA_OUT()  {GPIOG->CRH&=0xFF0FFFFF;GPIOG->CRH|=0x00300000;}
#define SCCB_SDA_IN()  {GPIOG->CRH&=0xFF0FFFFF;GPIOG->CRH|=0x00800000;}
//-----------------OV7725的SCCB读写ID-----------------------
#define SCCB_ID_WRITE 0x42   //ov7725的ID为0x42，ID地址byte的组成为ID(7位)+1位（读写控制），固读的时候位0x43
#define SCCB_ID_READ 0x43
//----------------------------------------------------------
typedef enum
{
	SCCB_OK = 0,
	SCCB_BYTE_WRITE_ERROR,
	SCCB_REG_WRITE_ERROR
}SCCB_RES;

void SCCB_init(void);
void SCCB_Start(void);
void SCCB_Ack(void);
void SCCB_Stop(void);
SCCB_RES SCCB_SendByte(uint8_t data);
uint8_t SCCB_ReadByte(void);	 
SCCB_RES SCCB_Write_Reg(uint8_t addr,uint8_t data);
uint8_t SCCB_Read_Reg(uint8_t addr);

	 
#ifdef __cplusplus
 }

#endif
#endif