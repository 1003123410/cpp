#include<stdio.h>
#include<string.h>

void jiema(void)
{
	int i=0,j=0;
    char c[20]={0},d[20]={0},b[20]={0};
    printf("��������Ҫ���ܵ��ַ�����");
    scanf("%s",c);
    printf("���������룺");
    scanf("%s",b);
    for(i=0,j=0;i<strlen(c);i++)
    {
        d[i]=c[i]-(b[j]-'0');
		j++;
        if(j>=strlen(b))j=0;
    }
    printf("���ܺ��ַ���Ϊ��");
	puts(d);
}

void jiami(void)
{
    int i=0,j=0;
	char c[20]={0},d[20]={0},b[20]={0};
    printf("��������Ҫ���ܵ��ַ�����");
    scanf("%s",c);
    printf("�����벻����20λ�����룺");
    scanf("%s",b);
    for(i=0,j=0;j<strlen(c);j++)
    {
        d[j]=c[j]+(b[i]-'0');
		i++;
		if(i>=strlen(b))i=0;
    }
    printf("���ܺ���ַ���Ϊ��");
	puts(d);
}

void select(void)
{
    int n;
    printf("1������     2������\n");
    printf("����������ѡ�");
    scanf("%d",&n);
	getchar();
    if(n==1)jiami();
    if(n==2)jiema();
}

int main()
{
    while(1)
    {
        select();
    }
    return 0;
}
