#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

void I2C_Start()
{
	I2C_SCL = 0;
	I2C_SDA = 1; //release SDA bus
	
	I2C_SCL = 1;
	I2C_SDA = 0; //high-to-low
	
	I2C_SCL = 0;	
}

void I2C_Stop()
{
	I2C_SCL = 0;
	I2C_SDA = 0;
	
	I2C_SCL = 1;
	I2C_SDA = 1; //low-to-high
}

void I2C_SendByte(unsigned char byte)
{
	unsigned char i;

	I2C_SCL = 0; //init low level for changing data
	
	for (i=0; i<8; i++)
	{
		I2C_SDA = byte & (0x80 >> i);
		I2C_SCL = 1; //notify sampling
		I2C_SCL = 0;
	}
}

void I2C_SendAck(unsigned char ackBit)
{
	I2C_SCL = 0;

	I2C_SDA = ackBit;
	I2C_SCL = 1; //notify sampling
	I2C_SCL = 0;
}

unsigned char I2C_ReceiveByte()
{
	unsigned char byte = 0x00;
	unsigned char i;
	
	I2C_SCL = 0; //notify slave device to set value
	I2C_SDA = 1; //release SDA bus
	
	for (i=0; i<8; i++)
	{
		I2C_SCL = 1; //notify sampling to read value
		if(1 == I2C_SDA) { byte |= (0x80>>i); }
		I2C_SCL = 0;
	}
	
	return byte;
}

unsigned char I2C_ReceiveAck()
{
	unsigned char ackBit = 0x00;
	
	I2C_SCL = 0;
	I2C_SDA = 0; //init sda value

	I2C_SCL = 1;
	ackBit = I2C_SDA;
	I2C_SCL = 0;
}
