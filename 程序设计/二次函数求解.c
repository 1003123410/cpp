#include<stdio.h>
#include<math.h>

void fun(void)
{
    START:
    printf("����������Ķ��η��̵�ϵ��a��b��c(�ֱ�Ϊ���Σ�һ�κͳ�����ϵ��)��");
    double a,b,c;
    scanf("%lf%lf%lf",&a,&b,&c);
    if(a==0)
    {
        if(b==0)
        {
            if(c==0)
            {
                printf("���̵Ľ�Ϊ������ֵ��\n");
            }
            else
            {
                printf("����������Ϊ��ʽ�����ܳ�����������������롣\n");
                goto START;
            }
        }
        else
        {
            printf("���̵Ľ�Ϊ��%lf\n",-c/b);
        }
    }
    else
    {
        if((b*b-4*a*c)<0)printf("�÷����޽⡣\n");
        else if((b*b-4*a*c)==0)printf("���̽���һ���⣬���Ϊ��%lf\n",-b/(2*a));
        else printf("�����������⣬�ֱ�Ϊ %lf �� %lf \n",-((b+sqrt(b*b-4*a*c))/(2*a)),(-b+sqrt(b*b-4*a*c))/(2*a));
    }
}

int main()
{
    while(1)
    {
        fun();
    }
    return 0;
}
