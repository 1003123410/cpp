#include<stdio.h>
#include <string.h>

int main()
{
    int b,c;
    printf("����������������");
    scanf("%d",&b);
    printf("\n");
    for(c=0;c<b;++c)
    {
        int i,a[100]={0};
        printf("���������ͣ�����1�����������ͣ�����2�����ַ���");
        scanf("%d",&i);
        printf("\n");
        if(i==1)
        {
            int m,j=0,k,d;
            printf("���������֣�");                 //����
            scanf("%d",&m);
            d=m;
            while(m>0)
            {
                a[j]=m%10;
                m/=10;
                j++;
            }
            for(k=0;k<j;k++)
            {
                if(a[k]!=a[j-k-1])
                {
                    break;
                }
            }
            if(k>=j/2)printf("����%d�ǻ�����\n",d);
            else printf("����%d���ǻ�����\n",d);
        }
        if(i==2)
        {
            printf("�������ַ�����");
            char d[100]={0},e[100]={0};
            scanf("%s",&d);
            int j,k=strlen(d);
            putchar('\n');
            for(j=0;j<k;j++)
            {
                e[j]=d[k-j-1];
            }
            if(strcmp(e,d)==0)printf("�ַ���%s�ǻ�����\n",d);
            else printf("�ַ���%s���ǻ�����\n",d);
        }
    }
    return 0;
}
