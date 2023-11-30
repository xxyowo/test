#ifndef _CLOCK_H_
#define _CLOCK_H_
#include<reg51.h>

sbit K4=P3^3;

void show_clock();
void ExitInit();
void ExitInit_isr();
#endif