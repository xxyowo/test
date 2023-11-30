#include"DS18B20.h"
sbit DSIO=P3^7;
void Delayms1(unsigned int n)
{
	unsigned int i,j;
  for(j=n;j>0;j--)
  for(i=112;i>0;i--);
}
unsigned char Ds18b20Init()
{
	unsigned int i;
  DSIO=0; 
  i=80;
	while(i--);//持续低电平
	DSIO=1;//拉高
	i=0;
	while(DSIO) //检测是否存在DS18B20应答低电平信号
{
	i++;
	if(i>50000)//等待>50MS
		return 0;
}
return 1;
}

void Ds18b20WriteByte(unsigned char dat)
{
	unsigned int i,j;
  for(j=0;j<8;j++)
  {
		DSIO=0; //先拉低总线1us
    i++;
    DSIO=dat&0x01; //从最低位开始输入
    i=6;
    while(i--); //延时60us以上，让DS18B20读取到输入的信息
    DSIO=1; //释放总线
    dat>>=1;//移位，继续写入
		}
}

unsigned char Ds18b20ReadByte()
{
	unsigned char byte,bi;
  unsigned int i,j;
  for(j=8;j>0;j--)
	{
		DSIO=0;//拉低1us
    i++;
    DSIO=1;//让DS18B20把数据传到总线上
    i++;
    i++;//延时6us等待数据稳定
    bi=DSIO; //从最低位开始读取数据
    byte=(byte>>1)|(bi<<7); //byte右移1位，bi左移七位，两者相与
    i=4; 
    while(i--);//读取完后等待48us再读取下一位
		}
	return byte;
}

void Ds18b20ChangTemp()//写入温度转换指令
{
	Ds18b20Init();//DS18B20初始化
  Delayms1(1);
  Ds18b20WriteByte(0xcc); //跳过ROM
  Ds18b20WriteByte(0x44); //温度转换命令
  Delayms1(100);
}

void Ds18b20ReadTempCom()//写入读取温度指令
{
	Ds18b20Init();//DS18B20初始化
  Delayms1(1);
  Ds18b20WriteByte(0xcc); //跳过ROM
  Ds18b20WriteByte(0xbe); //发送读取温度命令
}

int Ds18b20ReadTemp()//读取温度
{
	unsigned int temp;
  unsigned char tmh,tml;
  Ds18b20ChangTemp(); //写入转换指令
  Ds18b20ReadTempCom();//写入读取温度指令
  tml=Ds18b20ReadByte(); //读取温度，16位，低八位
  tmh=Ds18b20ReadByte(); //高八位
  temp=tmh;
  temp<<=8; //
  temp|=tml; //
  return temp;
}
