#include<iostream>
using namespace std;
//��3����������С����˳������Ҫ��ʹ�ñ��������á�
void sort(int &a,int &b);

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    sort(a,b);
    sort(a,c);
    sort(b,c);
    cout<<a<<" "<<b<<" "<<c<<endl;
    return 0;
}

void sort(int &a,int &b)
{
    int t=a;
    if(b<a)
    {
        a=b;
        b=t;
    }
}
