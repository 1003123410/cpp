#include<stdio.h>

int jiaogu(int n)
{
    if(n%2==0)return n/2;
    else return n*3+1;
}

int main()
{
    int m,a;
    printf("����������������");
    scanf("%d",&m);
    if(m<100&&m>0)
    {
        for(a=1;a<=m;++a)
        {
            int n,sum;
            printf("�������������ݣ�");
            scanf("%d",&n);
            for(sum=1;;++sum)
            {
               if(n==1)break;
               else n=jiaogu(n);
            }
            printf("��ִ��%d��\n",sum);
        }
    }
return 0;
}
