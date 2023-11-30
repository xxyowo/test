#include<reg51.h>
#include"lcd.h"
#include"DS18B20.h"
#include"show_temp.h"
#include"delay.h"
sbit beep=P1^5;
sbit PWM=P1^0;
unsigned int num[4],temp;
float tmp,x;
unsigned char sign;
unsigned char receiveData[2];

void BEEP()//温度报警
{
	if(tmp-x<1e-7)
		PWM=0;//PWM=1转动
	else
	{
		PWM=1;
		beep=1;
		delay1ms(1);
		beep=0;
		delay1ms(1);
	}
}
void DISPLAY()//阈值温度显示到LCD
{
	unsigned char i;
	Lcd1602_Write_Cmd(0x80+11);
	for(i=0;i<2;i++)
	  Lcd1602_Write_Data(receiveData[i]);
	/* 显示℃*/
    Lcd1602_Write_Cmd(0x80+13);
	Lcd1602_Write_Data(0xdf);
	Lcd1602_Write_Cmd(0x80+14); 
	Lcd1602_Write_Data('C');

}
float displayTemperature()//在LcD上显示温度
{
	unsigned int i;
	float f;
	if(temp<0)
		tmp=(~temp+1)*0.0625; 
	else
		tmp=temp*0.0625; 
	num[0]=(int)tmp/10;
	num[1]=(int)tmp%10;
	f=(float)(tmp-(num[0]*10+num[1]));
	i=(int)(f*100);
	num[2]=i/10;
	num[3]=i%10;	   
	/*显示十位*/
	Lcd1602_Write_Cmd(0x80+0x40);
	Lcd1602_Write_Data(num[0]+0x30);
	/*显示个位*/
	Lcd1602_Write_Cmd(0x80+0x40+1);
  Lcd1602_Write_Data(num[1]+0x30);
	/*显示小数点*/
	Lcd1602_Write_Cmd(0x80+0x40+2);
	Lcd1602_Write_Data('.');
	/*显示小数点后一位*/
	Lcd1602_Write_Cmd(0x80+0x40+3);
	Lcd1602_Write_Data(num[2]+0x30);
	/*显示小数点后两位*/
	Lcd1602_Write_Cmd(0x80+0x40+4);
	Lcd1602_Write_Data(num[3]+0x30);
	/* 显示℃*/
  Lcd1602_Write_Cmd(0x80+0x40+5);
	Lcd1602_Write_Data(0xdf);
	Lcd1602_Write_Cmd(0x80+0x40+6); 
	Lcd1602_Write_Data('C');
	return tmp;			  
}

void send()//向PC端发送温度
{
	unsigned int i;
  ES=0;
	for(i=0;i<2;i++)
	{
		SBUF=num[i]+0x30; //发数据
		while(!TI);
		TI=0;//清除标志位
	}
	SBUF='.'; //发数据
  while(!TI);
  TI=0;//清除标志位
	for(i=2;i<4;i++)
	{
		SBUF=num[i]+0x30; //发数据
  	while(!TI);
		TI=0;//清除标志位
	}
	SBUF=' '; //发送空格，进行间隔
  while(!TI);
  TI=0;//清除标志位
	ES=1;
}
void UsartConfiguration()
{
	  SCON=0X50; //设置为工作方式1
    PCON=0X00; //波特率不倍增
    TMOD=0X20; //设置计数器工作方式2
    TL1=0xfA;//波特率4800
    TH1=0xfA;
    TR1=1; //启动计数器
    EA=1; //开中断
    ES=1;
}
void show_init()
{
	unsigned char code name[10]="0303/0304:";
	unsigned int i;
	InitLcd1602();
	UsartConfiguration();//串口通信初始化
	Lcd1602_Write_Cmd (0x80);
	for(i=0;i<10;i++)
	Lcd1602_Write_Data (name[i]);
}
	
void show_temp()
{
	unsigned char i;
	temp=Ds18b20ReadTemp();//读取DS18B20的温度
	tmp=displayTemperature();//进行温度转换
	send();
	(float)x=(receiveData[0]-0x30)*10+receiveData[1]-0x30;
	if(sign)
		{
			DISPLAY();
			for(i=0;i<50;i++)
			{
				BEEP();
			}
		}
}
/*void show()
{
	unsigned char i;
	UsartConfiguration();//串口通信初始化
	temp=Ds18b20ReadTemp();//读取DS18B20的温度
	tmp=displayTemperature();//进行温度转换
	send();
}*/
