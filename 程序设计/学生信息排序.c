#include<stdio.h>
#include<string.h>
#define N 5

typedef struct
{
    int number;
    char name[20];
    double physics;
    double math;
    double computer;
    double sum;
}student;

void mathsort(student stu[])
{
    int i=0,j;
    student t;
    printf("����ѧ�ɼ�������Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].math<stu[j].math)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void physicssort(student stu[])
{
    int i=0,j;
    student t;
    printf("������ɼ�������Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].physics<stu[j].physics)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void computersort(student stu[])
{
    int i=0,j;
    student t;
    printf("��������ɼ�������Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].computer<stu[j].computer)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void numbersort(student stu[])
{
    int i=0,j;
    student t;
    printf("��ѧ������Ľ��Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].number<stu[j].number)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void namesort(student stu[])
{
    int i=0,j;
    student t;
    printf("������������Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(strcmp(stu[i].name,stu[j].name)<0)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void sumsort(student stu[])
{
    int i=0,j;
    student t;
    printf("���ܷ�������Ϊ��\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if((stu[i].math+stu[i].physics+stu[i].computer)<(stu[j].math+stu[j].physics+stu[j].computer))
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void select(void)
{
    student stu[N];
    printf("����������ѧ��������");
    int i;
    for(i=0;i<N;i++)
    {
        printf("������ѧ��������");
        scanf("%s",&stu[i].name);
        printf("������ѧ�ţ�");
        scanf("%d",&stu[i].number);
        printf("��������ѧ�ɼ���");
        scanf("%lf",&stu[i].math);
        printf("����������ɼ���");
        scanf("%lf",&stu[i].physics);
        printf("�����������ɼ���");
        scanf("%lf",&stu[i].computer);
        stu[i].sum=stu[i].computer+stu[i].math+stu[i].physics;
    }
    while(1)
    {
        int n;
        printf("1������������         2����ѧ������\n");
        printf("3������ѧ�ɼ�����     4��������ɼ�����\n");
        printf("5����������ɼ�����   6�����ܷ�����\n");
        printf("0���˳�\n");
        printf("���������ѡ�");
        scanf("%d",&n);
        switch(n)
        {
            case 1:namesort(stu);break;
            case 2:numbersort(stu);break;
            case 3:mathsort(stu);break;
            case 4:physicssort(stu);break;
            case 5:computersort(stu);break;
            case 6:sumsort(stu);break;
            default:break;
        }
    }
}


int main()
{
    select();
    return 0;
}
