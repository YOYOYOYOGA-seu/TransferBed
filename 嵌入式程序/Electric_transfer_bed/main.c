#include "common.h"

void key_action(void);
void init_all(void);

void (*appProgramPtr)(void) = HomePage;
char usart_DMA_test[]={"USART_DMA_TEST"};



int main()
{
	
	Delay_ms(5000);
	init_all();
	//IfNoHomePage();
	
	while(1)
	{
		appProgramPtr();
		//key_action();
	}
}



void init_all()
{

	LED3_ON;
	LED2_OFF;
	__disable_irq();
	LCD_DisplayOff();
	LCD_Init();
	LCD_LED_ON;
	LCD_Clear(WHITE);
	LCD_DisplayOn();
	NVIC_config();
	led_init();
	key_init();
	TIM6_init();
	TOUCH_SCREEN_init();
	RTC_init();
	LCD_Clear(WHITE);
	time_config();
	LED2_ON;
	LED3_OFF;
	MOTOR_init();
	LS_init();
	__enable_irq();
	
	SD_fs_test();               //ª∂”≠ΩÁ√Ê
}


void key_action()
{
	if(key[S1].short_press)
	{
		key[S1].short_press = 0;
		BedPlateMove(MOVE_OUT);
	}
	else if(key[S2].short_press)
	{
		key[S2].short_press = 0;
		BedPlateMove(MOVE_IN);
	}
	else if(key[S3].short_press)
	{
		key[S3].short_press = 0;
		BedPlateMove(MOVE_STOP);
	}
	
		
}
