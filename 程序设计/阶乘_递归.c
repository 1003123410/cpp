#include<stdio.h>

int jiecheng(int i)
{
    if(i==1)return 1;
    else return jiecheng(i-1)*i;
}

int main()
{
    int i;
    scanf("%d",&i);
    printf("%d�Ľ׳���%d",i,jiecheng(i));
    return 0;
}
