#include<stdio.h>

int main()
{
    printf("����������������");
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;++i)
    {
        printf("��������ݣ�");
        int year,month;
        scanf("%d",&year);
        printf("�������·ݣ�");
        scanf("%d",&month);
        putchar('0');
        switch(month)
        {
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            printf("%d��%d����31��\n",year,month);
            break;
            case 4:case 6:case 9:case 11:
            printf("%d��%d����30��\n",year,month);
            break;
            case 2:
            if(year%4==0&&year%100!=0||year%400==0)
            printf("%d��%d����28��\n",year,month);
            else printf("%d��%d����29��\n",year,month);
            break;
            default:
            printf("��������\n");
            break;
        }
    }
    return 0;
}
