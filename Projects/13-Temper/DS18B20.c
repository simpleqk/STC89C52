#include <REGX52.H>
#include "OneWire.h"
//#include  "LCD1602.h"

//TRANSACTION SEQUENCE
//The protocol for accessing the DS18B20 via the 1-Wire port is as follows.
//1-Initialization
//2-ROM Function Command
//3-Memory Function Command
//4-Transaction/Data

#define DS18B20_CMD_ROM_READ         0x33
#define DS18B20_CMD_ROM_MATCH        0x55
#define DS18B20_CMD_ROM_SKIP         0xCC
#define DS18B20_CMD_ROM_SEARCH       0xF0
#define DS18B20_CMD_ROM_ALARM_SEARCH 0xEC

#define DS18B20_CMD_MEM_WRITE        0x4E
#define DS18B20_CMD_MEM_READ         0xBE
#define DS18B20_CMD_MEM_COPY         0x48
#define DS18B20_CMD_MEM_CONVERT      0x44
#define DS18B20_CMD_MEM_RECALL       0xE2

#define DS18B20_CMD_POW_READ         0xB4


static void DS18B20_ConvertTemperature()
{
	OneWire_Init();
	
	OneWire_WriteByte(DS18B20_CMD_ROM_SKIP);
	OneWire_WriteByte(DS18B20_CMD_MEM_CONVERT);	
}

static float DS18B20_ReadTemperature()
{
	float fTemper = 0.0;
	unsigned char LSB=0, MSB=0;
		
	OneWire_Init();
	
	OneWire_WriteByte(DS18B20_CMD_ROM_SKIP);
	OneWire_WriteByte(DS18B20_CMD_MEM_READ);
	
	LSB = OneWire_ReadByte(); //LSB
	MSB = OneWire_ReadByte(); //MSB
	
	//for test
	//LCD1602_Clear();
	//LCD1602_DisplayNum(0,0,MSB);
	//LCD1602_DisplayNum(0,8,LSB);
	
	fTemper = ((MSB<<8) | LSB) / 16.0; //LSB low 4bit need >>4
	
	return fTemper;
}


float DS18B20_GetTemperature()
{
	float fTemper = 0.0;
	
	DS18B20_ConvertTemperature();
	
	fTemper = DS18B20_ReadTemperature();
	
	return fTemper;
}
