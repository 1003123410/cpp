#include<stdio.h>

int jiaogu(int n)
{
    if(n%2==0)return n/2;
    else return n*3+1;
}

int main()
{
    int m,a,b=0;
    printf("�������������ޣ�");
    scanf("%d",&m);
    int i;
        for(i=1;i<=m;++i)
        {
            int sum;
            a=i;
            for(sum=1;;++sum)
            {
               if(a==1)break;
               else a=jiaogu(a);
            }
            b+=sum;
            printf("%d����ִ��%d��\n",i,sum);
        }
        printf("%d�ڵ�������ִ��%d��\n",m,b);
return 0;
}
