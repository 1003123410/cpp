#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
/*��Ŀ��һ��������������100����һ����ȫƽ�������ټ���168����һ����ȫƽ���������ʸ����Ƕ��٣�*/
int main(int agc,char **agv)
{
    for(int i=0;i<100000;++i)
    {
        if(((int)sqrt(i+268))*((int)sqrt(i+268))==(i+268)&&((int)sqrt(i+100))*((int)sqrt(i+100))==(i+100))cout<<i<<"  "<<i+100<<"  "<<i+268<<"  "<<sqrt(i+100)<<"  "<<sqrt(i+268)<<endl;
    }
    return 0;
}
