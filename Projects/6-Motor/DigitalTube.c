#include <REGX52.H>

static char code number_map_table[] = {
	0x3F,  //"0"
	0x06,  //"1"
	0x5B,  //"2"
	0x4F,  //"3"
	0x66,  //"4"
	0x6D,  //"5"
	0x7D,  //"6"
	0x07,  //"7"
	0x7F,  //"8"
	0x6F,  //"9"
	0x77,  //"A"
	0x7C,  //"B"
	0x39,  //"C"
	0x5E,  //"D"
	0x79,  //"E"
	0x71,  //"F"
	0x76,  //"H"
	0x38,  //"L"
	0x40,  //"-"
	0x00,  //turn off
};


void DigitalTube_Display(unsigned int value)
{
	unsigned char i = 0;
	unsigned char v = 0;
	unsigned int  t = 0;
	
	if(0 == value)
	{
		//select unit
		P2_7 = 1;
		P0 = ~(1 << 7);
		P2_7 = 0;
		
		//set unit value
		P2_6 = 1;
		P0 = number_map_table[v];
		P2_6 = 0;
		
		//need delay some time
		for(t=0; t<1000; t++);		
	}
	
	while(value > 0)
	{
		i++;
		v = value % 10;
		
		//select unit
		P2_7 = 1;
		P0 = ~(1 << (8-i));
		P2_7 = 0;
		
		//set unit value
		P2_6 = 1;
		P0 = number_map_table[v];
		P2_6 = 0;
		
		value = value / 10;
		
		//need delay some time
		for(t=0; t<100; t++);
	}
}

void DigitalTube_clear()
{
	unsigned int i=0;
	
	for (i=1; i<=8; i++)
	{
		//select unit
		P2_7 = 0;
		P0 = ~(1 << (8-i));
		P2_7 = 1;
		
		//set unit value
		P2_6 = 0;
		P0 = 0;
		P2_6 = 1;
	}
}
