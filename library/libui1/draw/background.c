#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
void blackstring(int x,int y,char* str);
void line(QWORD,QWORD,QWORD);
void rectangle(QWORD,QWORD,QWORD);

QWORD readwindow(QWORD);
void writewindow();




static DWORD* screenbuf=0;
static int xsize=0;
static int ysize=0;
void initbackground(char* unusedaddr)
{
	//how
	QWORD temp=readwindow(0x657a6973);
	ysize=(temp>>16)&0xffff;
	xsize=temp&0xffff;
	if(xsize>1024)xsize=1024;
	if(ysize>1024)ysize=1024;

	//where
	screenbuf=(DWORD*)readwindow(0x6572656877);
}




void backgroundcolor(unsigned int color)
{
	int x;

	for(x=0;x<1024*768;x++)
	{
		screenbuf[x]=color;
	}
}




void background1()
{
	QWORD x,y;

	//用指定颜色清屏
	for(x=0;x<1024*ysize;x++)
	{
		screenbuf[x]=0xf0f0f0f0;
	}

	//上下
	for(y=0;y<16;y++)
	{
		DWORD color=0x40404040+(0x0b0b0b0b*y);

		//上，编译器会不会用rep stosd指令优化呢?
		DWORD* p=screenbuf+y*1024;
		for(x=y;x<1024-y;x++)p[x]=color;

		//下
		p=screenbuf+(ysize-1-y)*1024;
		for(x=y;x<1024-y;x++)p[x]=color;
	}
	//左右
	for(x=0;x<16;x++)
	{
		DWORD color=0x40404040+(0x0b0b0b0b*x);

		for(y=x;y<ysize-x;y++)
		{
			screenbuf[(y*1024)+x]=color;
			screenbuf[(y*1024)+xsize-1-x]=color;
		}
	}
}
