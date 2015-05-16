#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long

static QWORD dirbuffer;

static int complex=0;		//主体华丽程度




void logic0init(QWORD in)
{
	dirbuffer=in;
}
void logic0mouse()
{
	
}
void logic0kbd()
{
	
}
void logic0background()
{
	QWORD x,y;
	unsigned int color,i=0;
	//清屏
	for(y=0;y<640;y++)
	{
		for(x=0;x<1024;x++)
		{
			point(x,y,0xcccccccc);
		}
	}
	//框
	for(x=0;x<1024;x++)
	{
		point(x,0,0xcc00);
		point(x,639,0xcc00);
	}
	for(y=0;y<640;y++)
	{
		point(0,y,0xcc00);
		point(1023,y,0xcc00);
	}
	/*
	for(y=640-32;y<640-16;y++)
	{
		color=0xcccccccc-0x11110011*(i*3/4);		//绿
		for(x=1024-32+i;x<1024;x++)
		{
			point(x,y,color);
		}
		i++;
	}
	for(x=16;x<32;x++)
	{
		point(1024-x,640-x,0xcc00);
	}
	*/
	//左上
	for(y=0;y<32;y++)
		for(x=0;x<32-y;x++)
			point(x,y,0);
	//右上
	for(y=0;y<32;y++)
		for(x=1024-32+y;x<1024;x++)
			point(x,y,0);
	//左下
	for(x=0;x<32;x++)
		for(y=640-32+x;y<640;y++)
			point(x,y,0);
	//右下
	//for(y=640-32;y<640;y++)
	//	for(x=1024-32;x<1024;x++)
	//		point(x,y,0xff00);
	/*
	for(x=256;x<768;x++)
	{
		for(y=0;y<16;y++)
		{
			point(x,y,0xfedcba98);
		}
		for(y=640-16;y<640;y++)
		{
			point(x,y,0xfedcba98);
		}
	}
	for(y=128;y<640-128;y++)
	{
		for(x=0;x<16;x++)
		{
			point(x,y,0x01234567);
		}
		for(x=1024-16;x<1024;x++)
		{
			point(x,y,0x01234567);
		}
	}
	*/
}




void printfile0()
{
	int x,y;
	char* p;

//三.每个分区里面的文件和文件夹
	p=(char*)dirbuffer;
	string(32,0,"name");
	string(48,0,"id");
	string(64,0,"type");
	string(80,0,"size");
	for(y=0;y<36;y++)
	{
		if(*(DWORD*)(p+0x40*y) == 0) break;
		string(32,y+1,p+0x40*y);
		hexadecimal(48,y+1,*(QWORD*)(p+0x40*y+0x10));
		hexadecimal(64,y+1,*(QWORD*)(p+0x40*y+0x20));
		hexadecimal(80,y+1,*(QWORD*)(p+0x40*y+0x30));
	}
}
void printfile1()
{
	
}
void printfile2()
{
	
}
void logic0()
{
	logic0background();

	//-------------------
	if(complex==0)
	{
		printfile0();
	}
	else if(complex==1)
	{
		printfile1();
	}
	else
	{
		printfile2();
	}
}