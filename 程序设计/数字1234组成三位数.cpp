#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
/*��Ŀ����1��2��3��4�����֣�
����ɶ��ٸ�������ͬ�����ظ����ֵ���λ����
���Ƕ��٣�*/
int main(int agc,char **agv)
{
    int sum=0;
    for(int i=1;i<5;++i)
    {
        for(int j=1;j<5;++j)
        {
            for(int k=1;k<5;++k)
            {
                if(i!=j&&j!=k&&k!=i)
                {
                    cout<<i<<j<<k<<endl;//����ѭ��������������������ѡ���
                    ++sum;
                }
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}
