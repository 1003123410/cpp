#include<stdio.h>

void shudu(void)
{
    int i,j,flag,a[9][9]={0};
    FILE *p;
    char s[20]={0};
    printf("�����������ļ�����");
    scanf("%s",s);
    p=fopen(s,"r");
    if(p==NULL)printf("�����ļ���ʧ�ܣ������ԣ�\n");
    else
    {
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                fscanf(p,"%d",&a[i][j]);                  //�ļ���ȡ
            }
        }
        while(1)
        {
            flag=0;
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    if(a[i][j]==0)
                    {
                        int k=0,l=0,c[9]={0};
                        for(k=0;k<9;k++)
                        {
                            if(a[k][j]!=0)c[a[k][j]-1]=a[k][j];        //������
                        }
                        for(l=0;l<9;l++)
                        {
                            if(a[i][l]!=0)c[a[i][l]-1]=a[i][l];         //������
                        }
                        for(k=(i/3)*3;k<(i/3)*3+3;k++)
                        {
                            for(l=(j/3)*3;l<(j/3)*3+3;l++)
                            {
                                if(a[k][l]!=0)c[a[k][l]-1]=a[k][l];      //������Ź���
                            }
                        }
                        int sum=0;
                        for(k=0;k<9;k++)
                        {
                            if(c[k]==0)
                            {
                                sum++;                                //����С��С��Ź�����
                                l=k;
                            }
                        }
                        if(sum==1)
                        {
                            a[i][j]=l+1;            //�С��С��Ź����Ƿ��һ��
                            flag=1;
                        }
                    }
                }
            }
            if(0==flag)break;
        }
        fclose(p);
        p=fopen("soduke.txt","w");
        if(p==NULL)
        {
            printf("����ļ���ʧ�ܣ������ԣ�\n");
        }
        else
        {
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    fprintf(p,"%d ",a[i][j]);                     //����ļ�
                }
				fprintf(p,"\n");
            }
            printf("����soduke.txt�в鿴�����⣡\n");
        }
    }
    fclose(p);
}

int main()
{
    shudu();                                                 //����������
    return 0;
}
