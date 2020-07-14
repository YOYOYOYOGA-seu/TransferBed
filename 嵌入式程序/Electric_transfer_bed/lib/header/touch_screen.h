#ifndef __TOUCH_SCREEN_H
#define __TOUCH_SCREEN_H
#endif
#ifdef __cplusplus
 extern "C" {
#endif 
	 
#include "stm32f10x_conf.h"
//------------------------SPI参数-------------------
//默认是按照第四种模式工作的
#define TS_SPI_SPEED GPIO_Speed_10MHz  // SPI传输速度

//------------------引脚参数---------------------------	 
#define TOUCH_SCREEN_MOSI_PORT GPIOF
#define TOUCH_SCREEN_MOSI_PIN GPIO_Pin_9
#define TOUCH_SCREEN_MOSI_CLK RCC_APB2Periph_GPIOF
	 
#define TOUCH_SCREEN_MISO_PORT GPIOF
#define TOUCH_SCREEN_MISO_PIN GPIO_Pin_8
#define TOUCH_SCREEN_MISO_CLK RCC_APB2Periph_GPIOF
	 
#define TOUCH_SCREEN_SCK_PORT GPIOB
#define TOUCH_SCREEN_SCK_PIN GPIO_Pin_1
#define TOUCH_SCREEN_SCK_CLK RCC_APB2Periph_GPIOB
	 
#define TOUCH_SCREEN_CS_PORT GPIOB
#define TOUCH_SCREEN_CS_PIN GPIO_Pin_2
#define TOUCH_SCREEN_CS_CLK RCC_APB2Periph_GPIOB
//---------------------置位参数------------------------
#define TS_MOSI(a) PFout(9,a)
#define TS_MISO GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8);
#define TS_CS(a) PBout(2,a)
#define TS_SCK(a) PBout(1,a)
//---------------------控制字---------------------------
#define TS_GET_Y 0x90
#define TS_GET_X 0xD0
//--------------------触摸屏校准------------------------

#define TS_ADJUSTING_FLAG 0
#define TS_X_RADIO 1
#define TS_X_OFFSET 2
#define TS_Y_RADIO 3
#define TS_Y_OFFSET 4

extern float TS_Adjusting_cof[5];

#define SAMPLE_NUM 3   //校准采样次数
#define SAMPLE_POINT_NUM 3

#define FILTER_NUM 3
//---------------------坐标结构-------------------------
typedef struct{
	uint16_t x;
	uint16_t y;
}TS_Coord;

extern TS_Coord TS_AD_XY;
extern TS_Coord TS_XY;
//----------------------------------------------------
void TOUCH_SCREEN_init(void);
void TS_SPI_init(void);
uint8_t TS_SPI_SendByte(uint8_t data);
uint8_t TS_SPI_ReadData(void);
uint16_t TS_Read_AD(void);
TS_Coord TS_Read_Coordinate(void);
void TS_Adjusting(void);
void TS_Adjusting_test(void);
uint8_t TS_Judge_Bad_Point(TS_Coord Coord,TS_Coord pre_Coord);

#ifdef __cplusplus
 }

#endif

