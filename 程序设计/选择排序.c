#include<stdio.h>
#define B 100

int main()
{
    int i,b=30,a[B]={0};
    printf("������%d���������ݣ�",B);
    for(i=0;i<B;++i)scanf("%d",&a[i]);
    int j,k,t;
    for(i=0;i<B-1;i++)
    {
        for(j=i,k=i+1;k<B;++k)if(a[j]>a[k])j=k;
        if(j!=i)
        {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    for(i=0;i<B;++i)printf("%d    ",a[i]);
return 0;
}
