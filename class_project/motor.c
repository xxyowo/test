#include"motor.h"

sbit LED=P2^0;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
unsigned int timer;
unsigned int count_motor;
/*void delay(unsigned char i)
{
	unsigned char j;
	for(;i>0;i--)
	for(j=0;j<125;j++);
}

void Motor_Init()
{
	EA=0;
	TMOD=0x10; 
  TH1=0xFF; //设定T1初值，每计数一次触发中断
  TL1=0x1c;
	
	ET1=1; //开T1中断
	TR1=1;//开定时器T1

	//外部中断
	EX0=0;
	IT0=0;//电平触发
}*/

void Compare(unsigned int fan)
{
	
	if(timer<fan)
	{
		PWM=1;//PWM=1转动
	  LED=0;//LED=0灯亮
	}
  else
	{
		PWM=0;
		LED=1;
	}
}
/*
void display(unsigned int level)
{
	unsigned char bit_table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80};
	LSA=1;
	LSB=1;
	LSC=1;
	P0=bit_table[level];
	delay(1);
}*/
void zhuandong()
{
	switch(count_motor)
		{
			case 0: Compare(50);break;
		  case 1: Compare(30);break;
		  case 2: Compare(75);break;
			case 3: Compare(100);break;
		}
}
