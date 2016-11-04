/**
  ******************************************************************************
  * @file    DwinLcd.c/DwinLcd.h
  * @author  李本
  * @version V1.0
  * @date    2016-10-18
  * @brief   迪文串口指令屏驱动代码
  ******************************************************************************
  * @attention
  *
  * 
  * 
  * 
  *
  ******************************************************************************
  */ 
 
#include "DwinLcd.h"
#include <stdlib.h>
#include <string.h>


GLCD_DEF  LCD_Typ
={
    LCD_COLOR_BLACK	,						//默认背景色
    LCD_COLOR_WHITE	,						//默认前景色
    ASCII_16x32,							//默认字库
    -1,									//初始化为无应答状态
    30,									//默认后台页
    800,								//LCD 水平像素大小
    600,								//LCD 垂直像素大小
    NULL,								//LCD串口发送函数指针=NULL
    NULL								//LCD串口接收函数指针=NULL
};

/**
*函数名称：LCD_DataEnd
*函数功能：每帧数据的结尾
*输入参数：无
*输出参数：无
*/
static void LCD_DataEnd(void)
{
    LCD_Typ.LCD_PutFun(0xCC);
    LCD_Typ.LCD_PutFun(0x33);
    LCD_Typ.LCD_PutFun(0xC3);
    LCD_Typ.LCD_PutFun(0x3C);
}

/**
*函数名称：LCD_ShookHands
*函数功能：握手
*输入参数：无
*输出参数：无
*/
void LCD_ShookHands(void)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x00);
    LCD_DataEnd();
}

/**
*函数名称：LCD_ShookHands
*函数功能：设置前景色和背景色
*输入参数：uint16_t ForeColor,uint16_t BackColor
*输出参数：无
*/
void LCD_BackGroundAndForeGroundSet(uint16_t ForeColor,uint16_t BackColor)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x40);
    LCD_Typ.LCD_PutFun((uint8_t)(ForeColor>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(ForeColor));
    LCD_Typ.LCD_PutFun((uint8_t)(BackColor>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(BackColor));
    LCD_DataEnd();
}


/**
*函数名称：LCD_Init
*函数功能：画矩形
*输入参数：uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t Color
*输出参数：无
*/
void LCD_DrawRectangle(uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t Color)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x40);
    LCD_Typ.LCD_PutFun((uint8_t)(Color>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Color));
    LCD_Typ.LCD_PutFun(0x00);
    LCD_Typ.LCD_PutFun(0x00);
    LCD_DataEnd();
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x5B);				//前景色画线指令
    LCD_Typ.LCD_PutFun((uint8_t)(Xs>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Xs));
    LCD_Typ.LCD_PutFun((uint8_t)(Ys>>8)); 
    LCD_Typ.LCD_PutFun((uint8_t)(Ys));
    LCD_Typ.LCD_PutFun((uint8_t)(Xe>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Xe));
    LCD_Typ.LCD_PutFun((uint8_t)(Ye>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Ye));
    LCD_DataEnd();
} 

//画直线
void LCD_DrawLine(uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x55);
    LCD_Typ.LCD_PutFun((uint8_t)(Xs>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Xs));
    LCD_Typ.LCD_PutFun((uint8_t)(Ys>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Ys));
    LCD_Typ.LCD_PutFun((uint8_t)(Xe>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Xe));
    LCD_Typ.LCD_PutFun((uint8_t)(Ye>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Ye));
    LCD_DataEnd();
} 

//切换图片
void LCD_PictureToCache(uint16_t Pic_ID)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x70);
    LCD_Typ.LCD_PutFun((uint8_t)(Pic_ID>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Pic_ID));
    LCD_DataEnd();
}


/**
*函数名称：LCD_Init
*函数功能：通过形参输入串口发送函数跟串口接收函数的函数名来初始化
*输入参数：void (*LCD_PutFun)(uint8_t Dat),char(*LCD_GetFun)(void)
*输出参数：无
*函数功能：传入UART发送和接收函数的函数名，供调用者选择。
*/
void LCD_Init(void (*LCD_PutFun)(uint8_t Dat),char(*LCD_GetFun)(void))
{
    LCD_Typ.LCD_PutFun=LCD_PutFun;

    LCD_Typ.LCD_GetFun=LCD_GetFun;				//初始化LCD串口接收函数指针

    LCD_BackGroundAndForeGroundSet( LCD_Typ.LCD_BACKGROUND,LCD_Typ.LCD_FOREGROUND);//设置前景背景
//    LCD_Typ.LCD_Fonts;
//    LCD_Typ.LCD_AnswerCode;
//    LCD_Typ.LCD_BackgroundPage;
//    LCD_Typ.LCD_X_SIZE;
//    LCD_Typ.LCD_Y_SIZE;
}


/**
*函数名称：LCD_Init
*函数功能：设置字体间距
*输入参数：uint16_t x,uint16_t y
*输出参数：无
*功能说明：设置字体间距，x表示字体行间距，y表示列间距，范围0x00-0x7f之间，系统默认值为零。
*/
void LCD_LetterSpacingSet(uint16_t x,uint16_t y)
{
		LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x41);
    LCD_Typ.LCD_PutFun((uint8_t)(x<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(x));
	  LCD_Typ.LCD_PutFun((uint8_t)(y<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(y));
	  LCD_DataEnd();
}


/**
*函数名称：LCD_SetSpecifiedLocationColor
*函数功能：取某点颜色到前景色或者背景色调色板
*输入参数：uint16_t x,uint16_t y,uint8_t mode
*输出参数：无
*功能说明：取某点颜色到前景色或者背景色调色板。mode为0时取色到前景色，为1时为背景色
*/
void LCD_SetSpecifiedLocationColor(uint16_t x,uint16_t y,uint8_t mode)
{


		LCD_Typ.LCD_PutFun(0xAA);
		if(mode==0)
		{
			LCD_Typ.LCD_PutFun(0x43);
		}
		else
		{
			LCD_Typ.LCD_PutFun(0x42);
		}
    LCD_Typ.LCD_PutFun((uint8_t)(x<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(x));
	  LCD_Typ.LCD_PutFun((uint8_t)(y<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(y));
		LCD_DataEnd();
}


/**
*函数名称：LCD_CursorDisplay
*函数功能：设置光标显示及光标的大小
*输入参数：uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t mode
*输出参数：无
*功能说明：设置光标显示及光标的大小，x表示光标的宽度，y表示光标的坐标，输入宽度和长度值得范围为0x01-0x1f,
*          mode为0的时开光标显示，为1时关光标显示，这时输入的其他参数无效。
*/
void LCD_CursorDisplay(uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t mode)
{
		LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x44);
		if(mode==0)
		{
			LCD_Typ.LCD_PutFun(0x01);
		}
		else
		{
			LCD_Typ.LCD_PutFun(0x00);
		}	
    LCD_Typ.LCD_PutFun((uint8_t)(x<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(x));
	  LCD_Typ.LCD_PutFun((uint8_t)(y<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(y));
    LCD_Typ.LCD_PutFun(width);
    LCD_Typ.LCD_PutFun(height);
	  LCD_DataEnd();
}



/**
*函数名称：LCD_TextDisplay
*函数功能：标准字库文本显示
*输入参数：uint8_t x,uint16_t y,const uint16_t *Str
*输出参数：无
*功能说明：x,y为文本起始位置坐标，传入字符串使用，函数体内部有前背景色的设置和字体的设置
*					 需要时要在使用该函数之前给GLCD_DEF结构体相关成员变量赋值，不修改为默认参数。
*/
void LCD_TextDisplay(uint16_t x,uint16_t y,const char *Str)
{

		unsigned int k=0;
		LCD_BackGroundAndForeGroundSet(LCD_Typ.LCD_FOREGROUND,LCD_Typ.LCD_BACKGROUND);//设置前背景
		LCD_Typ.LCD_PutFun(0xAA);
		LCD_Typ.LCD_PutFun(LCD_Typ.LCD_Fonts);//设置字体
    LCD_Typ.LCD_PutFun((uint8_t)(x<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(x));
	  LCD_Typ.LCD_PutFun((uint8_t)(y<<8));
    LCD_Typ.LCD_PutFun((uint8_t)(y));
		for(k=0;*(Str + k)!='\0';k++)
		{
			LCD_Typ.LCD_PutFun(*(Str+k));
		}
		LCD_DataEnd();
}
/**
*函数名称：LCD_PointDisplay
*函数功能：显示点（最多62个）
*输入参数：uint8_t *x,uint8_t *y,uint8_t mode
*输出参数：无
*功能说明：x,y数组表示传入点的坐标，mode为0表示删除背景色，为1表示在前景色画点。
*/
void LCD_PointDisplay(uint8_t *x,uint8_t *y,uint8_t mode)
{		
		uint8_t i;
		LCD_Typ.LCD_PutFun(0xAA);
		if(mode==0)
		{
			LCD_Typ.LCD_PutFun(0x50);
		}
		else
		{
			LCD_Typ.LCD_PutFun(0x51);
		}	
		for(i=0;((i<(sizeof(x)/sizeof(uint8_t)))||(i<(sizeof(y)/sizeof(uint8_t)))||i<62);i++)
		{
 				LCD_Typ.LCD_PutFun((uint8_t)(x[i]));
				LCD_Typ.LCD_PutFun((uint8_t)(y[i]<<8));
				LCD_Typ.LCD_PutFun((uint8_t)(y[i]));
		}
		LCD_DataEnd();

}



/**
*函数名称：LCD_PointDisplay
*函数功能：显示一个点
*输入参数：uint16_t Xs,uint16_t Ys
*输出参数：无
*功能说明：x,y数组表示传入点的坐标，mode为0表示删除背景色，为1表示在前景色画点。
*/
void LCD_DrawOnePoint(uint16_t Xs,uint16_t Ys)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x51);
    LCD_Typ.LCD_PutFun((uint8_t)(Xs>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Xs));
    LCD_Typ.LCD_PutFun((uint8_t)(Ys>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Ys));
    LCD_DataEnd();
} 

/**
*函数名称：LCD_SetTextBox
*函数功能：设置文本框
*输入参数：uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye
*输出参数：无
*功能说明：输入参数决定文本框大小，mode为0时设置文本框，为1不设置，如果设置了文本框，则显示字符只能在文本框内换行
*/
void LCD_SetTextBox(uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint8_t mode)
{
    LCD_Typ.LCD_PutFun(0xAA);
		LCD_Typ.LCD_PutFun(0x45);
		if(mode==0)
		{
			LCD_Typ.LCD_PutFun((uint8_t)(Xs>>8));
			LCD_Typ.LCD_PutFun((uint8_t)(Xs));
			LCD_Typ.LCD_PutFun((uint8_t)(Ys>>8));
			LCD_Typ.LCD_PutFun((uint8_t)(Ys));
			LCD_Typ.LCD_PutFun((uint8_t)(Xe>>8));
			LCD_Typ.LCD_PutFun((uint8_t)(Xe));
			LCD_Typ.LCD_PutFun((uint8_t)(Ye>>8));
			LCD_Typ.LCD_PutFun((uint8_t)(Ye));
		}
		else
		{
			LCD_Typ.LCD_PutFun(0x00);//取消文本框设置
		}
    LCD_DataEnd();
} 



/* 
staic void LCD_SetBaudRate(uint32_t BaudRate)
{

 



}
 */


//end of file


