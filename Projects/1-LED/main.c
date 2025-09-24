#include <REGX52.H>
#include <intrins.h>

extern void delay_1ms(void);
extern void delay_2ms(void);
extern void delay_3ms(void);
extern void delay_4ms(void);
extern void delay_10ms(void);
extern void delay_20ms(void);
extern void delay_30ms(void);
extern void delay_40ms(void);
extern void delay_100ms(void);
extern void delay_200ms(void);
extern void delay_500ms(void);


void main()
{
	char i = 0;
	
	//light on 0th led
	P1_0 = 0;
	
	while(1)
	{
		//500ms
		delay_500ms();
		
		//P1_0 = ~P1_0;
		
		i++;
		
		if (i>16)
		{
			i=0;
			//rest to light on 0th led only
			P1 = 0xFE;
		}
		else if (i>8)
		{
			//continue light on next led
			P1 <<= 1;
		}
		else
		{
			//left circle shift, light on one led like stream
			P1 = _crol_(P1, 1);
		}
	}
}