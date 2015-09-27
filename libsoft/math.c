#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long long
int decstring2data(BYTE* source,QWORD* data);




static double stack2[20];
static int count2=0;




static void initstack2()
{
	count2=20;
}
static int push(double data)
{
	//say("push %llf\n",data);

	//满栈
	if(count2==0)return 0;

	//count2-1(rsp-8)，然后放下这个数字
	count2--;
	stack2[count2]=data;
	return 1;
}
static int pop(double* dest)
{
	//空栈
	if(count2>=20)return 0;

	//拿出当前数字，然后count2+1(rsp+8)
	dest[0]=stack2[count2];
	count2++;

	//say("pop %llf\n",dest[0]);
	return 1;
}







double cosine(double x)
{
    double ret=0,item=1.0,temp;
    int n=0,i,sign=1;
    if(x>2*3.1415||x<-2*3.1415){x-=((int)(x/(2*3.1415)))*(2*3.1415);}

    do{
        temp=item;
        for(i=1;i<=2*n;i++)temp/=i;
        ret+=sign*temp;
        item*=x*x;
        sign *=-1;
        n++;
      }while (temp>1e-10);
return ret;
}




double sine(double x)
{
    int m = 1,i;
    double temp,ret = 0.0;
    if(x>2*3.1415||x<-2*3.1415){x-=((int)(x/(2*3.1415)))*(2*3.1415);}

    do{
        i=0;
        if (m%2 == 0){temp= -1.0;}
        else{temp= 1.0;}
        for(i=1;i<=2*m-1;i++){temp = temp * x/i;}
        ret+= temp;
        m++;
    }while (temp<-.0000005||temp>0.0000005);
return ret;
}




double squareroot(double x)
{
    double temp,ret;
    if(x<0){return 0;}

    temp=0.5*(1+x);
    ret=0.5*(temp+x/temp);
    while(1)
    {
	if( (ret-temp) >= 1e-10 ) break;
	if( (temp-ret) >= 1e-10 ) break;
        temp=ret;
        ret=0.5*(temp+x/temp);
    }
return ret;
}




double calculator(char* postfix,QWORD x,QWORD y)
{
	int source=0;
	int count;
	QWORD data;
	double first,second,temp;

	initstack2();

	while(1)
	{
		if(source>=128)break;
		if(postfix[source]<0x20)break;
		//say("%c@%d\n",postfix[source],source);

		//数字
		if( ( postfix[source] >= '0' ) && ( postfix[source] <= '9' ) )
		{
			//先拿整数部分
			count = decstring2data( postfix+source , &data );
			source += count;
			first = (double)data;

			//检查有没有小数部分有就加上
			if(postfix[source] == '.')
			{
				//say(".@%d\n",source);

				source++;
				count=decstring2data( postfix+source , &data );

				if(count>0)
				{
					source += count;
					temp = (double)data;

					while(1)
					{
						temp /= 10.00;

						count--;
						if(count==0)break;
					}

					//加上小数
					first+=temp;
				}

			}

			push(first);
		}//是数字
		else 
		{
		switch(postfix[source])
		{
			case '+':
			{
				pop(&second);
				pop(&first);			//注意，栈，先进后出
				temp = first + second;
				push(temp);

				//say("%llf + %llf = %llf\n",first,second,first+second);
				break;
			}
			case '-':
			{
				pop(&second);
				pop(&first);
				temp=first-second;
				push(temp);
				break;
			}
			case '*':
			{
				pop(&second);
				pop(&first);
				temp=first*second;
				push(temp);
				break;
			}
			case '/':
			{
				pop(&second);
				pop(&first);
				temp=first/second;
				push(temp);
				break;
			}
			case '^': 	//指数		x^y
			{
				pop(&second);
				pop(&first);

				temp=1.00;
				data=(QWORD)(second+0.000001);
				if(data!=0) while(1)
				{
					temp*=first;
					data--;
					if(data==0)break;
				}
				push(temp);
				break;
			}
			case '%': 	//取余		x%y
			{
				break;
			}
			case '!': 	//阶乘		x!
			{
				break;
			}
			case 'l':		//对数		xlogy
			{
				break;
			}
			case 's':
			{
				//根号		ysqrty
				//正弦		sinx
				break;
			}
			case 'c': 	//余弦		cosx
			{
				break;
			}
			case 't': 	//正切		tanx
			{
				break;
			}
		}//switch结束
		source++;		//下一个
		}//else结束

	}//while结束

	pop(&temp);
	return temp;
}

