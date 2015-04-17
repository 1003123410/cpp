#include<stdio.h>
#include<math.h>
#define MAXPOINT 100                    //����������

typedef struct
{
    double x;
    double y;
}point;                                  //�ṹ�嶨��

int input(point p[])
{
    int n=0;
    printf("�����������꣬���ؼ����ţ�\n");
    while(scanf("%lf%lf",&p[n].x,&p[n].y)==2)n++;
    return n;
}                                        //���뺯��

double polylength(point p[],int n)
{
    int i=0;
    double length=0.0;
    for(;i<n-1;i++)
    {
        length+=sqrt(pow((p[i+1].x-p[i].x),2.0)+pow((p[i+1].y-p[i].y),2.0));
    }
    return length;
}                                         //���߶γ��ȼ��㺯��

void output(double length)
{
    printf("���߶γ���Ϊ:%.4f\n",length);
}                                         //�������

int main()
{
    point p[MAXPOINT];
    int count=input(p);
    output(polylength(p,count));
    return 0;
}                                            //������
