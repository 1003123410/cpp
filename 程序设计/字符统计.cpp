#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

void zifu(void)
{
    ifstream infile;
    cout<<"�������ļ�����";
    char a[20]={0};
    cin.getline(a,20);
    infile.open(a);
    if(infile.is_open())
    {
        int count=0,space=0,num=0,letter=0,other=0;
        char c;
        while(!infile.eof())
        {
            infile.get(c);
            if(c>='0'&&c<='9')++num;
            else if(c<='z'&&c>='a'||c>='A'&&c<='Z')++letter;
            else if(c==' ')++space;
            else ++other;
            ++count;
        }
        cout<<"�ļ�"<<a<<"�й���"<<count<<"���ַ�."<<endl;
        cout<<"����:"<<num<<"��\n"<<"��ĸ��"<<letter<<"��\n"<<"�ո�:"<<space<<"��\n"<<"�����ַ�:"<<other<<"��"<<endl;
    }
    else cout<<"�ļ���ʧ�ܣ�";
    infile.close();
}

int main()
{
    zifu();
    return 0;
}
