#include <REGX52.H>
#include "PCF8591.h"
#include "LCD1602.h"
#include "DelayMs.h"

void main()
{
	unsigned int value;
	
	LCD1602_Init();
	LCD1602_DisplayStr(0,0,"AD Test");
	
	while(1)
	{
		value = PCF8591_ReadAD(EAD_CHANNEL_0);
		//value = (value / 256.0 * 3) * 10;
		LCD1602_DisplayNum(1,0, value);
		delay_100ms();
		
		value = PCF8591_ReadAD(EAD_CHANNEL_1);
		LCD1602_DisplayNum(1,4, value);
		delay_100ms();

		value = PCF8591_ReadAD(EAD_CHANNEL_2);
		LCD1602_DisplayNum(1,8, value);
		delay_100ms();
		
	}
}
