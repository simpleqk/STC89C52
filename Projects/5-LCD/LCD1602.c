#include <REGX52.H>

sbit LCD_RS = P3^5;
sbit LCD_RW = P3^6;
sbit LCD_EN = P3^4;

#define LCD_DATA P0


static void LCD1602_CheckBusy()
{
	char status = 0;
	
	LCD_DATA = 0xFF;
	
	//read status
	LCD_RS = 0;
	LCD_RW = 1;

	do
	{
		LCD_EN = 1;
	
		status = LCD_DATA;
	
		LCD_EN = 0;
		
	}while(status & 0x80); //0 ready
}

static void LCD1602_WriteCmd(const char byte)
{
	LCD1602_CheckBusy();

	//write command
	LCD_RS = 0;
	LCD_RW = 0;
	
	LCD_DATA = byte;
	
	//wait >=30ns
	
	LCD_EN = 1;
	//wait >= 150ns;
	LCD_EN = 0;
}

static void LCD1602_WriteChar(const char byte)
{
	LCD1602_CheckBusy();
	
	//write data
	LCD_RS = 1;
	LCD_RW = 0;
	
	LCD_DATA = byte;
	
	//wait >=30ns
	
	LCD_EN = 1;
	//wait >= 150ns;
	LCD_EN = 0;
}

static void LCD1602_SetPos(unsigned char row, unsigned char col)
{
	unsigned char pos = 0;
	
	pos  = (0==row) ? 0x00 : 0x40;
	pos += (col<40) ? col  : 0;
	
	LCD1602_WriteCmd(0x80 | pos);
}


void LCD1602_Init()
{
	//setup display mode 16x2
	LCD1602_WriteCmd(0x38);
	
	//turn on display
	LCD1602_WriteCmd(0xc);
	
	//the address pointer auto increase
	LCD1602_WriteCmd(0x06);
	
	//clear display
	LCD1602_WriteCmd(0x01);
}

void LCD1602_Clear()
{
	LCD1602_WriteCmd(0x01);
}

void LCD1602_DisplayStr(unsigned char row, unsigned col, const char *text)
{
	const char *p = text;
	
	LCD1602_SetPos(row, col);
	
	while(*p != '\0')
	{
		LCD1602_WriteChar(*p++);
	}
}

void LCD1602_DisplayNum(unsigned char row, unsigned col, unsigned int value)
{
	char i = 0;
	char j = 0;
	char v = 0;
	char str[] = "65535";
		
	while(value > 0)
	{
		v = value % 10;
		
		v += '0'; //convert value to character
		str[i++] = v;
		
		value /= 10;
	}
	str[i] = '\0';
	
	for (j=0; j<i/2; j++)
	{
		v = str[j];
		str[j] = str[i-1-j];
		str[i-1-j] = v;
	}
	
	LCD1602_DisplayStr(row, col, str);
}
