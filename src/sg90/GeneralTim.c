
#include "GeneralTim.h" 
#include <math.h>
#include <stdlib.h>
#include "usart.h"

static void GENERAL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	// ����Ƚ�ͨ��3 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);

}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = 0.5/20.0*GENERAL_TIM_Period;	// ռ�ձ�����
	TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_Mode_Config();		
}

/**
  * @brief  ���ö��ռ�ձ�
  * @param  angle: ռ�ձȣ���0.5/20.0*PWM_PERIOD_COUNT �� 2.5/20.0*PWM_PERIOD_COUNT��
  * @retval ��
  */
void set_steering_gear_dutyfactor(uint16_t dutyfactor)
{
  #if 1
  {
    /* �Գ�����Χ��ռ�ձȽ��б߽紦�� */
    dutyfactor = 0.5/20.0*GENERAL_TIM_Period > dutyfactor ? 0.5/20.0*GENERAL_TIM_Period : dutyfactor;
    dutyfactor = 2.5/20.0*GENERAL_TIM_Period < dutyfactor ? 2.5/20.0*GENERAL_TIM_Period : dutyfactor;
  }
  #endif
  
  TIM_SetCompare3(TIM4, dutyfactor);
}

/**
  * @brief  ���ö���Ƕ�
  * @param  angle: �Ƕȣ���0 �� 180�����Ϊ0��-180�㣩��
  * @retval ��
  */
void set_steering_gear_angle(uint16_t angle_temp)
{
  angle_temp = (0.5 + angle_temp / 180.0 * (2.5 - 0.5)) / 20.0 * GENERAL_TIM_Period;    // ����Ƕȶ�Ӧ��ռ�ձ�
  
  set_steering_gear_dutyfactor(angle_temp);    // ����ռ�ձ�
}

/**
  * @brief  ��ӡ��������
  * @param  ��
  * @retval ��
  */
void show_help(void)
{
    printf("��������(<>�ڵ����ݣ��Իس�����)��\n\r");
    printf("<?>       -�����˵�\n\r");
    printf("<a+�Ƕ�>  -���ö���ĽǶȣ���Χ��%d��%d����ʹ�ÿո����+��\n\r", 0, 180);
}


extern uint16_t ChannelPulse;

/**
  * @brief  �����ڽ��յ�������
  * @param  ��
  * @retval ��
  */
void deal_serial_data(void)
{
    int angle_temp=0;
    
    //���յ���ȷ��ָ���Ϊ1
    char okCmd = 0;

    //����Ƿ���յ�ָ��
    if(receive_cmd == 1)
    {
      if(UART_RxBuffer[0] == 'a' || UART_RxBuffer[0] == 'A')
      {
        //�����ٶ�
        if(UART_RxBuffer[1] == ' ')
        {
          angle_temp = atoi((char const *)UART_RxBuffer+2);
          if(angle_temp>=0 && angle_temp <= 180)
          {
            printf("\n\r�Ƕ�: %d\n\r", angle_temp);
            ChannelPulse = (0.5 + angle_temp / 180.0 * (2.5 - 0.5)) / 20.0 * GENERAL_TIM_Period;    // ���°�ť���Ƶ�ռ�ձ�
            set_steering_gear_angle(angle_temp);
//            printf("\n\r�Ƕ�: %d\n\r", (uint16_t)(angle_temp/PWM_PERIOD_COUNT*20.0/(2.5-0.5)*180.0));
            okCmd = 1;
          }
        }
      }
      else if(UART_RxBuffer[0] == '?')
      {
        //��ӡ��������
        show_help();
        okCmd = 1;
      }
      //���ָ���������ӡ��������
      if(okCmd != 1)
      {
        printf("\n\r ������������������...\n\r");
        show_help();
      }

      //��մ��ڽ��ջ�������
      receive_cmd = 0;
      uart_FlushRxBuffer();

    }
}

/*********************************************END OF FILE**********************/
