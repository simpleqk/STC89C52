#include <REGX51.H>

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

//key press jitter feature
//|--------- 5~10ms --------|------ 50~200ms ------|------- 5~10ms -------|
//|--jitter downward range--|-----stable range-----|--jitter upward rang--|
char is_key_press(unsigned char key)
{
	char press = 0;
	
	if(0 == key)
	{
		delay_10ms();
		press = (0 == key) ? 1 : 0;
		delay_10ms();
	}
	
	return press;
}

void scan_indenpend_keys()
{
	//S2
	P1_0 = (1 == is_key_press(P3_0)) ? 0 : 1;
	//S3
	P1_1 = (1 == is_key_press(P3_1)) ? 0 : 1;
	//S4
	P1_2 = (1 == is_key_press(P3_2)) ? 0 : 1;
	//S5
	P1_3 = (1 == is_key_press(P3_3)) ? 0 : 1;
}

void scan_matrix_keys()
{
	//P3, H:col, L:row
	unsigned char cols[] = {~0x10,~0x20,~0x40,~0x80}; //set col from 1 to 4
	char count = sizeof(cols);
	char i = 0;
	char v = 0;
	
	for(i=0; i<count; i++)
	{
		P3 = cols[i];
		
		//check row from 1 to 4
		v = (1 == is_key_press(P3_0)) ? (1+i)  : 0;
		v = (1 == is_key_press(P3_1)) ? (5+i)  : v;
		v = (1 == is_key_press(P3_2)) ? (9+i)  : v;
		v = (1 == is_key_press(P3_3)) ? (13+i) : v;
		
		//light on led bits to indicate current key value
		P1 = ~v;
	}
}

void main(void)
{
	char scan_matrix = 0;
	
	while(1)
	{
		if(scan_matrix)
		{
			scan_matrix_keys();
		}
		else
		{
			scan_indenpend_keys();
		}
	}
}



