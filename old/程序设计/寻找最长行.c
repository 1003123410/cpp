#include<stdio.h>
#include<string.h>

int main()
{
    printf("�������ַ�����\n");
    char a[100]={0},b[100]={0},c[]="***end***";
    int m,n;
    while(1)
    {
        gets(a);
        n=strlen(a);
        m=strlen(b);
        if(strcmp(a,c)==0)
        {
            break;
        }
        if(n>m)
        {
            strcpy(b,a);
        }
    }
    puts(b);
    printf("��г���Ϊ��%d",m);
    return 0;
}
