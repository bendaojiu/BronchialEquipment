/*
*用于生产迪文指令屏的指令
*/
#ifndef DEMO_H_
#define DEMO_H_
#pragma once

#include "stdint.h"


//命令结尾
#define END "CC33C33C"

//默认坐标
//用于显示系统时间的坐标
#define SysTime_X "0226"
#define SysTime_Y "023A"

//颜色宏替换
#define COLOR_RED "F800"
#define COLOR_GREEN "07E0"
#define COLOR_BLUE "001F"
#define COLOR_WHITE "FFFF"
#define COLOR_BLACK "0000"
#define COLOR_YELLOW "FFE0"

//屏幕功能宏替换
#define WoShow() send("AA00CC33C33C")//用于握手
#define QingPing() send("AA52CC33C33C")//用于清屏
//用于设置前景色，背景色
#define setColor(ch1, ch2) do{								\
															send("AA40");	 	\
															send(ch1);	 	 	\
															send(ch2);			\
															send(END);			\
															}while(0);
#define buzzer_long()	send("AA792FCC33C33C");//蜂鸣器长鸣一声
//用于在右下角显示系统RTC时间
//指令为 AA 9B FF <RTC_Mode> <Text_Mode> <Color> <X> <Y> CC 33 C3 3C
//此处显示模式默认为01，字体默认12*24，默认颜色为红色，X、Y坐标默认"0226"、"023A"，坐标为（550， 570）十进制
#define showTime() do{												\
											send("AA9BFF0103F800");	\
											send(SysTime_X);				\
											send(SysTime_Y);				\
											send(END);							\
											}while(0);
//在屏幕左下角显示状态
//00位显示“设备正常，请连接导管”
//01为显示“设备正常，等待治疗开始。。。”
//02为显示“治疗中。。。”
//坐标为（10，570）
//注意：使用前，需要清除当前区域显示，否则会叠加于其上
#define showStatus(ii)	do{										\
											send("AA9C02000A023A02200258000A023ACC33C33C");\
												if (ii == 0)					\
													send("AA6F000A023AC9E8B1B8D5FDB3A3A3ACC7EBC1ACBDD3B5BCB9DCCC33C33C");\
												else if (ii == 1)			\
													send("AA6F000A023AC9E8B1B8D5FDB3A3A3ACB5C8B4FDD6CEC1C6BFAACABCA1A3A1A3A1A3CC33C33C");\
												else if (ii == 2)			\
													send("AA6F000A023AD6CEC1C6D6D0A1A3A1A3A1A3CC33C33C"); \
										}while(0);
//显示图片，
//ch为字符串形式的图片索引ID
#define showPicture(ch)	do{										\
														send("AA70");			\
														send(ch);					\
														send(END);				\
													}while(0);

//void drawLine(char *x1, char *y1, char *x2, char *y2);//指定点连线，画线
void drawLine(int x, int y);//画直线，前一个点通过

//void drawSquare(int x1, int y1, int x2, int y2);//用前景色画矩形

//用于显示各个数值
void showCurrentTemp(int i);//用于显示实时温度
void showCurrentPow(int i);//用于显示实时功率
void showSetTime(int i);//用于显示设置的治疗时间
void showSetTemp(int i);//用于显示设置的治疗温度
void showSetPow(int i);//用于显示设置的治疗功率

void send(char *ch);//用于发送指令
uint8_t valueToHex(char ch);
void int2ASCII(int i, char *ch1);//将i转换为ASCII格式
void valueToStr(int value, int value1, char *x1, char *y1);//获得这个字符的十六进制中的半位

#endif
