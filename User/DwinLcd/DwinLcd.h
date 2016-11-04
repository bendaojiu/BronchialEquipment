#ifndef _DWIN_LCD_H
#define _DWIN_LCD_H


#include "stm32f10x.h"

/*全局结构体，用于迪文屏幕的参数及数据传输*/
typedef struct
{
    uint16_t    LCD_BACKGROUND;								//背景色
    uint16_t    LCD_FOREGROUND;								//前景色
    uint8_t 		LCD_Fonts;								//字体定义
    int16_t     LCD_AnswerCode;							//LCD指令应答代码(初始时必须为-1,-1代表无应答数据)
    uint8_t 		LCD_BackgroundPage;						//这是一个关键变量.
    int16_t			LCD_X_SIZE;							//LCD水平像素大小(不要把这个变量修改成宏定义,这样做不便于实现模块化库函数.)
    int16_t     LCD_Y_SIZE;							//LCD垂直像素大小(不要把这个变量修改成宏定义,这样做不便于实现模块化库函数.)
    void        (*LCD_PutFun)  (uint8_t Dat);				//LCD串口发送函数指针
    char        (*LCD_GetFun)  (void   );				//LCD串口buffer数据获取函数指针
}GLCD_DEF;

/*字体大小枚举变量*/
typedef enum
{
    ASCII_8x8            =	0x53,
    ASCII_8x16           =	0x54,
    ASCII_16x32          = 	0x55,
    ASCII_6x12           = 	0x6E,
    ASCII_12x24          = 	0x6F
}FONTS_TYP;



typedef enum
{  LCD_COLOR_WHITE   = 0xFFFF ,  
   LCD_COLOR_BLACK   = 0x0000 ,  
   LCD_COLOR_GREY    = 0xF7DE ,  
   LCD_COLOR_BLUE    = 0x001F ,  
   LCD_COLOR_BLUE2   = 0x051F ,  
   LCD_COLOR_RED     = 0xF800 ,  
   LCD_COLOR_MAGENTA = 0xF81F ,  
   LCD_COLOR_GREEN   = 0x07E0 ,  
   LCD_COLOR_CYAN    = 0x7FFF ,  
   LCD_COLOR_YELLOW  = 0xFFE0    
}LCD_COLOR;

static void LCD_DataEnd(void);
void LCD_ShookHands(void);
void LCD_BackGroundAndForeGroundSet(uint16_t ForeColor,uint16_t BackColor);
void LCD_DrawRectangle(uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t Color);
void LCD_DrawLine(uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye);
void LCD_PictureToCache(uint16_t Pic_ID);
void LCD_Init(void (*LCD_PutFun)(uint8_t Dat),char(*LCD_GetFun)(void));
void LCD_LetterSpacingSet(uint16_t x,uint16_t y);
void LCD_SetSpecifiedLocationColor(uint16_t x,uint16_t y,uint8_t mode);
void LCD_CursorDisplay(uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t mode);
void LCD_TextDisplay(uint16_t x,uint16_t y,const char *Str);
void LCD_PointDisplay(uint8_t *x,uint8_t *y,uint8_t mode);
void LCD_DrawOnePoint(uint16_t Xs,uint16_t Ys);




#endif  //end of file 
