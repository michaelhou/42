#include<stdio.h>
extern char* _binary_unicode_unicode_start;
void printmemory(char*,int);




void printunicode(char* p)
{
	int j,k;
	unsigned short temp;
	for(j=0;j<0x10;j++)
	{
		temp  = p[j*2] << 8;
		temp += p[(j*2)+1];

		for(k=0;k<0x10;k++)
		{
			if( (temp&0x8000) == 0x8000 )printf("* ");
			else printf("  ");

			temp=temp<<1;
		}

		printf("\n");
	}
}
void main()
{
	int i;
	unsigned char* p=(char*)&_binary_unicode_unicode_start;
	//printmemory(p,0x1000);

	printunicode(p+(0x6709*0x20));		//有
	printunicode(p+(0x6ca1*0x20));		//没
}