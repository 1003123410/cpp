#include<stdio.h>

void huiduzhifang(void)
{
    FILE *p;
    int a,i=0,j=0,col=0,row=0,b[16]={0};
    p=fopen("imagin.in","r");
    if(p!=NULL)
    {
        fscanf(p,"%d%d",&col,&row);
        for(;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                fscanf(p,"%d",&a);
                if(a>=0&&a<16)
                {
                    b[a]++;
                }
                else
                {
                    printf("�ļ��г��ֲ��ڻҶ�ֵ�ڵ��������飡\n");
                    goto END;
                }
            }
        }
        fclose(p);
        printf("�Ҷ�ֵͳ�ƽ��Ϊ��\n");
        int max=b[0],j;
        for(i=1;i<16;i++)
        {
            if(b[i]>max)
            {
                max=b[i];
            }
        }
        for(j=0;j<max;j++)
        {
            for(i=0;i<16;i++)
            {
                if(b[i]>=max-j)
                {
                    if(i>9)printf(" %c  ",2);
                    else printf(" %c ",2);
                }
                else
                {
                    if(i>9)printf("    ");
                    else printf("   ");
                }
            }
            putchar('\n');
        }
        for(i=0;i<16;i++)
        {
            printf(" %d ",i);
        }
        putchar('\n');
        putchar('\n');
        for(i=0;i<16;i++)
        {
            if(i>9)printf(" %d  ",b[i]);
            else printf(" %d ",b[i]);
        }
        putchar('\n');
        putchar('\n');
        END:;
    }
}

int main()
{
    huiduzhifang();
    getchar();
    return 0;
}
