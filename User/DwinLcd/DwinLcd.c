/**
  ******************************************************************************
  * @file    DwinLcd.c/DwinLcd.h
  * @author  �
  * @version V1.0
  * @date    2016-10-18
  * @brief   ���Ĵ���ָ������������
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
    LCD_COLOR_BLACK	,						//Ĭ�ϱ���ɫ
    LCD_COLOR_WHITE	,						//Ĭ��ǰ��ɫ
    ASCII_16x32,							//Ĭ���ֿ�
    -1,									//��ʼ��Ϊ��Ӧ��״̬
    30,									//Ĭ�Ϻ�̨ҳ
    800,								//LCD ˮƽ���ش�С
    600,								//LCD ��ֱ���ش�С
    NULL,								//LCD���ڷ��ͺ���ָ��=NULL
    NULL								//LCD���ڽ��պ���ָ��=NULL
};

/**
*�������ƣ�LCD_DataEnd
*�������ܣ�ÿ֡���ݵĽ�β
*�����������
*�����������
*/
static void LCD_DataEnd(void)
{
    LCD_Typ.LCD_PutFun(0xCC);
    LCD_Typ.LCD_PutFun(0x33);
    LCD_Typ.LCD_PutFun(0xC3);
    LCD_Typ.LCD_PutFun(0x3C);
}

/**
*�������ƣ�LCD_ShookHands
*�������ܣ�����
*�����������
*�����������
*/
void LCD_ShookHands(void)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x00);
    LCD_DataEnd();
}

/**
*�������ƣ�LCD_ShookHands
*�������ܣ�����ǰ��ɫ�ͱ���ɫ
*���������uint16_t ForeColor,uint16_t BackColor
*�����������
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
*�������ƣ�LCD_Init
*�������ܣ�������
*���������uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye,uint16_t Color
*�����������
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
    LCD_Typ.LCD_PutFun(0x5B);				//ǰ��ɫ����ָ��
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

//��ֱ��
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

//�л�ͼƬ
void LCD_PictureToCache(uint16_t Pic_ID)
{
    LCD_Typ.LCD_PutFun(0xAA);
    LCD_Typ.LCD_PutFun(0x70);
    LCD_Typ.LCD_PutFun((uint8_t)(Pic_ID>>8));
    LCD_Typ.LCD_PutFun((uint8_t)(Pic_ID));
    LCD_DataEnd();
}


/**
*�������ƣ�LCD_Init
*�������ܣ�ͨ���β����봮�ڷ��ͺ��������ڽ��պ����ĺ���������ʼ��
*���������void (*LCD_PutFun)(uint8_t Dat),char(*LCD_GetFun)(void)
*�����������
*�������ܣ�����UART���ͺͽ��պ����ĺ���������������ѡ��
*/
void LCD_Init(void (*LCD_PutFun)(uint8_t Dat),char(*LCD_GetFun)(void))
{
    LCD_Typ.LCD_PutFun=LCD_PutFun;

    LCD_Typ.LCD_GetFun=LCD_GetFun;				//��ʼ��LCD���ڽ��պ���ָ��

    LCD_BackGroundAndForeGroundSet( LCD_Typ.LCD_BACKGROUND,LCD_Typ.LCD_FOREGROUND);//����ǰ������
//    LCD_Typ.LCD_Fonts;
//    LCD_Typ.LCD_AnswerCode;
//    LCD_Typ.LCD_BackgroundPage;
//    LCD_Typ.LCD_X_SIZE;
//    LCD_Typ.LCD_Y_SIZE;
}


/**
*�������ƣ�LCD_Init
*�������ܣ�����������
*���������uint16_t x,uint16_t y
*�����������
*����˵�������������࣬x��ʾ�����м�࣬y��ʾ�м�࣬��Χ0x00-0x7f֮�䣬ϵͳĬ��ֵΪ�㡣
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
*�������ƣ�LCD_SetSpecifiedLocationColor
*�������ܣ�ȡĳ����ɫ��ǰ��ɫ���߱���ɫ��ɫ��
*���������uint16_t x,uint16_t y,uint8_t mode
*�����������
*����˵����ȡĳ����ɫ��ǰ��ɫ���߱���ɫ��ɫ�塣modeΪ0ʱȡɫ��ǰ��ɫ��Ϊ1ʱΪ����ɫ
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
*�������ƣ�LCD_CursorDisplay
*�������ܣ����ù����ʾ�����Ĵ�С
*���������uint16_t x,uint16_t y,uint8_t width,uint8_t height,uint8_t mode
*�����������
*����˵�������ù����ʾ�����Ĵ�С��x��ʾ���Ŀ�ȣ�y��ʾ�������꣬�����Ⱥͳ���ֵ�÷�ΧΪ0x01-0x1f,
*          modeΪ0��ʱ�������ʾ��Ϊ1ʱ�ع����ʾ����ʱ���������������Ч��
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
*�������ƣ�LCD_TextDisplay
*�������ܣ���׼�ֿ��ı���ʾ
*���������uint8_t x,uint16_t y,const uint16_t *Str
*�����������
*����˵����x,yΪ�ı���ʼλ�����꣬�����ַ���ʹ�ã��������ڲ���ǰ����ɫ�����ú����������
*					 ��ҪʱҪ��ʹ�øú���֮ǰ��GLCD_DEF�ṹ����س�Ա������ֵ�����޸�ΪĬ�ϲ�����
*/
void LCD_TextDisplay(uint16_t x,uint16_t y,const char *Str)
{

		unsigned int k=0;
		LCD_BackGroundAndForeGroundSet(LCD_Typ.LCD_FOREGROUND,LCD_Typ.LCD_BACKGROUND);//����ǰ����
		LCD_Typ.LCD_PutFun(0xAA);
		LCD_Typ.LCD_PutFun(LCD_Typ.LCD_Fonts);//��������
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
*�������ƣ�LCD_PointDisplay
*�������ܣ���ʾ�㣨���62����
*���������uint8_t *x,uint8_t *y,uint8_t mode
*�����������
*����˵����x,y�����ʾ���������꣬modeΪ0��ʾɾ������ɫ��Ϊ1��ʾ��ǰ��ɫ���㡣
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
*�������ƣ�LCD_PointDisplay
*�������ܣ���ʾһ����
*���������uint16_t Xs,uint16_t Ys
*�����������
*����˵����x,y�����ʾ���������꣬modeΪ0��ʾɾ������ɫ��Ϊ1��ʾ��ǰ��ɫ���㡣
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
*�������ƣ�LCD_SetTextBox
*�������ܣ������ı���
*���������uint16_t Xs,uint16_t Ys,uint16_t Xe,uint16_t Ye
*�����������
*����˵����������������ı����С��modeΪ0ʱ�����ı���Ϊ1�����ã�����������ı�������ʾ�ַ�ֻ�����ı����ڻ���
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
			LCD_Typ.LCD_PutFun(0x00);//ȡ���ı�������
		}
    LCD_DataEnd();
} 



/* 
staic void LCD_SetBaudRate(uint32_t BaudRate)
{

 



}
 */


//end of file


