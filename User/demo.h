/*
*用于生产迪文指令屏的指令
*/
#ifndef DEMO_H_
#define DEMO_H_
#pragma once

#include "stdint.h"

//命令结尾
#define END "CC33C33C"

//颜色宏替换
#define COLOR_RED "F800"
#define COLOR_GREEN "07E0"
#define COLOR_BLUE "001F"
#define COLOR_WHITE "FFFF"
#define COLOR_BLACK "0000"
#define COLOR_YELLOW "FFE0"

void WoShou(void);//用于握手
void QingPing(void);//用背景色清屏
void setColor(char *ch1, char *ch2);
void buzzer_long(void);//蜂鸣器长鸣一声
void showTime(void);//在屏幕右下角显示RTC时间
void showStatus(int i);//在屏幕左下角显示状态
void showPicture(char *ch);//图片显示
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
