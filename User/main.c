/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "demo.h"
#include "DwinLcd.h"

char pos_time[5] = "004C";//ʱ��ԭ�㣬��t=0�ĵ�
char pos_temp[5] = "01F8";//�¶���㣬��ʵ���У��Դ������õ��ĵ�һ��Ϊ׼

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	//char str[4] = {0};
	LED_GPIO_Config();
	SysTick_Init();	//���ü�ʱ��

		/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USART1_Config();
	USART2_Config();
	NVIC2_Configuration();
	NVIC_Configuration();
	LCD_Init(USART_SendByte,USART_ReceiveByte);

	LCD_PictureToCache(0);
	
	LCD_CursorDisplay(110,100,100,100,1);
	
	
//	setColor(COLOR_RED, COLOR_GREEN);
//	showPicture("00");
//	//buzzer_long();
//	Delay_ms(1000);
//	showPicture("0001");
//	showStatus(0);
//	showTime();
//	showSetTime(37);
//	showSetTemp(60);
//	showSetPow(20);
//	setColor(COLOR_BLUE, COLOR_GREEN);
//	showCurrentTemp(1);
//	showCurrentPow(8);
//	drawLine(80, 480);
//	Delay_ms(1000);
//	showCurrentTemp(23);
//	showCurrentPow(24);
//	drawLine(120, 300);
//	Delay_ms(1000);
//	showCurrentTemp(145);
//	showCurrentPow(364);
//	drawLine(180, 380);
//	Delay_ms(1000);
//	showCurrentTemp(89);
//	showCurrentPow(98);
//	drawLine(220, 300);
//	drawLine(320, 400);



	for(;;)
	{
		LED1(ON);
		Delay_us(10000);
		LED1(OFF);
		LED2(ON);
		Delay_ms(100);
		LED2(OFF);
	}
	
	
	
}
/*********************************************END OF FILE**********************/
