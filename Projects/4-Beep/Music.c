#include <REGX52.H>
#include "Timer.h"

//music scale: midlle
static int music_freq[] = {
	0,     // 0: pad bit
  //500,   // test         2000/2 us, actual 2.0/2ms
    523,   // 1: do  C4    1912/2 us, actual 2.5/2ms
    587,   // 2: re  D4    1570/2 us, actual 2.4/2ms
    659,   // 3: mi  E4    1398/2 us, actual 1.6/2ms
    698,   // 4: fa  F4    1320/2 us, actual 2.0/2ms
    784,   // 5: sol G4    1175/2 us, actual 1.9/2ms
    880,   // 6: la  A4    1047/2 us, actual 1.8/2ms
    988,   // 7: si  B4    932/2  us, actual 1.1/2ms
};

static int music_half_period_us[] = {
	0,     // 0: pad bit
    956,   // 1: do  C4    956*2 us
    852,   // 2: re  D4    852*2 us
    759,   // 3: mi  E4    759*2 us
    716,   // 4: fa  F4    716*2 us
    638,   // 5: sol G4    638*2 us
    568,   // 6: la  A4    568*2 us
    506,   // 7: si  B4    506*2 us
};


//
void timer_callback(char timer_id)
{
	timer_id;
	
	//turn on/off beep
	P2_3 = ~P2_3;
	
}

void Music_Start(unsigned char music_note)
{
	unsigned int half_period_us = 0;
	
	if (music_note>0 & music_note<9)
	{
		//half_period_us = (unsigned int)(1000000L / 2 / music_freq[music_note]);
		half_period_us = music_half_period_us[music_note];
	
		Timer0_Stop();
		Timer0_Init(1, half_period_us, timer_callback);
		Timer0_Start();
	}
	else
	{
		P2_3 = 1; //turn off
		Timer0_Stop();
	}
}
