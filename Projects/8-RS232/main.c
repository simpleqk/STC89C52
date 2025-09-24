#include <REGX52.H>
#include "UART.h"
#include "DelayMs.h"
#include "LCD1602.h"

unsigned char g_received_dat[2] = {'\0'};
unsigned int  g_received_val;
	
UART_ReceivedByte(unsigned char byte)
{
	//P1_7 = ~P1_7;
	//P1 = byte;
	
	g_received_val = byte;
	g_received_dat[0] = (char)byte;
	
	UART_SendByte(byte);
}

void main()
{
	unsigned char value = 0;
	
	//P1 = 0;
	
	LCD1602_Init();
	UART_Init(UART_ReceivedByte);
	
	LCD1602_DisplayStr(1, 1, "test");
	LCD1602_Clear();
	
	while(1)
	{
		UART_SendByte(value);
		value++;
		
		delay_500ms();
		
		//display received byte
		LCD1602_DisplayStr(1,1, g_received_dat);		
		//LCD1602_DisplayNum(1, 1, g_received_val);
	}
}
