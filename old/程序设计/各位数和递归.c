#include<stdio.h>

int gewei(int n)
{
    return n<10?n:n%10+gewei(n/10);
}

int main()
{
    int n;
    printf("������Ҫ���λ���͵���n:");
    scanf("%d",&n);
    printf("%d�ĸ�λ����Ϊ%d\n",n,gewei(n));
return 0;
}
