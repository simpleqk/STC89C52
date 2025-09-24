#include <REGX51.H>
#include "DelayMs.h"
#include "Timer.h"
#include "DigitalTube.h"

#define STEPPER_MOTOR //if not define, use DC motor

unsigned char motor_speed;
unsigned int  timer_count;

enum
{
	EMOTOR_SPEED_1 = 2,
	EMOTOR_SPEED_2 = 5,
	EMOTOR_SPEED_3 = 6
};

#ifdef STEPPER_MOTOR
unsigned char motor_enable;

//motor type: 28BYJ-48, rotate 1 circle need 4096 steps
#define STEPS_PER_REVOLUTION 4096

//driver mode
//A -> AB -> B -> BC -> C -> CD -> D -> DA
unsigned char code stepper_motor_rotate_seq_v1[] = {0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //1 phase 2 phase alternating excitation
//AB -> BC -> CD -> DA -> AB -> BC -> CD
unsigned char code stepper_motor_rotate_seq_v2[] = {0xf3,0xf6,0xfc,0xf9,0xf3,0xf6,0xfc,0xf9}; //just 2 phase
//A -> B -> C -> D -> A -> B -> C -> D
unsigned char code stepper_motor_rotate_seq_v3[] = {0xf1,0xf2,0xf4,0xf8,0xf1,0xf2,0xf4,0xf8}; //just 1 phase

void stepper_motor_rotate_angle(int angle, unsigned char *seq)
{
	int i;
	int steps = (int)(((unsigned long)(angle>0 ? angle : -angle) * STEPS_PER_REVOLUTION) / 360);
	
	if (angle > 0)
	{
		//clockwise
		for(i=0; i<steps; i++)
		{
			P1 = seq[i%8];
			delay_1ms(); //control speed
		}
	}
	else
	{
		//counterclockwise
		for(i=steps; i>=0; i--)
		{
			P1 = seq[i%8];
			delay_1ms(); //control speed
		}	
	}
}

void stepper_motor_rotate_cw(unsigned char *seq)
{
	int i;

	for(i=0; i<8; i++)
	{
		P1 = seq[i];
		delay_1ms(); //control speed, more slowly for sinlge 2 phase or 1 phase mode
	}
}

void stepper_motor_rotate_ccw(unsigned char *seq)
{
	int i;

	for(i=7; i>=0; i--)
	{
		P1 = seq[i];
		delay_1ms(); //control speed
	}
}

#else

sbit motor_enable = P1^0;
#endif //DC_MOTOR


//key press jitter feature
//|--------- 5~10ms --------|------ 50~200ms ------|------- 5~10ms -------|
//|--jitter downward range--|-----stable range-----|--jitter upward rang--|
char is_key_press(unsigned char key)
{
	char press = 0;
	
	if(0 == key)
	{
		delay_10ms();
		press  = (0 == key) ? 1 : 0;
		press &= (0 == key) ? 1 : 0;
		press &= (0 == key) ? 1 : 0;
		delay_10ms();
	}
	
	return press;
}

void scan_indenpend_keys()
{
	//S2
	//P1_0 = (1 == is_key_press(P3_0)) ? 0 : 1;
	//if(0 == P1_0)
	//{
	//	motor_enable = 0;
	//}
	if(1 == is_key_press(P3_0))
	{
		motor_enable = 0;
		motor_speed = 0; //motor stop
	}
	
	//S3
	P1_1 = (1 == is_key_press(P3_1)) ? 0 : 1;
	if(0 == P1_1)
	{
		motor_enable = 1;
		motor_speed = EMOTOR_SPEED_1; //Duty Cycle: 2/10
	}
	
	//S4
	P1_2 = (1 == is_key_press(P3_2)) ? 0 : 1;
	if(0 == P1_2)
	{
		motor_enable = 1;
		motor_speed = EMOTOR_SPEED_2;  //Duty Cycle: 5/10
	}
	
	//S5
	P1_3 = (1 == is_key_press(P3_3)) ? 0 : 1;
	if(0 == P1_3)
	{
		motor_enable = 1;
		motor_speed = EMOTOR_SPEED_3; //Duty Cycle: 6/10
	}
}

void timer_callback(char timer_id)
{
	timer_count++;	
	timer_count %= 10;
	
	if (motor_speed > 0)
	{
		if (timer_count < motor_speed)
		{
			motor_enable = 1;
		}
		else
		{
			motor_enable = 0;
		}
	}
}


void main(void)
{
	char i;

#ifndef STEPPER_MOTOR //use DC motor
	Timer0_Init(10, 1000, timer_callback);
	Timer0_Start();
#endif //STEPPER_MOTOR

	motor_enable = 0;
	
	while(1)
	{
		DigitalTube_Display(motor_speed);

		scan_indenpend_keys();

#ifdef STEPPER_MOTOR //use stepper motor
		if(motor_enable)
		{
			switch(motor_speed)
			{
				case EMOTOR_SPEED_1:
					stepper_motor_rotate_cw(stepper_motor_rotate_seq_v1);
					break;
				case EMOTOR_SPEED_2:
					stepper_motor_rotate_ccw(stepper_motor_rotate_seq_v1);				
					break;
				case EMOTOR_SPEED_3:
					stepper_motor_rotate_angle(90, stepper_motor_rotate_seq_v1);
					delay_500ms();
					stepper_motor_rotate_angle(-90, stepper_motor_rotate_seq_v1);
					delay_500ms();
					break;
			}
		}
#endif //STEPPER_MOTOR		
	}
}
