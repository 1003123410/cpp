#include<stdio.h>

int main()
{
	int x;
	scanf("%d",&x);
	if(x>=0&&x<=99999)
	{
		int a=x/10000;
		int b=(x-10000*a)/1000;
		int c=(x-10000*a-1000*b)/100;
		int d=(x-10000*a-1000*b-100*c)/10;
		int e=x-10000*a-1000*b-100*c-10*d;
		int y=a+10*b+100*c+1000*d+10000*e;                   //��ȡ��λ��
		printf("%d\n",y);
		printf("%d  %d  %d  %d  %d\n",a,b,c,d,e);
		if(a==0)                                  
		{
			if(b==0)
			{
				if(c==0)
				{
					if(d==0)
					{
					printf("һλ��");
					}
					else
						printf("��λ��");
				}
				else
					printf("��λ��");
			}
			else
				printf("��λ��");
		}
		else
		printf("��λ��");                            //λ���ж�
	}	
return 0;
}