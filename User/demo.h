/*
*������������ָ������ָ��
*/
#ifndef DEMO_H_
#define DEMO_H_
#pragma once

#include "stdint.h"


//�����β
#define END "CC33C33C"

//Ĭ������
//������ʾϵͳʱ�������
#define SysTime_X "0226"
#define SysTime_Y "023A"

//��ɫ���滻
#define COLOR_RED "F800"
#define COLOR_GREEN "07E0"
#define COLOR_BLUE "001F"
#define COLOR_WHITE "FFFF"
#define COLOR_BLACK "0000"
#define COLOR_YELLOW "FFE0"

//��Ļ���ܺ��滻
#define WoShow() send("AA00CC33C33C")//��������
#define QingPing() send("AA52CC33C33C")//��������
//��������ǰ��ɫ������ɫ
#define setColor(ch1, ch2) do{								\
															send("AA40");	 	\
															send(ch1);	 	 	\
															send(ch2);			\
															send(END);			\
															}while(0);
#define buzzer_long()	send("AA792FCC33C33C");//����������һ��
//���������½���ʾϵͳRTCʱ��
//ָ��Ϊ AA 9B FF <RTC_Mode> <Text_Mode> <Color> <X> <Y> CC 33 C3 3C
//�˴���ʾģʽĬ��Ϊ01������Ĭ��12*24��Ĭ����ɫΪ��ɫ��X��Y����Ĭ��"0226"��"023A"������Ϊ��550�� 570��ʮ����
#define showTime() do{												\
											send("AA9BFF0103F800");	\
											send(SysTime_X);				\
											send(SysTime_Y);				\
											send(END);							\
											}while(0);
//����Ļ���½���ʾ״̬
//00λ��ʾ���豸�����������ӵ��ܡ�
//01Ϊ��ʾ���豸�������ȴ����ƿ�ʼ��������
//02Ϊ��ʾ�������С�������
//����Ϊ��10��570��
//ע�⣺ʹ��ǰ����Ҫ�����ǰ������ʾ����������������
#define showStatus(ii)	do{										\
											send("AA9C02000A023A02200258000A023ACC33C33C");\
												if (ii == 0)					\
													send("AA6F000A023AC9E8B1B8D5FDB3A3A3ACC7EBC1ACBDD3B5BCB9DCCC33C33C");\
												else if (ii == 1)			\
													send("AA6F000A023AC9E8B1B8D5FDB3A3A3ACB5C8B4FDD6CEC1C6BFAACABCA1A3A1A3A1A3CC33C33C");\
												else if (ii == 2)			\
													send("AA6F000A023AD6CEC1C6D6D0A1A3A1A3A1A3CC33C33C"); \
										}while(0);
//��ʾͼƬ��
//chΪ�ַ�����ʽ��ͼƬ����ID
#define showPicture(ch)	do{										\
														send("AA70");			\
														send(ch);					\
														send(END);				\
													}while(0);

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
