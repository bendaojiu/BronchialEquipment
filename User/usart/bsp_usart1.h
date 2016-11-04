#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>


void USART1_Config(void);
void USART2_Config(void);
void NVIC_Configuration(void);
void NVIC2_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void USART_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void USART_SendString( USART_TypeDef * pUSARTx, char *str);
void USART_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART1_H */
