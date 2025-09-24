#include <REGX52.H>

sbit OneWire_Pin = P2^2;


unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char ack;
	
	OneWire_Pin = 1; //init state
	OneWire_Pin = 0; //pull low and stay 480~960us
	i = 230; while (--i); //wait 500us;
	OneWire_Pin = 1; //release bus, need wait 15~60us
	i = 31;  while (--i); //wait 70us, then sample to get ack
	
	//slave issue presence pulse, at least 480us
	ack = OneWire_Pin;
	i = 230; while (--i); //wait 500us
	
	return ack;
}

static void OneWire_WriteBit(unsigned char b)
{
	unsigned char i;

	OneWire_Pin = 1;
	OneWire_Pin = 0; //pull low and stay at least 15us
	i = 3; while (--i); //wait 10us
	OneWire_Pin = b; //assign value and stay >45us (if b is 1, <120us)
	i = 22; while (--i); //wait 50us
	OneWire_Pin = 1; //release bus
}

static unsigned char OneWire_ReadBit()
{
	unsigned char i;
	unsigned char b;

	OneWire_Pin = 1;
	OneWire_Pin = 0; //pull low and wait near by 15us and sample, then wait about 45us
	i = 3; while (--i); //wait 10us
	b = OneWire_Pin;
	i = 22; while (--i); //wait 50us
	//slave device will release the bus (OneWire_Pin = 1)
	
	return b;
}

void OneWire_WriteByte(unsigned char value)
{
	unsigned char i;
	
	for (i=0; i<8; i++)
	{
		OneWire_WriteBit(value & (1<<i));
	}
}

unsigned char OneWire_ReadByte()
{
	unsigned char i;
	unsigned char value=0x00;
	
	for (i=0; i<8; i++)
	{
		//value |= (OneWire_ReadBit() << i);
		if (OneWire_ReadBit()) {value |= (0x01<<i);}
	}
	
	return value;
}
