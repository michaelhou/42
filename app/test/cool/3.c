//martin buttner
#include<stdio.h>
#include<math.h>
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
void initwindow();
void killwindow();
void writewindow(QWORD size,void* addr);
void uievent(QWORD* type,QWORD* key);




//
static DWORD palette[1024*1024];
static DWORD color;




//
#define _sq(x) ((x)*(x))
unsigned char RED(int i,int j)
{
	float x=0,y=0;int k;
	for(k=0;k++<256;)
	{
		float a=x*x-y*y+(i-768.0)/512;
		y=2*x*y+(j-512.0)/512;
		x=a;
		if(x*x+y*y>4)break;
	}
	return log(k)*47;
}
unsigned char GREEN(int i,int j)
{
	float x=0,y=0;
	int k;
	for(k=0;k++<256;)
	{
		float a=x*x-y*y+(i-768.0)/512;
		y=2*x*y+(j-512.0)/512;
		x=a;
		if(x*x+y*y>4)break;
	}
	return log(k)*47;
}
unsigned char BLUE(int i,int j)
{
	float x=0,y=0;int k;
	for(k=0;k++<256;)
	{
		float a=x*x-y*y+(i-768.0)/512;
		y=2*x*y+(j-512.0)/512;
		x=a;
		if(x*x+y*y>4)break;
	}
	return 128-log(k)*23;
}




//
void main()
{
	//before
	int x,y;
	int r,g,b;
	initwindow();

	//picture
	for(y=0;y<1024;y++)
	{
		for(x=0;x<1024;x++)
		{
			r=RED(x,y)&0xff;
			g=GREEN(x,y)&0xff;
			b=BLUE(x,y)&0xff;
			palette[y*1024+x]=(b)+(g<<8)+(r<<16);
		}
	}

	//forever
	QWORD type=0;
	QWORD key=0;
	while(1)
	{
		//1.先在内存里画画，然后一次性写到窗口内
		writewindow(0x04000400,palette);

		//2.等事件，是退出消息就退出
		uievent(&type,&key);
		if( type==0 )break;
	}

	//after
	killwindow();
}