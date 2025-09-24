#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

unsigned char OneWire_Init();
void OneWire_WriteByte(unsigned char value);
unsigned char OneWire_ReadByte();

#endif
