#include <REGX52.H>
#include "UART.h"

LPUART_RECEIVEBYTE g_pfReceiveByte;

enum EUART_BAUND_RATE
{
	EUART_RATE_4800 = 4800,
	EUART_RATE_9600 = 9600
};

static unsigned char UART_Calc8bTimerCount_ByBaundRate(bit smod, enum EUART_BAUND_RATE rate)
{
	//baund-rate = 2^SMOD / 32 * (11059200 / 12 / (256 - TH1));

	if (1 == smod)
	{
		//baund-rate = 1 / 16 * ( 921600 / (256 - TH1) )
		//       TH1 = 256 - (57600 / baund-rate)
		return 256 - (57600 / rate);
	}
	else
	{
		//baund-rate = 1 / 32 * ( 921600 / (256 - TH1) )
		//       TH1 = 256 - (28800 / baund-rate)
		return 256 - (28800 / rate);
	}
}

void UART_Init(LPUART_RECEIVEBYTE pf) //11.0592MHz
{
	unsigned char rate;
	rate = UART_Calc8bTimerCount_ByBaundRate(1, EUART_RATE_4800); //4800Hz
	
	PCON |= 0x80; //SMOD=1
	SCON = 0x50;  //8bits UART with variable baud rate
	
	//Configure Timer1
	TMOD &= 0x0F; //clear timer1 config
	TMOD |= 0x20; //set timer1 mode is that automatic reloading 8 bits value
	TL1 = rate; //0xF4;
	TH1 = rate; //TH1 automatic assign to TL1
	ET1 = 0; //disable timer1 interupt
	TR1 = 1; //start timer1
	
	EA = 1; //enable MCU interupt
	ES = 1; //enable serial interupt
	
	g_pfReceiveByte = pf;
}

void UART_SendByte(unsigned char byte)
{
	SBUF = byte;
	while(0 == TI);
	TI = 0;
}

void UART_Routine(void) interrupt 4
{
	if (1 == RI)
	{	
		//received data
		if (g_pfReceiveByte)
		{
			g_pfReceiveByte(SBUF);
		}
		
		RI = 0;
	}
	else if(1 == TI)
	{
		//sent data
	}
}
