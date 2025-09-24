#include <REGX52.H>
#include "PCF8591.h"
#include "I2C.h"

sbit PCF8591_SDA = P2^0;
sbit PCF8591_SCL = P2^1;

#define PCF8591_ADDRESS_W  0x90 //8bits: 1 0 0 1 A2 A1 A0 R/W
#define PCF8591_ADDRESS_R  0x91 //8bits: 1 0 0 1 A2 A1 A0 R/W
#define PCF8591_AD_CONTROL 0x00 //8bits: 0 0 00 0 0 00/01/10/11


unsigned int PCF8591_ReadAD(enum AD_CHANNEL ch)
{
	unsigned int value;
	
	//write config
	I2C_Start();
	
	//send address
	I2C_SendByte(PCF8591_ADDRESS_W);
	I2C_ReceiveAck();
	
	//send control
	I2C_SendByte(PCF8591_AD_CONTROL | (ch & 0x3));
	I2C_ReceiveAck();
	
	I2C_Stop();
	
	//------
	
	//read AD value
	I2C_Start();
	
	I2C_SendByte(PCF8591_ADDRESS_R);
	I2C_ReceiveAck();
	
	value = I2C_ReceiveByte();
	I2C_SendAck(1);
	
	I2C_Stop();
	
	return value;
}
