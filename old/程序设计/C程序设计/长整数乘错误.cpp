#include<stdio.h>
int main(){
	int i,m,n,b[1024];
    printf("ע�⣺���������ʾһ����������ֻ���������ֳ���n���Լ���λ�����ɣ�\n");
	printf("���볤�����ĳ���n\n");scanf("%d",&n);
	printf("�������λ����\n");
	for(i=n;i>=1;--i)
		scanf("%d",&b[i]);
	b[0]=n;
	printf("������Ҫ�˵�����\n");
	scanf("%d",&m);
	for(i=n;i>=2;--i)
		printf("%d*10^%d+",b[i]*m,i-1);
	printf("%d\n",b[1]*m);
	return 0;
}
