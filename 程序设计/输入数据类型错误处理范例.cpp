#include <stdio.h>

int main(int argc, char *argv[])
{
    int i=0;
    while (scanf("%d", &i)!=1)
    {
        printf("�����������ʹ���\n�������������ݣ�");
        while(getchar()!='\n');   //���뻺���������봦�����ʱ�Ὣ����ͣ���ڻ�������getchar�������������Ϣ���Ե���
    }
    for(;i<10;++i)printf("%d",i);
    return 0;
}
//���ı���ΪUTF-8
