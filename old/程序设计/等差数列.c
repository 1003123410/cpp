#include<stdio.h>

int main()
{
    int n,i;
    printf("����������������");
    scanf("%d",&n);
    if(n<=10)
    {
        for(i=0;i<n;i++)
        {
            printf("����������������");
            int j,k,a[100]={0},max,m;
            scanf("%d",&m);
            if(m<=100)
            {
                for(j=0;j<m;j++)
                {
                    scanf("%d",&a[j]);
                    if(a[j]<-32768||a[j]>32767)
                    {
                        break;
                        printf("���ݷ�Χ����");
                    }
                }
                for(j=0;j<m-1;j++)
                {
                    for(k=j;k<m;k++)
                    {
                        if(a[k]>a[j])
                        {
                            max=a[k];
                            a[k]=a[j];
                            a[j]=max;
                        }
                    }
                }
                for(j=0;j<m;j++)
                {
                    printf("%d  ",a[j]);
                }
                printf("\n");
                for(j=0;j<m-1;j++)
                {
                    if(a[j]-a[j+1]!=a[0]-a[1])break;
                }
                if(j<m-1)printf("no\n");
                else printf("%d\n",a[0]-a[1]);
            }
            else printf("�������ݹ��࣡\n");
        }
    }
    else printf("����������������!");
    return 0;
}
