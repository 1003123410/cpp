#include<iostream>
using namespace std;
class rectangle
{
public:
    rectangle(){length=0;width=0;height=0;cout<<"constructor!"<<endl;}
    ~rectangle(){cout<<"destructor!"<<endl;}
    void set();
    int volume();
private:
    int length,width,height;
};
void rectangle::set()
{
    int l,w,h;
    cout<<"�����볤���εĳ���ߣ�";
    cin>>l>>w>>h;
    length=l;
    width=w;
    height=h;
}
int rectangle::volume()
{
    return length*width*height;
}
int main()
{
    rectangle rec[3];
    for(int i=0;i<3;++i)
    {
        rec[i].set();
        cout<<"������"<<i+1<<"�����Ϊ��"<<rec[i].volume()<<endl;
    }
    return 0;
}
