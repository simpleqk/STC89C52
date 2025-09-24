#include <REGX52.H>
#include "DelayMs.h"
#include "LCD1602.h"
#include "AT24C02.h"

void main()
{
	unsigned char value;
	
	LCD1602_Init();
	LCD1602_DisplayStr(0, 1, "EEPROM RW - I2C");
	
	AT24C02_WriteByte(200, 131);
	delay_10ms();
	value = AT24C02_ReadByte(200);
	
	LCD1602_DisplayNum(1, 1, value);

	while(1)
	{
	}
}
