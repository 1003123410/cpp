#include<stdio.h>
#include<math.h>
#define PI 3.1415926

int main()
{
   int a,b;
   double c,d;
   printf("����������ͽ����ֱ������λ���ף���");
   scanf("%d%d",&a,&b);
   c=pow((a/2000.0),3)*PI*(4.0/3.0)*7860000;
   d=pow((b/2000.0),3)*PI*(4.0/3.0)*19300000;
   printf("���������Ϊ%.3f��\n��������Ϊ%.3f��\n",c,d);
return 0;
}
