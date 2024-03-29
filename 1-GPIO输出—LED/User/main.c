/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "./led/bsp_led.h"

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED GPIO ��ʼ�� */
	LED_GPIO_Config();	
	
	while(1)
	{		
		LED( OFF ); 			  // ��
		Delay(0x0FFFFF);	
		LED( ON );		  // ����
		Delay(0x0FFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
