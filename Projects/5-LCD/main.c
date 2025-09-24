#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD1602_Init();
	LCD1602_DisplayNum(0,1,2025);
	LCD1602_DisplayStr(1,5,"WELCOM 2025");
	
	while(1);
}
