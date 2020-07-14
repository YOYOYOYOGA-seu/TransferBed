#include "common.h"
uint8_t reset_flag = 0;
uint16_t time_and_date[7] ={0,0,0,0,0,0,0};
uint16_t normal_year_month[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
uint16_t leap_year_month[13] = {0,31,60,91,121,152,182,213,244,274,305,335,366};
uint16_t time_init[7] ={0,0,0,1,1,2017,0};
uint16_t time_set[7] = {0,0,0,1,1,2017,0};
char weeks[7][6] = {"Sun.","Mon.","Tues.","Wed.","Thur.","Fri.","Sat."};
void time_config()
{
	uint8_t i=0;
	
	if(reset_flag)   //如果RTC复位，则初始化时间，否则从RTC计数器中读取时间
	{
		for(i=0;i<7;i++)
			time_and_date[i] = time_init[i];
		RTC_SetCounter(0x00);
	}
	else
	
		time_IncrementCalculate();
		
	
	
}

void RTC_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);//开BKP、PWR时钟
	PWR_BackupAccessCmd(ENABLE); //使能RTC和备份寄存器的访问
	
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x0328)    //上点检查BKP标志位是否还在，若不再则说明BKP和RTC复位，要重新设置，
	{																									//否则不可重新初始化BKP和设置RTC
		BKP_DeInit();
		reset_flag = 1;    //标志位，表示RTC是否发生复位
		BKP_WriteBackupRegister(BKP_DR1,0x0328);
		if(RTC_CLK == LSE||RTC_CLK == LSI)//设置分频系数，达到1hz
			RTC_SetPrescaler(32767);
		else
			RTC_SetPrescaler(62498);
	RTC_WaitForLastTask();
	}
		//复位BKP为默认值
	
	
	if(RTC_CLK == LSE)
	{
		RCC_LSEConfig(RCC_LSE_Bypass);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	}
	else if(RTC_CLK == LSI)
	{
		RCC_LSICmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET){}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	}
	else
	{
		RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
	}
	RCC_RTCCLKCmd(ENABLE);  //是能RTC时钟
	RTC_WaitForSynchro();  //等待RTC时钟与APB时钟同步
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC,ENABLE); //使能秒中断
	//RTC_ITConfig(RTC_IT_ALR);  //使能闹钟中断
	RTC_WaitForLastTask();
	NVIC_RTC_init();
}


void time_IncrementCalculate() //从计数器中读取时间
{
	uint8_t i;
	uint32_t counter;
	uint16_t inc_year;
//	uint16_t leap_year;
	counter = RTC_GetCounter();
	time_and_date[sec] = counter%60;
	counter /= 60;
	time_and_date[min] = counter%60;
	counter /= 60;
	time_and_date[hour] = counter%24;
	counter /= 24;
	time_and_date[week] = counter%7;
	inc_year = ((counter+1)<<2)/1461;
	time_and_date[year] = 2017 + inc_year;
  counter -= inc_year *365.25;
	if(time_and_date[year]%4 == 0)
	{
		for(i=0;i<13;i++)
		{
			if(counter<leap_year_month[i])
			{
				time_and_date[month] = i;
				time_and_date[date] = counter-leap_year_month[i-1]+1;
				break;
			}
		}
	}
	else
	{
		for(i=0;i<13;i++)
		{
			if(counter<normal_year_month[i])
			{
				time_and_date[month] = i;
				time_and_date[date] = counter-normal_year_month[i-1]+1;
				break;
			}
		}
	}
}



uint32_t counter_IncrementCalculate()  //根据设置的时间计算寄存器需要设置的时间
{
	uint32_t counter = 0;
	counter+= (time_set[year]-time_init[year])*365.25;
	if(time_set[year]%4 == 0)
		counter +=leap_year_month[time_set[month]];
	else
	  counter +=normal_year_month[time_set[month]];
	counter +=time_set[date]-1;
	counter*=24;
	counter+=time_set[hour];
	counter*=3600;
	counter+=60*time_set[min]+time_set[sec];
	return counter;
}

