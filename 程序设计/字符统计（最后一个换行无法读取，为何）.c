#include<stdio.h>

void zifu(void)
{
    FILE *p;
    int letter=0,number=0,space=0,other=0,i=0;
    char c;
    p=fopen("1.txt","r");
    if(p==NULL)
    {
        printf("�ļ�δ�ܳɹ��򿪣�\n");
    }
    else
    {
        while((c=fgetc(p))!=EOF)
        {
            if(c>='a'&&c<='z'||c>='A'&&c<='Z')letter++;
            else if(c>='0'&&c<='9')number++;
            else if(c==' ')space++;
            else other++;
        }
        printf("���ļ�1.txt����ĸ��%d��\n����%d��\n�ո�%d��\n�����ַ���%d��\n�ļ��й����ַ�%d��",letter,number,space,other,letter+number+space+other);
    }
    fclose(p);
}

int main()
{
    zifu();
    return 0;
}
