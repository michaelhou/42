//martin buttner
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
//
void initwindow();
void killwindow();
void writewindow(QWORD size,void* addr);
void uievent(QWORD* type,QWORD* key);
//
void channel_b(QWORD size,BYTE* addr);
void channel_g(QWORD size,BYTE* addr);
void channel_r(QWORD size,BYTE* addr);
void channel_rg(QWORD size,BYTE* addr);
void channel_rb(QWORD size,BYTE* addr);
void channel_gb(QWORD size,BYTE* addr);




//
static DWORD palette[1024*1024];
static DWORD final[1024*1024];




//
#define _sq(x) ((x)*(x))
#define r(n)(rand()%n)
unsigned char RED(int i,int j)
{
	static char c[1024][1024];
	return!c[i][j]?c[i][j]=!r(999)?r(256):RED((i+r(2))%1024,(j+r(2))%1024):c[i][j];
}
unsigned char GREEN(int i,int j)
{
	static char c[1024][1024];
	return!c[i][j]?c[i][j]=!r(999)?r(256):GREEN((i+r(2))%1024,(j+r(2))%1024):c[i][j];
}
unsigned char BLUE(int i,int j)
{
	static char c[1024][1024];
	return!c[i][j]?c[i][j]=!r(999)?r(256):BLUE((i+r(2))%1024,(j+r(2))%1024):c[i][j];
}




//
void processmessage(QWORD type,QWORD key)
{
	
	int i;
	printf("%llx,%llx\n",type,key);

	if(type==0x72616863)             //'char'
	{
		//channel
		for(i=0;i<1024*1024;i++)
		{
			final[i]=palette[i];
		}

		//0
		if(key==0x30)
		{
		}
		//1
		else if(key==0x31)
		{
			channel_b(0x04000400,(BYTE*)final);
		}
		//2
		else if(key==0x32)
		{
			channel_g(0x04000400,(BYTE*)final);
		}
		//3
		else if(key==0x33)
		{
			channel_r(0x04000400,(BYTE*)final);
		}
		//4
		else if(key==0x34)
		{
			channel_rg(0x04000400,(BYTE*)final);
		}
		//5
		else if(key==0x35)
		{
			channel_rb(0x04000400,(BYTE*)final);
		}
		//6
		else if(key==0x36)
		{
			channel_gb(0x04000400,(BYTE*)final);
		}
	}
}
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
	processmessage(0x72616863,0x30);

	//forever
	QWORD type=0;
	QWORD key=0;
	while(1)
	{
		//1.先在内存里画画，然后一次性写到窗口内
		writewindow(0x04000400,final);

		//2.等事件，是退出消息就退出
		uievent(&type,&key);
		if( type==0 )break;
		if( (type==0x64626b)&&(key==0x1b))break;


		//3.处理事件
		processmessage(type,key);
	}

	//after
	killwindow();
}
