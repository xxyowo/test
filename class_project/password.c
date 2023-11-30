#include"lcd.h"
#include"delay.h"
#include<string.h>
#include"password.h"
//#include"eeprom.h"
uchar code str[]="password:";
uchar code str_3[]="change:";
uchar code str_1[]="welcome!";
uchar code str_2[]="wrong";
uchar code clear[]="password:       ";
uchar back[]=" ";
char pass[]="012456";//将密码设置为“123456”；
char input[]="      ";//赋初值，不赋初值会寄
uchar start=0,add=0,last=0,enter=0,flag=1,len=0,clc=0,write=0,len_2=0;
char keyvalue;
uchar code lcd[]={0x31,0x32,0x33,0x50, //1 2 3 P（开始输入,唤醒密码输入功能）
                  0x34,0x35,0x36,0x51, //4 5 6 Q（清屏已输入的）
                  0x37,0x38,0x39,0x52, //7 8 9 R（回删一位）
                  0x20,0x30,0x23,0x53};//  0 # S(enter进入)
void KeyBoard()
{
	char a=0;
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay1ms(10);//延时10ms进行消抖
	if(P1!=0x0f)//再次检查键盘是否按下
	{
		add++;//显示在第几个lcd上
		P1=0xf0;//测试行
		switch(P1)
		{
			case(0x70):keyvalue=0;break;//1行
			case(0xb0):keyvalue=1;break;//2行
			case(0xd0):keyvalue=2;break;//3行
			case(0xe0):keyvalue=3;break;//4行
		}
		P1=0x0f;//测试列
		switch(P1)
		{
			case(0x07):keyvalue=keyvalue*4+0;break;//1列
			case(0x0b):keyvalue=keyvalue*4+1;break;//2列
			case(0x0d):keyvalue=keyvalue*4+2;break;//3列
			case(0x0e):keyvalue=keyvalue*4+3;break;//4列
		}
		//按键消抖
		while((a<10)&&(P1!=0xf0))//按键松手检测
		{
			delay1ms(10);
			a++;
		}
		
		if(write==0)
		{
		if(keyvalue!=3&&keyvalue!=7&&keyvalue!=11&&keyvalue!=15)
		{
			if(len<6)
			{
				input[len]=keyvalue+0x30;//必须加0x30
			}
			Lcd1602_Write_Cmd(0x88+add);
			Lcd1602_Write_Data(lcd[keyvalue]);
			//Lcd1602_Write_Data(0x2a);
			len++;
		}
		}
		if(write==1)
		{
			if(len_2<6)
			{
				input[len_2]=keyvalue+0x30;//必须加0x30
				pass[len_2]=input[len_2];
			}
			Lcd1602_Write_Cmd(0xc7+len_2);
			Lcd1602_Write_Data(lcd[keyvalue]);
			//Lcd1602_Write_Data(0x2a);
			len_2++;
		}
		
		if(keyvalue==3)
		{
			start=1;
		}
		if(keyvalue==7)
		{
			clc=1;
		}
		if(keyvalue==11)
		{
			last=1;
		}
		if(keyvalue==15)
		{
			enter=1;
		}
		if(keyvalue==12)
		{
			write=1;
		}
		
		if(keyvalue==3||keyvalue==7||keyvalue==11||keyvalue==15||keyvalue==12)
		{
			add--;//不为键值就不后移
		}
	}
 }
}

void begin()
{
	InitLcd1602();
	while(1)
	{
		KeyBoard();
		//开始输入密码
		while(start==1)
		{
			display(str);
			KeyBoard();
			//整行清除
			if(clc==1)
			{
				display(clear);
				add=0;
				len=0;
				enter=0;
				clc=0;
			}
			//回删一位
			if(last==1)
			{
				Lcd1602_Write_Cmd(0x88+add);
				Lcd1602_Write_Data(*back);
				len--;
				add--;
				last=0;
				
			}
			
			//改密码
			if(write==1)
			{
				display_1(str_3);
				
				if(len_2==6)
				{
					len=0;
					add=0;
				  write=0;
				}
			}
			
			//判断密码是否为6位
			if(len==7&&enter==1||len<6&&enter==1)
		   {
			   display_1(str_2);
		   }
		  if(len==6)
		  {
				//判断两个数组是否相等
				if (strcmp(input,pass)==0)
				{
					flag=1;
				}
				else
				{
					flag=0;
				}
			  if(flag==1&&enter==1)
			  {
				  display_1(str_1);
					delay1ms(500);
					InitLcd1602();
					return;
			  }
			  if(flag==0&&enter==1)
			  {
				  display_1(str_2);
					add=0;
				  len=0;
					enter=0;
			  }
		  }
		}
	}
}