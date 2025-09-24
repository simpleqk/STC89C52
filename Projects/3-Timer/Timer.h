#ifndef _TIMER_H_
#define _TIMER_H_


typedef void (*pftimer_callback)(char timer_id);

//void Timer0_Init(unsigned int microseconds, timer_callback pftimer_callback); //very slowly
void Timer0_Init(unsigned int count,  unsigned int period, pftimer_callback timer_callback); //time = count * period us

void Timer0_Start();
void Timer0_Stop();

#endif
