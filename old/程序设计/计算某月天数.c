#include<stdio.h>

int leapyear(int year)
{
    if(year%4==0&&year%100!=0||year%400==0)return 1;
    else return 0;
}

int main()
{
    int n,i;
    printf("����������������");
    scanf("%d",&n);
    if(n<100)
    {
        for(i=1;i<=n;++i)
        {
            int a,b;
            printf("������Ҫ��ѯ����ݺ��·ݣ�");
            scanf("%d %d",&a,&b);
            if(b==1||b==3||b==5||b==7||b==8||b==10||b==12)printf("%d��%d�µ�����Ϊ31��\n",a,b);
            if(b==4||b==6||b==9||b==11)printf("%d��%d�µ�����Ϊ30��\n",a,b);
            else if(b==2)
            {
                if(leapyear(a))printf("%d��%d������Ϊ28��\n",a,b);
                else printf("%d��%d������Ϊ29��\n",a,b);
            }
        }
    }
return 0;
}
