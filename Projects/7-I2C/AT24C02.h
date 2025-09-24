#ifndef _AT24C02_H_
#define _AT24C02_H_

//address range: 0~255
void AT24C02_WriteByte(unsigned char address, unsigned char byte);
unsigned char AT24C02_ReadByte(unsigned char address);


#endif