#include <REGX52.H>
#include "Timer.h"

static unsigned int g_timer0_count;
static unsigned int g_timer0_count_target;
static unsigned int g_timer0_period;
static pftimer_callback g_timer0_pf;

//11.0629MHZ
//one instruction cost 1/11.0629 * 12 = 1.085us
//timer pricision is 1.085us

/*
//auto find the proper timer period and count
void Find_Timer_Param(unsigned int microseconds, unsigned int *count, unsigned int *period)
{
	//count * period = time
	//count: 1 ~ 65536
	//period: 1us ~ 65535us
	//time: 1us ~ 4294836225us
	//calc the minimal count
	unsigned long i, j;
	unsigned long m;
	unsigned char find=0;
	
	m = (0==microseconds) ? 1*1000L : microseconds*1000L; //us
	
	for (i=0; i<65536; i++)
	{
		for (j=0; j<65536; j++)
		{
			//P1_6 = 0; //for debug
			if (i*j == m) //the command is very slowly, about 320us
			//if (i*j*1.085 - m <= 2.0) //11.0592MHz
			{
				find = 1;
				break;
			}
			//P1_6 = 1; //for debug
		}
		
		if (1==find)
		{
			break;
		}
	}
	
	*count = i;
	*period = j;
}

void Timer0_Init(unsigned int microseconds, pftimer_callback timer_callback)
{
	unsigned int count = 0;
	unsigned int period = 0;

	P1_6 = 0;
	Find_Timer_Param(microseconds, &count, &period);
	P1_7 = 0;
	
	//counter add 1 every 1.085 us
	TMOD = 0x01; //use timer0 with 16bits value
	TL0  = (65536 - (unsigned int)(period/1.085)) & 0xFF; //period us
	TH0  = (65536 - (unsigned int)(period/1.085)) >> 8;
	TR0  = 0; //timer0 default don't start
	TF0  = 0; //clear overflow flag of timer0
	ET0  = 1; //enable timer0 interrupt
	PT0  = 0; //set timer0 interrupt Priority
	EA   = 1; //enable system interrupt
	
	g_timer0_count = 0;
	g_timer0_count_target = count;
	g_timer0_period = period/1.085;
	g_timer0_pf = timer_callback;
}
*/

void Timer0_Init(unsigned int count, unsigned int period, pftimer_callback timer_callback)
{
	unsigned int p = (unsigned int)(period/1.085);
	
	//counter add 1 every 1.085 us
	TMOD = 0x01; //use timer0 with 16bits value
	TL0  = (65536 - p) & 0xFF; //period us
	TH0  = (65536 - p) >> 8;
	TR0  = 0; //timer0 default don't start
	TF0  = 0; //clear overflow flag of timer0
	ET0  = 1; //enable timer0 interrupt
	PT0  = 0; //set timer0 interrupt Priority
	EA   = 1; //enable system interrupt
	
	g_timer0_count = 0;
	g_timer0_count_target = count;
	g_timer0_period = p;
	g_timer0_pf = timer_callback;
}


void Timer0_Start()
{
	TR0 = 1;
}

void Timer0_Stop()
{
	TR0 = 0;
}

void Timer0_Rountine(void) interrupt 1
{
	TL0 = (65536 - g_timer0_period) & 0xFF;
	TH0 = (65536 - g_timer0_period) >> 8;
	g_timer0_count++;
	
	if(g_timer0_count >= g_timer0_count_target)
	{
		g_timer0_count = 0;
		
		if(g_timer0_pf)
		{
			g_timer0_pf(0);
		}
	}
}
