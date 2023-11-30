#ifndef _DS18B20_H_
#define _DS18B20_H_
#include<reg51.h>
unsigned char Ds18b20Init();
void Ds18b20WriteByte(unsigned char dat);
unsigned char Ds18b20ReadByte();
void Ds18b20ChangTemp();
void Ds18b20ReadTempCom();
int Ds18b20ReadTemp();
#endif