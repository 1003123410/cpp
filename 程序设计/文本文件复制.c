#include<stdio.h>

void copy(void)
{
    START:;
    FILE *in,*out;
    char infile[20]={0},outfile[20]={0};
    printf("��������Ҫ���Ƶ��ı��ļ���");
    scanf("%s",infile);
    printf("���Ƶ���");
    scanf("%s",outfile);
    in=fopen(infile,"r");
    out=fopen(outfile,"w");
    if(in==NULL)
    {
        printf("�ļ��ļ�%s��ʧ�ܣ������ԡ�\n",infile);
        goto START;
    }
    if(out==NULL)
    {
        printf("�ı��ļ�%s��ʧ�ܣ������ԡ�\n",outfile);
        goto START;
    }
    char c;
    while((c=fgetc(in))!=EOF)
    {
        fputc(c,out);
    }
    fclose(in);
    fclose(out);
    printf("�ı��ļ����Ƴɹ�������%s�в鿴��\n",outfile);
}

int main()
{
    copy();
    return 0;
}
