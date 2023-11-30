#ifndef _SHOW_TEMP_H_
#define _SHOW_TEMP_H_
#include<reg51.h>
extern unsigned char receiveData[2];
extern unsigned char sign;
void UsartConfiguration();
void show_temp();
void show_init();
void show();
#endif