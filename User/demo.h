/*
*������������ָ������ָ��
*/
#ifndef DEMO_H_
#define DEMO_H_
#pragma once

#include "stdint.h"

//�����β
#define END "CC33C33C"

//��ɫ���滻
#define COLOR_RED "F800"
#define COLOR_GREEN "07E0"
#define COLOR_BLUE "001F"
#define COLOR_WHITE "FFFF"
#define COLOR_BLACK "0000"
#define COLOR_YELLOW "FFE0"

void WoShou(void);//��������
void QingPing(void);//�ñ���ɫ����
void setColor(char *ch1, char *ch2);
void buzzer_long(void);//����������һ��
void showTime(void);//����Ļ���½���ʾRTCʱ��
void showStatus(int i);//����Ļ���½���ʾ״̬
void showPicture(char *ch);//ͼƬ��ʾ
//void drawLine(char *x1, char *y1, char *x2, char *y2);//ָ�������ߣ�����
void drawLine(int x, int y);//��ֱ�ߣ�ǰһ����ͨ��

//void drawSquare(int x1, int y1, int x2, int y2);//��ǰ��ɫ������

//������ʾ������ֵ
void showCurrentTemp(int i);//������ʾʵʱ�¶�
void showCurrentPow(int i);//������ʾʵʱ����
void showSetTime(int i);//������ʾ���õ�����ʱ��
void showSetTemp(int i);//������ʾ���õ������¶�
void showSetPow(int i);//������ʾ���õ����ƹ���

void send(char *ch);//���ڷ���ָ��
uint8_t valueToHex(char ch);
void int2ASCII(int i, char *ch1);//��iת��ΪASCII��ʽ
void valueToStr(int value, int value1, char *x1, char *y1);//�������ַ���ʮ�������еİ�λ

#endif
