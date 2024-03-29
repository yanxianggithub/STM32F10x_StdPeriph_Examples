/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V3.0
  * @date    2023-03-29
  * @brief   LEDӦ�ú����ӿ�
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*��������LED��GPIO�Ķ˿�ʱ��*/
		RCC_APB2PeriphClockCmd( LED_GPIO_CLK, ENABLE); 

		/*ѡ��Ҫ����LED��GPIO*/															   
		GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;	

		/*����GPIOģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*����GPIO����Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ�����Ʒ�������GPIO*/
		GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);			 
    
    /* �رշ�����*/
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);	 
}
/*********************************************END OF FILE**********************/
