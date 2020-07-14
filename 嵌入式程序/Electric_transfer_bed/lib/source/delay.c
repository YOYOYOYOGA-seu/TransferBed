/*-------------------------------------------------------------------------------
文件名称：SysTick.c
文件描述：SysTick 系统滴答时钟1us中断函数库,中断时间可自由配置，
          常用的有 1us 10us 1ms 中断。        
备    注：程序默认使用72M时钟，无分频 
---------------------------------------------------------------------------------*/
#include "delay.h"

 uint32_t TimingDelay[10];// 延时栈（防止多次调用延时函数时中断中的延时会把程序中延时的技术冲掉
 uint16_t TimingDelayPtr = 0;//
/*-------------------------------------------------------------------------------
程序名称：SysTick_Init
程序描述：启动系统滴答定时器 SysTick
输入参数：无
返回参数：无
备    注：使用此功能之前需要调用此函数，初始化寄存器等参数
---------------------------------------------------------------------------------*/
void SysTick_Init(void)
{
	 // SystemFrequency / 1000     1ms中断一次
	 // SystemFrequency / 100000	 10us中断一次
	 // SystemFrequency / 1000000  1us中断一次
	 
	if (SysTick_Config(SystemCoreClock / 1000000))	// 1us ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
}


/*-------------------------------------------------------------------------------
程序名称：Delay_us
程序描述：延时nTime us  
输入参数：nTime
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void Delay_us(uint32_t nTime)
{ 
		
	if( TimingDelay[TimingDelayPtr] >= 1 )
		TimingDelayPtr ++ ;
	for(TimingDelay[TimingDelayPtr]  = (SystemCoreClock / 72000000)*nTime;TimingDelay[TimingDelayPtr] >= 1;TimingDelay[TimingDelayPtr] -- )
	{   
	}
	if(TimingDelayPtr > 0 )
	{
		TimingDelayPtr --;
	}
}

/*-------------------------------------------------------------------------------
程序名称：TimingDelay_Decrement
程序描述：数字递减直到0  
输入参数：无
返回参数：无
备    注：需要在中断函数SysTick_Handler()中调用
---------------------------------------------------------------------------------*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay[TimingDelayPtr]--;
	}
}
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/

