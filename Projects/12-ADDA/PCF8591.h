#ifndef _PCF8591_H_
#define _PCF8591_H_

enum AD_CHANNEL
{
	EAD_CHANNEL_0 = 0,
	EAD_CHANNEL_1 = 1,
	EAD_CHANNEL_2 = 2,
	EAD_CHANNEL_3 = 3
};

unsigned int PCF8591_ReadAD(enum AD_CHANNEL ch);


#endif
