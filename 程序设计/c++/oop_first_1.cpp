#include<iostream>
using namespace std;
//��2������3���������е���������ô���Ĭ�ϲ����ĺ���ʵ�֡�
int max(int a,int b,int c=0);

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    if(a>0&&b>0&&c>0)cout<<max(a,b,c)<<endl<<max(a,b)<<endl;
    return 0;
}

int max(int a,int b,int c)
{
    if(b>a)a=b;
    if(c>a)a=c;
    return a;
}
