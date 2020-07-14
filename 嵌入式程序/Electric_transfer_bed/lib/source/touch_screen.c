#include "common.h"

TS_Coord TS_AD_XY={0,0};   //xpt2048返回AD值


TS_Coord TS_XY={0,0};    //由AD值换算成的坐标值
TS_Coord TS_XY_pre={0,0};  //上一次采样坐标值，由于比较判断飞点

TS_Coord TS_Sample_Coord[SAMPLE_POINT_NUM] = {40,40,40,280,200,280};   //触摸屏校准校准点坐标
float TS_Adjusting_cof[5] = {0,0.117,0,-0.156,320};     //由AD值转化为坐标值时的一次函数系数

//--------------------------触摸屏初始化--------------------------------
void TOUCH_SCREEN_init(void)
{
	float temp;
	TS_SPI_init();
	FLASH_Read_32(TS_ADJUSTING_DATA_ADDRESS,(uint32_t*)(&temp),1);
	if(temp == 1)
	{
		FLASH_Read_32(TS_ADJUSTING_DATA_ADDRESS,(uint32_t*)TS_Adjusting_cof,5);
	}
}

//-------------------------触摸屏SPI(IO模拟)初始化-------------------------
void TS_SPI_init()
{
	RCC_APB2PeriphClockCmd(TOUCH_SCREEN_MISO_CLK|TOUCH_SCREEN_MOSI_CLK|
													TOUCH_SCREEN_SCK_CLK|TOUCH_SCREEN_CS_CLK,ENABLE);
	
	GPIO_InitTypeDef MY_SPI_GPIO_init;
	
	MY_SPI_GPIO_init.GPIO_Speed = TS_SPI_SPEED;
	MY_SPI_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	MY_SPI_GPIO_init.GPIO_Pin = TOUCH_SCREEN_MOSI_PIN;
	GPIO_Init(TOUCH_SCREEN_MOSI_PORT,&MY_SPI_GPIO_init);
	
	MY_SPI_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	MY_SPI_GPIO_init.GPIO_Pin = TOUCH_SCREEN_CS_PIN;
	GPIO_Init(TOUCH_SCREEN_CS_PORT,&MY_SPI_GPIO_init);

	MY_SPI_GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	MY_SPI_GPIO_init.GPIO_Pin = TOUCH_SCREEN_SCK_PIN;
	GPIO_Init(TOUCH_SCREEN_SCK_PORT,&MY_SPI_GPIO_init);
	
	MY_SPI_GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	MY_SPI_GPIO_init.GPIO_Pin = TOUCH_SCREEN_MISO_PIN;
	GPIO_Init(TOUCH_SCREEN_MISO_PORT,&MY_SPI_GPIO_init);
	TS_SCK(0);
	TS_MOSI(0);
	TS_CS(1);
}

//------------------向xpt2046芯片发送一字节数据----------------------------
uint8_t TS_SPI_SendByte(uint8_t data)
{
	uint8_t i=0;
	uint8_t temp = 0;
	TS_SCK(0);
	Delay_us(5);
	for(i=0;i<8;i++)
	{
		if(data&0x80)
			TS_MOSI(1);
		else
			TS_MOSI(0);
		data<<=1;
		TS_SCK(1);
		Delay_us(5);
		temp<<=1;       //接收数据要先左移，否则最后得到9位（最后一次不需左移）
		temp+=TS_MISO;
		TS_SCK(0);
		Delay_us(5);
	}
	return temp;
	
}

//----------------------读取1字节数据----------------------------------
uint8_t TS_SPI_ReadData()
{
	return TS_SPI_SendByte(0x00);
}


//------------------读取xpt2046AD数据-----------------------------
 uint16_t TS_Read_AD(void)
 {
	 uint8_t i=0;
	 uint16_t temp;
	 TS_MOSI(0);
	 Delay_us(5);
	 for(i=0;i<12;i++)
	 {

		 temp<<=1;
		 temp+=TS_MISO;
		 Delay_us(1);
		 TS_SCK(1);
		 Delay_us(1);
		 TS_SCK(0);
		 
	 }
	 temp&=0xFFF;
	 return temp;
 }

//-------------------------读取触摸屏坐标-----------------------------
TS_Coord TS_Read_Coordinate()
{
	uint8_t i = 0;
	TS_AD_XY.x = 0;
	TS_AD_XY.y = 0;
	for(i = 0;i<FILTER_NUM;i++)
	{
		TS_SCK(0);
		TS_MOSI(0);
		TS_CS(0);
		TS_SPI_SendByte(TS_GET_X);
		Delay_us(1);
		TS_AD_XY.x += TS_Read_AD()/FILTER_NUM;
		TS_CS(1);
		Delay_us(1);
		TS_SCK(0);
		TS_MOSI(0);
		TS_CS(0);
		TS_SPI_SendByte(TS_GET_Y);
		Delay_us(1);
		TS_AD_XY.y += TS_Read_AD()/FILTER_NUM;
		TS_CS(1);
	}
	/*
	if(TS_AD_XY.y>=2040||TS_AD_XY.x<=3)
	{

		TS_AD_XY.y=2047;
		TS_AD_XY.x=0;
	}
	*/

	
	if(!lcddev.dir)//横屏和竖屏坐标转换
	{
		TS_XY.x = TS_Adjusting_cof[1]*TS_AD_XY.x + TS_Adjusting_cof[2];
		TS_XY.y = TS_Adjusting_cof[3]*TS_AD_XY.y + TS_Adjusting_cof[4];
		if(TS_XY.x<= 1 ||TS_XY.y <=1)
		{
			TS_XY.x = 0;
			TS_XY.y = 0;
		}
	}
	else
	{
		TS_XY.y = TS_Adjusting_cof[1]*TS_AD_XY.x + TS_Adjusting_cof[2];
		TS_XY.x =320 - (TS_Adjusting_cof[3]*TS_AD_XY.y + TS_Adjusting_cof[4]);
		if(TS_XY.x >= 319)   //横屏时坐标原点为左下角，要做变换
		{
			TS_XY.x = 0;
		}
	}
	return TS_XY;
}

//---------------------触摸屏校准------------------------------------
void TS_Adjusting()
{
	
	uint8_t i=0;
	uint8_t j=0;
	uint16_t AD_X_Temp[SAMPLE_NUM] = {0};
	uint16_t AD_Y_Temp[SAMPLE_NUM] = {0};
	LCD_Clear(WHITE);
	POINT_COLOR = RED;
	for(i=0;i<SAMPLE_NUM;i++)
	{
		for(j=0;j<3;j++)
		{
			LCD_DrawLine(TS_Sample_Coord[j].x,TS_Sample_Coord[j].y+20,TS_Sample_Coord[j].x,TS_Sample_Coord[j].y-20);
			LCD_DrawLine(TS_Sample_Coord[j].x+20,TS_Sample_Coord[j].y,TS_Sample_Coord[j].x-20,TS_Sample_Coord[j].y);
			while(1)
			{
				TS_Read_Coordinate();
				if(TS_XY.y<(TS_Sample_Coord[j].y + 30)&&TS_XY.y>(TS_Sample_Coord[j].y - 30)&&TS_XY.x<(TS_Sample_Coord[j].x + 30)&&TS_XY.x>(TS_Sample_Coord[j].x - 30))
					break;
				else
					Delay_ms(1);
			}
			AD_X_Temp[j] += TS_AD_XY.x/3;
			AD_Y_Temp[j] += TS_AD_XY.y/3;
			LCD_Clear(WHITE);
		}
	}
	
	TS_Adjusting_cof[0] = 1;
	TS_Adjusting_cof[1] = (float)(TS_Sample_Coord[2].x-TS_Sample_Coord[1].x)/(AD_X_Temp[2]-AD_X_Temp[1]);
	TS_Adjusting_cof[2] = TS_Sample_Coord[1].x - TS_Adjusting_cof[1]*AD_X_Temp[1];
	TS_Adjusting_cof[3] = (float)(TS_Sample_Coord[1].y-TS_Sample_Coord[0].y)/(AD_Y_Temp[1]-AD_Y_Temp[0]);
	TS_Adjusting_cof[4] = TS_Sample_Coord[0].y - TS_Adjusting_cof[3]*AD_Y_Temp[0];
	
	POINT_COLOR = BLACK;
	
	if(FLASH_Erase(TS_ADJUSTING_DATA_ADDRESS,TS_ADJUSTING_DATA_SIZE) == FLASH_COMPLETE)
	{
		if(FLASH_WriteData_32(TS_ADJUSTING_DATA_ADDRESS,(uint32_t*)TS_Adjusting_cof,5) == FLASH_COMPLETE)
			LCD_ShowString(20,200,200,20,12,"Touch_screen_adjusting_complete!",0);
		else
			LCD_ShowString(20,200,200,20,12,"Touch_screen_adjusting_error!",0);
	}
	else
		LCD_ShowString(20,200,200,20,12,"Touch_screen_adjusting_error!",0);
	Delay_ms(1500);
	LCD_Clear(WHITE);
	
}
//------------------------------------------触摸屏手写测试-----------------------------------------------------
void TS_Adjusting_test()
{
	uint16_t color;

	LCD_Clear(WHITE);
	for(color = 0; color<0xFBFF;color +=327)
	{
		POINT_COLOR = color;
		LCD_DrawLine(20+color/327,10,20+color/327,20);
	}
	POINT_COLOR = BLACK;
	
	while(currentApp == DRAWING)
	{
		while(TS_Judge_Bad_Point(TS_Read_Coordinate(),TS_XY_pre));
		if(TS_XY.y < 40)
		{
			if(TS_XY.x <220&&TS_XY.x>20)
				POINT_COLOR = TS_XY.x*327;
		}
		else if(TS_XY.y>280)
		{
			if(TS_XY.x <220&&TS_XY.x>180)
			{
				TS_Adjusting();
				for(color = 0; color<0xFBFF;color +=327)
				{
					POINT_COLOR = color;
					LCD_DrawLine(20+color/327,10,20+color/327,20);
				}
				POINT_COLOR = BLACK;
			}
		}
		else
			LCD_DrawLine(TS_XY.x,TS_XY.y,TS_XY_pre.x,TS_XY_pre.y);
		Delay_us(100);
		
	}
	POINT_COLOR = BLACK;
	LCD_Clear(WHITE);
	
}
//------------------------------------------触摸屏飞点过滤-----------------------------------------------------
uint8_t TS_Judge_Bad_Point(TS_Coord Coord,TS_Coord pre_Coord)
{
	
	if(((int)Coord.x - (int)pre_Coord.x)>3||((int)Coord.x - (int)pre_Coord.x)<-3||((int)Coord.y - (int)pre_Coord.y)>3||((int)Coord.y - (int)pre_Coord.y)<-3)
	{
		TS_XY_pre = TS_XY;
		return 1;
	}
	else 
	{
		TS_XY_pre = TS_XY;
		return 0;
	}
}
