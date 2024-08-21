/**
  ******************************************************************************
  * @file    systick.c
  * @author  
  * @version V1.0
  * @date    2023-xx-xx
  * @brief   SysTick 系统滴答时钟1ms中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  */
  
#include "systick.h"

static __IO u32 TimingDelay;
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   ms延时程序,1ms为一个单位
  * @param  
  *		@arg nTime: Delay_ms( 1 ) 则实现的延时为 1 * 1ms = 1ms
  * @retval  无
  */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}

/**
  * @brief   1s延时程序
  * @param  
  *		@arg nTime: Delay_s( 1 ) 则实现的延时为 1 000* 1ms = 1s
  * @retval  无
  */
void Delay_s(unsigned int ms)
{ 
	unsigned char i;
	for(i=0;i<ms;ms--)
		{
		Delay_ms(1000);
		}
}


/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
