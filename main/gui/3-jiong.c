#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
void jiong()
{
	int x,y;
	background3();

	//外面的口
	for(y=64;y<640-64;y++)
	{
		for(x=256;x<768;x++)
		{
			point(x,y,0xffff00);
		}
	}
	for(y=64;y<640-64;y++)
	{
		point(256,y,0);
		point(767,y,0);
	}
	for(x=256;x<768;x++)
	{
		point(x,64,0);
		point(x,639-64,0);
	}

	//撇捺
	for(y=0;y<128;y++)
	{
		point(512-64-y,y+128,0);
		point(512+64+y,y+128,0);
	}

	//里面的口
	for(y=320;y<512;y++)
	{
		for(x=256+128;x<768-128;x++)
		{
			point(x,y,0xffff);
		}
	}
	for(y=320;y<512;y++)
	{
		point(256+128,y,0);
		point(767-128,y,0);
	}
	for(x=256+128;x<768-128;x++)
	{
		point(x,320,0);
		point(x,512,0);
	}

	//
	string(0x38,16,"every where to live");
	string(0x38,24,"only here to die");
}
void overviewmessage(DWORD type,DWORD key)
{
	if(type==2)
	{
		int x=key&0xffff;
		int y=(key>>16)&0xffff;
		if(x>256+128)
		{
			if(x<768-128)
			{
				if(y>320)
				{
					if(y<320+128)
					{
						die();
						return;
					}
				}
			}
		}
	}
}