#include<stdio.h>
#include<stdio.h>

int pan(double a,double b,double c)
{
    if((a+b)>c&&(b+c)>a&&(a+c)>b)return 1;
    else
    {
        printf("������󣬲��ܹ��������Σ�\n");
        return 0;
    }
}

void rec(void)
{
    double a,b,c;
    printf("�����������ε������ߣ�");
    scanf("%lf%lf%lf",&a,&b,&c);
    double s=(a+b+c)/2;
    if(pan(a,b,c))
    {
        printf("��%.2f,%.2f,%.2fΪ�ߵ����������Ϊ%lf��\n",a,b,c,sqrt(s*(s-a)*(s-b)*(s-c)));
    }
}

int main()
{
    while(1)rec();
    return 0;
}
