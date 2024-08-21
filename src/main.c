#include "stm32f10x.h"
//#include "timerbase.h" 
//#include "advanceTim.h" 
//#include "generalTim.h" 
#include "systick.h"
//#include "usart.h"
//#include "key.h"
#include "led.h"
//#include "oled.h"
//#include "adc.h"
#include "internal_flash.h"   
//add by yanxcg,2024-07-21 13:59:49 --> oled
//extern const unsigned char BMP1[];
//extern const unsigned char BMP2[];
//add by yanxcg,2024-07-21 13:59:55 --> adc
//extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
// 局部变量，用于保存转换计算后的电压值
//float ADC_ConvertedValueLocal[NOFCHANEL];
//add by yanxcg,2024-07-21 21:51:07 --> timerbase
//volatile uint32_t time = 0;     // ms 计时变量 

int main()
{
    //SysTick_Init();
    // Key_GPIO_Config();
    LED_GPIO_Config();
    //USART_Config();
    //I2C_Configuration(); // 配置CPU的硬件I2C
    //OLED_Init();         // 初始化OLED
    //ADCx_Init();
    //BASIC_TIM_Init();
    //ADVANCE_TIM_Init();
    //GENERAL_TIM_Init();

    if(InternalFlash() == PASSED)
	{
		LED_GREEN;
		printf("读写内部FLASH测试成功\r\n");

	}
	else
	{
		printf("读写内部FLASH测试失败\r\n");
		LED_RED;
	}
    while (1) {



/*
        if ( time >= 1000 )  //1000 * 1 ms = 1s 时间到 
        {
            time = 0;
            // LED1 取反     
            LED1_TOGGLE; 
        } 
*/  
        /*
        Delay_s(5);
        ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
        ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
        ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
        ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
        ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
        ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;

        printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
        printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
        printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
        printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
        printf("\r\n CH4 value = %f V \r\n",ADC_ConvertedValueLocal[4]);
        printf("\r\n CH5 value = %f V \r\n",ADC_ConvertedValueLocal[5]);

        printf("\r\n\r\n");
        */
        // OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP2);//测试BMP位图显示

        /*Delay_ms(200);		// 200ms
        OLED_SetPos(128,64);
        for(int n=0;n<128;n++)
            {
                WriteDat(32);
            }
        Delay_ms(200);
        OLED_CLS();
    */
        /*
        OLED_Fill(0xFF);//全屏点亮
        Delay_s(1);		// 2s
        OLED_Fill(0x00);//全屏灭
        Delay_s(1);		// 2s
        for(i=0;i<4;i++)
        {
            OLED_ShowCN(22+i*16,0,i);										//测试显示中文
        }
        Delay_s(2);		// 2s
        OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//测试6*8字符
        OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//测试8*16字符
        Delay_s(2);		// 2*100=200s
        OLED_CLS();//清屏
        OLED_OFF();//测试OLED休眠
        Delay_s(2);		// 2s

        OLED_ON();//测试OLED休眠后唤醒
        OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP2);//测试BMP位图显示
        Delay_s(2);		// 2*100=200s
        */
    }
}
