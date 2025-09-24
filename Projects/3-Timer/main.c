#include <REGX51.H>
#include "Timer.h"
#include "DigitalTube.h"


static unsigned int count = 0;

void timer0_callback(char timer_id)
{
	timer_id;
	count++;
	
	P1_0 = ~P1_0;
	
	//beep
	//P2_3 = ~P2_3;
}

void main(void)
{
	P1_1 = 0;

	//Timer0_Init(500, timer0_callback);
	//Timer0_Init(100, 10*1000, timer0_callback); //1000ms = 100 * (10*1000)us / 1000; 
	Timer0_Init(16, 62500, timer0_callback); //1000ms = 16 * 62500 us;
	Timer0_Start();
	
	P1_2 = 0;
		
	while(1)
	{
		//Digital tube
		DigitalTube_Display(count);
		DigitalTube_clear();
	}
}

