#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<string.h>
/*�������룺 ��ȡһ�������ٰ�������������������������ӣ�
Ȼ�����������ٵ���������ԭ������ӣ�
�ظ��˹��̣�һ���ܻ��һ��������*/
using namespace std;
int panduan(char a[])
{
    int n=strlen(a),i=0;
    for(;i<=n/2;++i)
    {
        if(a[i]!=a[n-i-1])return 0;
    }
    if(n/2<i)return 1;
    else return 0;
}//judge whther it's a huiwen
int he(char a[])
{
    int n=strlen(a);
    char s[30]={0};
    for(int i=0;i<n;++i)s[i]=a[n-i-1];
	printf("%s+%s=%d\n",a,s,atoi(a)+atoi(s));
    return atoi(a)+atoi(s);
}//conclude the sum of a and it's shadow
int caixiang(char a[])
{
    if(panduan(a))
	{
		printf("%s�ǻ�����\n",a);
		return 1;
	}
    else
	{
		char s[30]={0};
		itoa(he(a),s,10);
		caixiang(s);
	}
}//digui
int main(int agc,char **agv)
{
    while(1)
    {
        int a;
        printf("please enter test number!\n");
        scanf("%d",&a);
        char s[30]={0};
        itoa(a,s,10);
        caixiang(s);
    }
    return 0;
}
