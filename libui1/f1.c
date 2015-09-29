#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
void die();

void hexadecimal(int x,int y,QWORD in);
void hexadecimal1234(int x,int y,QWORD in);
void string(int x,int y,char* str);
void anscii(int x,int y,char ch);
void blackanscii(int x,int y,char ch);
void point(int x,int y,DWORD color);
void background1();

int compare(char*,char*);
void data2hexstring(QWORD,char*);
void readmemory(QWORD rdi,QWORD rsi,QWORD rdx,QWORD rcx);

QWORD whereisworld();
QWORD screendata();
QWORD screenresolution();








//位置
static QWORD base;		//显示区基地址
static QWORD offset;
static BYTE* datahome;

//mainscreen
static QWORD screenaddr;
static int xsize;
static int ysize;
static int printmethod=0;

//flostarea
static int inputcount=0;
static BYTE haha[0x100];
	//[0,0x1f]:target,value
	//[0x20,0x3f]:base,value
	//[0x40,0x5f]:offset,value
	//[0x60,0x7f]:data,value




//in:想要哪儿
//out:请求的地方的内存地址
//作用:防止每动一下就读一次硬盘
static QWORD currentcache;
QWORD readornotread(QWORD wantaddr)
{
	//假如每次能显示0x1000(实际是0xa00)
	//想要[0,0x1000)：			确保[0,0x2000)			返回datahome+0
	//想要[0xfc0,0x1fc0)：		确保[0,0x2000)			返回datahome+0xfc0
	//想要[0x1000,0x2000)：		确保[0x1000,0x3000)		返回datahome+0x1000
	//想要[0x1040,0x2040)：		确保[0x1000,0x3000)		返回datahome+0x40
	//想要[0x1fc0,0x2fc0)：		确保[0x1000,0x3000)		返回datahome+0xfc0
	//想要[0x2000,0x3000)：		确保[0x2000,0x4000)		返回datahome+0
	//想要[0x2040,0x3040)：		确保[0x2000,0x4000)		返回datahome+0x40
	//想要[0x2fc0,0x3fc0)：		确保[0x2000,0x4000)		返回datahome+0xfc0
	//想要[0x3000,0x4000)：		确保[0x3000,0x5000)		返回datahome+0
	QWORD readwhere=wantaddr & 0xfffffffffffff000;
	if(readwhere!=currentcache)
	{
		readmemory((QWORD)datahome, readwhere/0x200, 0, 16);
		currentcache=readwhere;
	}

	return (QWORD)datahome+(wantaddr-readwhere);
}
void foreground()
{
	//一整页
	int x,y;
	int xsize,ysize,xshift;
	QWORD readwhere=readornotread(base);
	QWORD temp=screenresolution();

	ysize=( (temp>>16) & 0xffff ) >> 4;
	if(ysize>0x40)ysize=0x40;

	xsize=( temp & 0xffff ) >> 4;
	if(xsize>1024)xsize=0x40;

	xshift = xsize&0x3;
	xsize &= 0xfffc;

	//
	if(printmethod==0)			//hex
	{
		for(y=0;y<ysize;y++)
		{
			for(x=0;x<xsize;x+=4)
			{
				DWORD value=*(DWORD*)(readwhere+y*xsize+x);
				hexadecimal1234(2*x+xshift,y,value);
			}
		}
	}
	else if(printmethod==1)		//anscii
	{
		for(y=0;y<ysize;y++)
		{
			for(x=0;x<xsize;x+=4)
			{
				DWORD value=*(DWORD*)(readwhere+y*xsize+x);
				blackanscii(2*x+xshift,y,value&0xff);
				blackanscii(2*x+2+xshift,y,(value>>8)&0xff);
				blackanscii(2*x+4+xshift,y,(value>>16)&0xff);
				blackanscii(2*x+6+xshift,y,(value>>24)&0xff);
			}
		}
	}
}
void floatarea()
{
	int x,y;
	DWORD* screenbuf=(DWORD*)screendata();
	QWORD temp=screenresolution();
	int ysize=(temp>>16)&0xffff;
	int xsize=temp&0xffff;
	if(xsize>1024)xsize=1024;
	if(ysize>1024)ysize=1024;

	//byte框
	int thisx=(offset&0x3f)*16;
	int thisy=(offset%0xa00)/0x40*16;
	for(y=thisy;y<thisy+16;y++)
	{
		for(x=thisx;x<thisx+16;x++)
		{
			screenbuf[y*1024+x]=~screenbuf[y*1024+x];
		}
	}

	//256*128的详情框
	thisx+=16;
	if(thisx>768)thisx -= (256+16);
	thisy+=16;
	if(thisy>=640-128+16)thisy -= (128+16);

	for(y=thisy;y<thisy+128;y++)
	{
		for(x=thisx;x<thisx+256;x++)
		{
			screenbuf[y*1024+x]=0xffff;
		}
	}

	//
	data2hexstring(0x33333333,haha+0x10);
	data2hexstring(base,haha+0x30);
	data2hexstring(offset,haha+0x50);
	data2hexstring(0,haha+0x70);

	//target,base,offset,data
	int chx=thisx/8;
	int chy=thisy/16;
	for(y=0;y<8;y++)
	{
		for(x=0;x<32;x++)
		{
			blackanscii(chx+x,chy+y,haha[(y*32) + x]);
		}
	}
}








void f1show()
{
	//背景
	background1();

	//
	foreground();

	//
	floatarea();
}
void f1message(QWORD type,QWORD key)
{
	if(type==0x64626b)			//kbd
	{
		if(key==0x25)			//left	0x4b
		{
			if( (offset&0x3f) > 0 )offset--;
			else
			{
				if(base>=0x800)base-=0x800;
			}
		}
		else if(key==0x27)		//right	0x4d
		{
			if( (offset&0x3f) < 0x3f)offset++;
			else
			{
				base+=0x800;
			}
		}
		else if(key==0x26)		//up	0x4b
		{
			if(offset>=0x40)offset-=0x40;
			else
			{
				if(base>=0x40)base-=0x40;
			}
		}
		else if(key==0x28)		//down	0x4d
		{
			if(offset<0xa00-0x40)offset+=0x40;
			else base+=0x40;
		}
	}
	else if(type==0x72616863)		//char
	{
		if(key==9)					//tab
		{
			printmethod=(printmethod+1)%2;
		}
		else if(key==0x8)			//backspace
		{
			if(inputcount!=0)inputcount--;
			haha[0x80+inputcount]=0;
		}
		else if(key==0xd)			//enter
		{
			if(compare( haha+0x80 , "exit" ) == 0)
			{
				die();
				return;
			}
			else if(compare( haha+0x80 , "addr" ) == 0)
			{
			}

		}
		else
		{
			if(inputcount<128)
			{
				haha[0x80+inputcount]=key;
				inputcount++;
			}
		}
	}
	else if(type==0x7466656c)		//鼠标
	{
		int x=key&0xffff;
		int y=(key>>16)&0xffff;
		offset=(y/16*0x40)+(x/16);

		//浮动框以外的
		//px=x/(1024/0x40);
		//py=y/(640/40);
	}
	else if(type==0x6c65656877)		//滚轮
	{
		if(key<0xff0000)
		{
			if(base>=0x40)base-=0x40;
		}
		else if(key>0xff0000)
		{
			base+=0x40;
		}
	}
}








void f1init(QWORD world)
{
	int i;

	//
	datahome=(BYTE*)world+0x300000;
	for(i=0;i<0x2000;i++)datahome[i]=0;

	//浮动框
	for(i=0;i<0x100;i++)haha[i]=0;
	*(QWORD*)haha=0x3a746567726174;
	*(QWORD*)(haha+0x20)=0x3a65736162;
	*(QWORD*)(haha+0x40)=0x3a74657366666f;
	*(QWORD*)(haha+0x60)=0x3a61746164;

	//文件内部偏移
	base=0;
	offset=0;
	currentcache=0xffffffff;
}