/**
  ******************************************************************************
  * @file    EXTI/EXTI_Config/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_dbgmcu.h"           // Keil::Device:StdPeriph Drivers:DBGMCU
#include "common.h"

//--------------------------------key[S4] 中断------------------------------
//
void EXTI0_IRQHandler()
{
	if(IF_KEY0_DOWN)
	{
		key[0].press_flag = 1;
	}
	else
	{
		if(key[0].counter<INVALID_PRESS_COUNTER_VLAUE);
		else if(key[0].counter<LONG_PRESS_COUNTER_VALUE)
		{
#ifdef HOME_BUTTON_CMD                   //作为Home按键时
			GoHomePage();
#else
			//作为普通按键时的操作
			key[0].short_press = 1;
#endif
			
		}
		else
		{
			key[0].long_press = 0;
		}
		key[0].long_press_action = 0;
		key[0].press_flag = 0;
		key[0].counter = 0;
	}
  EXTI_ClearITPendingBit(EXTI_Line0);
}


//--------------------------------key[S1] 中断------------------------------
//
void EXTI4_IRQHandler()
{
	if(IF_KEY1_DOWN)
	{
		key[1].press_flag = 1;
	}
	else
	{
		if(key[1].counter<INVALID_PRESS_COUNTER_VLAUE);
		else if(key[1].counter<LONG_PRESS_COUNTER_VALUE)
		{
			key[1].short_press = 1;
		}
		else
		{
			key[1].long_press = 0;
		}
		key[1].long_press_action = 0;
		key[1].press_flag = 0;
		key[1].counter = 0;
	}
  EXTI_ClearITPendingBit(EXTI_Line4);
}


//--------------------------------key[S2] 中断------------------------------
//
void EXTI3_IRQHandler()
{
	if(IF_KEY2_DOWN)
	{
		key[2].press_flag = 1;
	}
	else
	{
		if(key[2].counter<INVALID_PRESS_COUNTER_VLAUE);
		else if(key[2].counter<LONG_PRESS_COUNTER_VALUE)
		{
			key[2].short_press = 1;
		}
		else
		{
			key[2].long_press = 0;
		}
		key[2].long_press_action = 0;
		key[2].press_flag = 0;
		key[2].counter = 0;
	}
  EXTI_ClearITPendingBit(EXTI_Line3);
}

//--------------------------------key[S3] 中断------------------------------
//
void EXTI2_IRQHandler()
{
	if(IF_KEY3_DOWN)
	{
		key[3].press_flag = 1;
	}
	else
	{
		if(key[3].counter<INVALID_PRESS_COUNTER_VLAUE);
		else if(key[3].counter<LONG_PRESS_COUNTER_VALUE)
		{
			key[3].short_press = 1;
		}
		else
		{
			key[3].long_press = 0;
		}
		key[3].long_press_action = 0;
		key[3].press_flag = 0;
		key[3].counter = 0;
	}
  EXTI_ClearITPendingBit(EXTI_Line2);
}


//--------------------------------TIM6 中断------------------------------
//

void TIM6_IRQHandler()
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)
	{
		int i=0;
		
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		if(currentApp == HOMEPAGE)
			ButtonPressJudgement();
		if(Period_Divide_Counter <LCD_REFRASH_PERIOD)
			Period_Divide_Counter++;
		else
		{

			Period_Divide_Counter = 0;
		}
		
		for(i=0;i<KEY_NUM;i++)
		{
			if(!key[i].long_press)
			{
				key[i].counter+=key[i].press_flag;
				if(key[i].counter > LONG_PRESS_COUNTER_VALUE)
				{
					key[i].long_press = 1;
				}
			}
		}	
		if(Period_Divide_Counter==4)
		{
			TS_Read_Coordinate();
		}		
	}
	
	
}

		
//------------------------RTC秒中断----------------------
void RTC_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_SEC)!=RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);
		RTC_WaitForLastTask();
		time_and_date[sec]++;
#ifdef TITLE_CMD
		if(ShowTitleCmd == 1)
			ShowTitle();
#endif
		if(time_and_date[sec]>=60)
		{

			time_and_date[sec] = 0;
			if(time_and_date[min] == 59)
			{
				if(time_and_date[hour] == 23)
					time_IncrementCalculate();
				else
				{
					time_and_date[hour]++;
					time_and_date[min] = 0;
				}
			}
			else
				time_and_date[min]++;
		}
	}
}

//------------------------USART1中断----------------------


//------------------------DMA1_Channel4(USB1_TTL_DMA发送)中断----------------------

