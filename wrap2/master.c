﻿#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long


//[buffer0][buffer1][buffer2]......[buffer15]
static QWORD realworld;
	//1个硬盘(或者虚拟磁盘文件) = 很多个分区(ext/fat/hfs/ntfs)
	static QWORD buffer0;
	//1个分区(或者某格式的文件) = 很多个区域(头/索引区/数据区/尾)
	static QWORD buffer1;
	//1个索引(mft/inode/btnode) = 很多信息(名字，唯一id，时间，扇区位置等)
	static QWORD buffer2;
	//[+0x30000,+0xfffff]:未用
	static QWORD buffer3;

//[0m,1m)[1m,2m)[2m,3m)[3m,4m)
static QWORD logicworld;
	//往这儿读，只临时用一下（当心别人也用）
	static QWORD readbuffer;
	//名，id，种类，大小
	static QWORD dirbuffer;
	//缓存几千几万个fat/mft/btnode/inode
	static QWORD fsbuffer;
	//[0x300000,0x3fffff]:未用

int (*explain)(QWORD id);		//((int (*)(QWORD))(explain))(value);
int (*cd)(QWORD id);		//((int (*)(QWORD))(cd))(arg1);
int (*load)(QWORD id,QWORD part);		//((int (*)(QWORD,QWORD))(load))(arg1,temp*0x100000);










void hello()
{
	readdisk(readbuffer,0,0,64);
	if( *(WORD*)(readbuffer+0x1fe) == 0xaa55 )
	{
		say("disk or image\n");
		explainparttable(readbuffer,buffer0);
	}
}


int searchthis(char* name,QWORD* addr)
{
	//printmemory(dirbuffer,0x1000);
	//say("i am in\n");

	QWORD temp=dirbuffer;
	for(;temp<dirbuffer+0x1000;temp+=0x40)
	{
		//say("%llx,%llx\n",*(QWORD*)name,*(QWORD*)temp);
		if( compare( name , (char*)temp ) == 0 )
		{
			*addr=temp;
			printmemory(temp,0x40);
			return 0;
		}
	}

	say("file not found\n");
	return -1;
}


int mount(QWORD in)
{
	//搞谁，是啥
	QWORD this=buffer0+in*0x40;
	QWORD type=*(QWORD*)(this+0x10);

	//不同种类的分区，不同的处理
	if(type == 0x747865)		//ext
	{
		mountext(this,buffer1);
	}
	else if(type == 0x746166)		//fat
	{
		mountfat(this,buffer1);
	}
	else if(type == 0x736668)		//hfs
	{
		mounthfs(this,buffer1);
	}
	else if(type == 0x7366746e)		//ntfs
	{
		mountntfs(this,buffer1);
	}

	//给函数指针赋值
	explain=(void*)( *(QWORD*)(this+0x20) );
	cd=(void*)( *(QWORD*)(this+0x28) );
	load=(void*)( *(QWORD*)(this+0x30) );

	printmemory(this,0x40);
}


void command(char* buffer)
{
//-----------------1.把收到的命令检查并翻译一遍-------------------
	BYTE* arg0;
	BYTE* arg1;
	buf2arg(buffer,&arg0,&arg1);
	//say("%llx,%llx\n",arg0,arg1);
	if(arg0==0)return;




//----------------------2.实际的活都找专人来干-----------------------------
	if(compare( arg0 , "help" ) == 0)
	{
		say("disk ?                  (choose a disk)\n");
		say("mount ?                 (choose a partition)\n");
		say("explain ?               (explain inode/cluster/cnid/mft)\n");
		say("cd dirname              (change directory)\n");
		say("load filename           (load this file)\n");
	}
	else if(compare( arg0 , "disk" ) == 0)
	{
		disk(arg1);			//第几个功能，数值或者地址
		hello();
	}
	else if(compare( arg0 , "mount" ) == 0)
	{
		if(arg1==0)
		{
			hello();
			return;
		}
		else
		{
			QWORD value;
			anscii2hex(arg1,&value);

			mount(value);		//第几个功能，字符串地址
		}
	}
	else if(compare( arg0 , "explain" ) == 0)
	{
		QWORD value;
		anscii2hex(arg1,&value);

		say("explainer@%llx\n",explain);
		explain(value);
	}
	else if(compare( arg0 , "cd" ) == 0)
	{
		QWORD addr;
		if( searchthis(arg1,&addr) < 0 )return;		//没找到

		//change directory
		cd( *(QWORD*)(addr+0x10) );
	}
	else if(compare( arg0 , "load" ) == 0)
	{
		//寻找这个文件名，得到id，type，size
		QWORD addr;
		if( searchthis(arg1,&addr) < 0 )return;
		QWORD id=*(QWORD*)(addr+0x10);
		QWORD type=*(QWORD*)(addr+0x20);
		QWORD size=*(QWORD*)(addr+0x30);
		if(size>0x100000)say("warning:large file\n");


		QWORD temp=0;
		//1m,1m,1m的整块搞
		for(;temp<( size&0xfffffff00000 );temp+=0x100000)
		{
			load(id,temp);
			mem2file(readbuffer,arg1,temp,0x100000);		//mem地址，file名字，文件内偏移，写入多少字节
		}
		//最后的零头(要是size=1m的整数倍，就没有零头)
		if(temp<size)
		{
			load(id,temp);
			mem2file(readbuffer,arg1,temp,size%0x100000);		//mem地址，file名字，文件内偏移，写入多少字节
		}
	}
	else if(compare( arg0 , "ls" ) == 0)
	{
		say("name                special id          type                size\n");
		QWORD addr=dirbuffer;
		for(;addr<dirbuffer+0x1000;addr+=0x40)
		{
			if(*(QWORD*)addr==0)break;
			say("%-16.16s    %-16llx    %-16llx    %-16llx\n",
			(char*)addr,*(QWORD*)(addr+0x10),*(QWORD*)(addr+0x20),*(QWORD*)(addr+0x30));
		}
		say("\n");
	}
	else
	{
		say("what?\n");
	}
}




void initmaster()
{
	//现实世界和逻辑世界在哪里
	whereisrealworld(&realworld);
	buffer0=realworld;
	buffer1=realworld+0x10000;
	buffer2=realworld+0x20000;
	buffer3=realworld+0x30000;

	whereislogicworld(&logicworld);
	readbuffer=logicworld;
	dirbuffer=logicworld+0x100000;
	fsbuffer=logicworld+0x200000;

	//你是个什么玩意喂(--!)
	hello();
}