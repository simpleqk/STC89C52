#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS_W 0xA0
#define AT24C02_ADDRESS_R 0xA1

void AT24C02_WriteByte(unsigned char address, unsigned char byte)
{
	I2C_Start();
	
	I2C_SendByte(AT24C02_ADDRESS_W);
	I2C_ReceiveAck();
	
	I2C_SendByte(address);
	I2C_ReceiveAck();
	
	I2C_SendByte(byte);
	I2C_ReceiveAck();
	
	I2C_Stop();
}

unsigned char AT24C02_ReadByte(unsigned char address)
{
	unsigned char byte;
	
	I2C_Start();
	
	I2C_SendByte(AT24C02_ADDRESS_W);
	I2C_ReceiveAck();
	
	I2C_SendByte(address);
	I2C_ReceiveAck();
	
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS_R);
	I2C_ReceiveAck();
	
	byte = I2C_ReceiveByte();
	I2C_SendAck(1);
	
	I2C_Stop();
	
	return byte;
}
