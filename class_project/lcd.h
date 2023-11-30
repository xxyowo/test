#ifndef _LCD_H_
#define _LCD_H_
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define LCD1602_DB P0
sbit LCD1602_EN=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;
void Lcd1602_Write_Cmd(uchar com);
void Lcd1602_Write_Data(uchar dat);
void InitLcd1602();
void Read_Busy();
void ShowStr(uchar *str);
void display(uchar str[]);
void display_1(uchar str[]);
#endif