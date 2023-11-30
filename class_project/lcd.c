#include"lcd.h"
#include"delay.h"
void Lcd1602_Write_Cmd(unsigned char cmd)//写入命令
{
	Read_Busy();
	LCD1602_RS=0;      
	LCD1602_RW=0;
	LCD1602_DB=cmd;
	delay1ms(10);
	LCD1602_EN=1;
	delay1ms(10);
	LCD1602_EN=0;
}
void Lcd1602_Write_Data(unsigned char dat)//写入数据
{
	Read_Busy();
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_DB=dat;
	delay1ms(10);
	LCD1602_EN=1;
	delay1ms(10);
	LCD1602_EN=0;
}
void InitLcd1602()//1602初始化
{
	Lcd1602_Write_Cmd(0x38);//打开5*8的8位数据
	Lcd1602_Write_Cmd(0x0c);//开显示，不显示光标
	Lcd1602_Write_Cmd(0x06);//地址加1，写入数据时光标右移
	Lcd1602_Write_Cmd(0x01);//清屏
}

//忙检测函数，判断bit7是0，允许执行；1禁止
void Read_Busy()
{
	uchar sta;
	LCD1602_DB=0xff;
	LCD1602_RS=0;
	LCD1602_RW=1;
	do
	{
		LCD1602_EN=1;
		sta=LCD1602_DB;//P0口
		LCD1602_EN=0;//使能。用完就拉低，释放总线
	}while(sta &0x80);
}
//显示字符串
void ShowStr(uchar *str)
{
	while(*str!='\0')
	{
		Lcd1602_Write_Data(*str++);
	}
}
void display(uchar str[])
{
	Lcd1602_Write_Cmd(0x80);//指明首地址
	ShowStr(str);//显示字符串
}
void display_1(uchar str[])
{
	Lcd1602_Write_Cmd(0xc0);//指明首地址
	ShowStr(str);//显示字符串
}
