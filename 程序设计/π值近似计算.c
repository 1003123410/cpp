#include<stdio.h>
#include<math.h>

int main()
{
    double n;
    printf("�������ֵ���㾫�ȣ�");
    scanf("%lf",&n);
    int j=1;
    double i=1,pi=0;
    while(fabs(1/i)>=n)
    {
        pi+=j/i;
        i+=2;
        j=-j;
    }
    printf("�еĽ���ֵΪ%lf\n",pi*4);
    return 0;
}
