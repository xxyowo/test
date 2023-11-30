#include<reg51.h>
#include"password.h"
#include"show_temp.h"
#include"DS18B20.h"
#include"clock.h"
#include"delay.h"
#define uchar unsigned char  
#define uint unsigned int 
void main(void)
{
	begin();
	show_init();
  while(1)
		{
			if(K4==0)
			{
				show_clock();
			}
			else
			{
				//EA=0;
				show_temp();
			}
		}
}


void intes( ) interrupt 4 //串口中断函数，向PC机发送温度
{
	unsigned char m;
	sign=0;
  receiveData[m] = SBUF; //读取数据
  RI = 0; //清除标志位
	m++;
	if(m==2)
		{
			sign=1;
			m=0;
	  }
}




