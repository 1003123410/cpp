#include<stdio.h>

int main()
{
    printf("������ѡ�");
    int i;
	printf("1����ASCII�����   2�����ַ�����   3����ӡASCII���\n");
    scanf("%d",&i);
    getchar();
    if(1==i)
    {
        int j;
        printf("������ASCII��ֵ��");
        scanf("%d",&j);
        char c=j;
        if(j>=0&&j<128)printf("ֵΪ%d���ַ�Ϊ��%c\n",j,c);
        else
        {
            printf("����ֵ����");
            main();
        }
        main();
    }
    if(2==i)
    {
        char c;
        printf("������Ҫ���ҵ��ַ���");
        scanf("%c",&c);
        int j=c;
        printf("�ַ�%c��ASCII��ֵΪ��%d\n",c,j);
        main();
    }
    if(3==i)
    {
        int j;
        for(j=0;j<128;j++)
        {
            if(j<100)printf("%d    %c    ",j,j);
            else printf("%d   %c    ",j,j);
			if(0==j%5)printf("\n");
        }
        putchar('\n');
        main();
    }
    else main();
    return 0;
}
