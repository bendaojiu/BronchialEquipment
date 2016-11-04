/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "demo.h"
#include <string.h>


char pos_time[5] = "004C";//时间原点，及t=0的点
char pos_temp[5] = "01F8";//温度零点，在实际中，以传感器得到的第一次为准

extern LCDRecvDataDef  LCDRecvData;

extern uint8_t LCDRecvDataMetux;//如果为1，证明主程序正在处理LCD返回的数据，此时不对LCD返回数据进行处理 


extern SetValue mySetValue;//引入设置范围数字初始化


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	//char str[4] = {0};
	uint8_t LCDRecvDataNum = 0;//用于存储处理的第几条指令
	LED_GPIO_Config();
	SysTick_Init();	//配置计时器

		/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USART1_Config();
	USART2_Config();
	NVIC2_Configuration();
	NVIC_Configuration();
	setColor(COLOR_RED, COLOR_GREEN);
	showPicture("00");
	//buzzer_long();
	Delay_ms(1000);
	showPicture("0001");
	showStatus(0);
	showTime();
	showSetTime(mySetValue.time);
	showSetTemp(mySetValue.temp);
	showSetPow(mySetValue.pow);
	setColor(COLOR_BLUE, COLOR_GREEN);
	showCurrentTemp(1);
	showCurrentPow(8);
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
		if (LCDRecvData.num > 0 && LCDRecvDataMetux != 1)
		{
			LCDRecvDataMetux = 1;
			for (LCDRecvDataNum=0; LCDRecvDataNum < LCDRecvData.num; LCDRecvDataNum++)
			{
				OperationLCDRecvData(LCDRecvData.recvData[LCDRecvDataNum]);
				memcpy(LCDRecvData.recvData[LCDRecvDataNum], 0, 20);//处理完成后重新初始化为0
			}
			LCDRecvData.num = 0;
			LCDRecvDataMetux = 0;
		}

		
		LED1(ON);
		Delay_us(10000);
		LED1(OFF);
		LED2(ON);
		Delay_ms(100);
		LED2(OFF);
	}
	
	
	
}
/*********************************************END OF FILE**********************/
