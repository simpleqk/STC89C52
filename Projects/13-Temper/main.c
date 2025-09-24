#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "DelayMs.h"
#include "OneWire.h"

void main()
{
	float fTemper = 0.0;
	unsigned char ack;
	
	LCD1602_Init();
	LCD1602_DisplayStr(0,0, "DS18B20 Temperature");
	
	ack = OneWire_Init();
	LCD1602_DisplayNum(0, 0, ack);
	
	while(1)
	{
		fTemper = DS18B20_GetTemperature();
		if(fTemper < 0.0)
		{
			fTemper = -fTemper;
			LCD1602_DisplayStr(1,0, "-");
		}
		else
		{
			LCD1602_DisplayStr(1,0, "+");
		}
		
		LCD1602_DisplayNum(1,1, (int)fTemper);
		LCD1602_DisplayStr(1,4, ".");
		LCD1602_DisplayNum(1,5, (int)(((long)(fTemper*10000)) % 10000));
		
		delay_500ms();
	}
}
