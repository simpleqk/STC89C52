#ifndef _LCD1602_H_
#define _LCD1602_H_

void LCD1602_Init();
void LCD1602_Clear();
void LCD1602_DisplayStr(unsigned char row, unsigned col, const char *text);
void LCD1602_DisplayNum(unsigned char row, unsigned col, unsigned int value);

#endif
