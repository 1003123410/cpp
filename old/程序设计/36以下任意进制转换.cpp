#include<stdio.h>
#include<math.h>
#include<string.h>                 //36��������
void fun(int in,int out,int sum,char a[]);    //ת������
int main()
{
    while(1)
    {
        int i,j,k;
        char a[100]={0};
        printf("���������ƣ�");
        scanf("%d",&i);
        getchar();
        printf("���������ݣ�");
        scanf("%s",a);
        printf("ת�������ƣ�");
        scanf("%d",&j);
        k=strlen(a);
        fun(i,j,k,a);
    }
    return 0;
}
void fun(int in,int out,int sum,char a[])
{
    int k;
    long temp=0;
    for(k=0;k<sum;++k)
    {
        if(a[sum-k-1]>='A'&&a[sum-k-1]<='Z')a[sum-k-1]=a[sum-k-1]-'A'+'9'+1;  //A��Z��ֵ�ӵ���9���ĺ���
        temp+=(a[sum-k-1]-'0')*pow(in,k);   //ת��Ϊ10��������long�洢
    }
    k=0;
    while(1)
    {
        a[k]=temp%out;
        temp/=out;
        if(temp==0)break;
        ++k;              //ʮ����ת��Ϊ�����������
    }
    for(in=k;in>=0;--in,--k)
    {
        if(a[in]>=0&&a[in]<=9)printf("%d",a[in]);
        else if(a[in]>=10&&a[in]<=25)printf("%c",a[in]+55);   //��ӡ����
        if(k%4==0)printf(" ");       //ÿ�ĸ�ֵ���һ���ո�
    }
    putchar('\n');
}
//yangyang
