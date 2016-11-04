#include "demo.h"
#include "bsp_usart1.h"
#include <string.h>
#include <stdlib.h>
/*
*用于生产迪文指令屏的指令
*/

extern char pos_time[5];
extern char pos_temp[5];

#define ShiLiuJinZhi  "0123456789ABCDEF"//用于转换十六进制

//画折线的时候

/*
*画曲线坐标说明(所有坐标十进制)
*原点坐标(76, 504)
*横坐标每 28，代表时间1秒
*纵坐标每 28，代表温度10度
*/

uint16_t pos[2] = {76, 504};//代表坐标远点的像素位置（十进制）



void valueToStr(int value, int value1, char *x1, char *y1);


//画出连接（x1，y1）（x2，y2）两个点的连线
//void drawLine(char *x1, char *y1, char *x2, char *y2)
//{
//	char ch[20];
//	sprintf(ch, "AA56%s%s%s%s%s", x1, y1, x2, y2, END);
//	send(ch);
//}
//画折线
void drawLine(int x, int y)
{
	char ch[28];
	char x_tmp[5] = {0}, y_tmp[5] = {0};//用于存储转换后的时间和温度的值
		char x1[5] = {0}, y1[5] = {0};//用于存储字符状态的x和y
	 valueToStr(x, y, x1, y1);//将x值由int转为char,将y值由int转为char
	//接下来构造所需的4位的char
	switch(strlen(x1))
	{
		case 1:
			sprintf(x_tmp, "000%s", x1);
			break;
		case 2:
			sprintf(x_tmp, "00%s", x1);
			break;
		case 3:
			sprintf(x_tmp, "0%s", x1);
			break;
		default:
			break;
	}
		switch(strlen(y1))
	{
		case 1:
			sprintf(y_tmp, "000%s", y1);
			break;
		case 2:
			sprintf(y_tmp, "00%s", y1);
			break;
		case 3:
			sprintf(y_tmp, "0%s", y1);
			break;
		default:
			break;
	}
	sprintf(ch, "AA56%s%s%s%s%s", pos_time, pos_temp, x_tmp, y_tmp, END);
	strcpy(pos_time, x_tmp);
	strcpy(pos_temp, y_tmp);
	send(ch);
}


/*
//用前景色画矩形
void drawSquare(int x1, int y1, int x2, int y2)
{
	char *xLeft = shijingzhiToshiliujinzhi(x1);
	char *yLeft = shijingzhiToshiliujinzhi(y1);
	char *xRight = shijingzhiToshiliujinzhi(x2);
	char *yRight = shijingzhiToshiliujinzhi(y2);
	
	//char ch[30] = {0x00, 0xAA, 0x59};
	
}
*/

//显示实时温度，坐标为（245，60）
//缺少当超出某个范围的时候，字体颜色的变化
void showCurrentTemp(int i)
{
	char ch[40] = {0};
	//现将该区域显示清除
	send("AA9C0200D5003C0135007C00D5003CCC33C33C");
	if (i < 10)//当要显示的数字小于10的时候，需要将坐标延后
	{
		sprintf(ch, "AA980115003C00C107FFFF001F3%d%s", i, END);
	}
	else if(i < 100)//当要显示数字为2位的时候
	{
		sprintf(ch, "AA9800F5003C00C107FFFF001F3%d3%d%s", i/10, i%10, END);		
	}
	else
	{
		sprintf(ch, "AA9800D5003C00C107FFFF001F3%d3%d3%d%s", i/100, (i%100)/10, (i%100)%10, END);
	}
	send(ch);
}

//显示实时功率，坐标为（445，60）
//缺少当超出某个范围的时候，字体颜色的变化
void showCurrentPow(int i)
{
	char ch[40] = {0};
	//现将该区域显示清除
	send("AA9C02019D003C01FD007C019D003CCC33C33C");
	if (i < 10)//当要显示的数字小于10的时候，需要将坐标延后
	{
		sprintf(ch, "AA9801DD003C00C107FFFF001F3%d%s", i, END);
	}
	else if(i < 100)//当要显示数字为2位的时候
	{
		sprintf(ch, "AA9801BD003C00C107FFFF001F3%d3%d%s", i/10, i%10, END);			
	}
	else
	{
		sprintf(ch, "AA98019D003C00C107FFFF001F3%d3%d3%d%s", i/100, (i%100)/10, (i%100)%10, END);
	}
	send(ch);
}

//显示设置的治疗时间，坐标为（635， 60）
void showSetTime(int i)
{
	char ch[40] = {0};
	//现将该区域显示清除
	send("AA9C02025B003C029B007C025B003CCC33C33C");
	if (i < 10)//当要显示的数字小于10的时候，需要将坐标延后
	{
		sprintf(ch, "AA98029B003C24C107FFFF001F3%d%s", i, END);
	}
	else if(i < 100)//当要显示数字为2位的时候
	{
		sprintf(ch, "AA98027B003C24C107FFFF001F3%d3%d%s", i/10, i%10, END);			
	}
	else
	{
		sprintf(ch, "AA98025B003C24C107FFFF001F3%d3%d3%d%s", i/100, (i%100)/10, (i%100)%10, END);
	}
	send(ch);
}

//显示设置的治疗温度，坐标为（635， 200）
void showSetTemp(int i)
{
	char ch[40] = {0};
	//现将该区域显示清除
	send("AA9C02025B00C8029B0108025B00C8CC33C33C");
	if (i < 10)//当要显示的数字小于10的时候，需要将坐标延后
	{
		sprintf(ch, "AA98029B00C824C107FFFF001F3%d%s", i, END);
	}
	else if(i < 100)//当要显示数字为2位的时候
	{
		sprintf(ch, "AA98027B00C824C107FFFF001F3%d3%d%s", i/10, i%10, END);			
	}
	else
	{
		sprintf(ch, "AA98025B00C824C107FFFF001F3%d3%d3%d%s", i/100, (i%100)/10, (i%100)%10, END);
	}
	send(ch);
}

//显示设置的治疗功率，坐标为（635， 340）
void showSetPow(int i)
{
	char ch[40] = {0};
	//现将该区域显示清除
	send("AA9C02025B0154029B0194025B0154CC33C33C");
	if (i < 10)//当要显示的数字小于10的时候，需要将坐标延后
	{
		sprintf(ch, "AA98029B015424C107FFFF001F3%d%s", i, END);
	}
	else if(i < 100)//当要显示数字为2位的时候
	{
		sprintf(ch, "AA98027B015424C107FFFF001F3%d3%d%s", i/10, i%10, END);			
	}
	else
	{
		sprintf(ch, "AA98025B015424C107FFFF001F3%d3%d3%d%s", i/100, (i%100)/10, (i%100)%10, END);
	}
	send(ch);
}

//将字符串转换为十六进制在发送
void send(char *ch)
{
	int i = 0, len = 0;
	uint8_t res[2];
	len = strlen(ch);
	for (i=0; i<len; i=i+2)
	{
		res[0] = valueToHex(ch[i]);
		res[1]=valueToHex(ch[i+1]);
		USART_SendData(USART2, (res[0]*16+res[1]));
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, (res[0]*16+res[1]));
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
	//printf("%d\n", len);
}

uint8_t valueToHex(char ch)
{
	uint8_t result = 0;
  
  if(ch >= '0' && ch <= '9'){
    result = (int)(ch - '0');
  }
  else if(ch >= 'a' && ch <= 'z'){
    result = (int)(ch - 'a') + 10;
  }
  else if(ch >= 'A' && ch <= 'Z'){
    result = (int)(ch - 'A') + 10;
  }
  else{
    result = 0;
  }
  return result;
}

//将数字转换为ASCII，以便于显示
void int2ASCII(int i, char *ch1)
{
}

void valueToStr(int value, int value1, char *x1, char *y1)
{
	
	int tmp_i=0, tmp_j = 0;
   char x2[5] = {0}, y2[5] = {0};
    while(value)
    {
        x2[tmp_i++]=ShiLiuJinZhi[value%16];
        value/=16;
    }
		tmp_i -= 1;
		while(tmp_i >= 0)
			x1[tmp_j++] = x2[tmp_i--];
		
		tmp_j = 0;
		tmp_i = 0;
		while(value1)
    {
        y2[tmp_i++]=ShiLiuJinZhi[value1%16];
        value1/=16;
    }
		tmp_i -= 1;
		while(tmp_i >= 0)
			y1[tmp_j++] = y2[tmp_i--];
    
}
