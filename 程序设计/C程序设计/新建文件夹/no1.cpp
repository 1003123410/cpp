#include<stdio.h>
#include<stdio.h>
#include<math.h>

int isleayear(int year){
          return  year%4==0&&year%100!=0||year%400==0;
}                                                                             //�����ж�
int NUM(int year,int k){
	int x;
	 if(k==0||k==2||k==4||k==7||k==9||k==11)x=31;
     if(k==3||k==5||k==6||k==8||k==10)x=30;
	 if(isleayear(year)&&k==1)x=29;
	 if(isleayear(year)==0&&k==1)x=28;
	return x;
}                                                                             //�ж�ÿ������

int main(){
       int n,k,year,m,i,j; 
	   char mon[12][12]={"һ��","����","����","����","����","����","����","����","����","ʮ��","ʮһ��","ʮ����"};
	   printf("�������\n");
	   scanf("%d",&year);
	   if(isleayear(year)==1 || year<2000)
	     n=(int)(fabs(year-2000)*365+(int)fabs(year-2000)/4)%7;                //�ж�ĳ��һ��һ��Ϊ���ڼ�
	   else
         n=(int)(fabs(year-2000)*365+(int)fabs(year-2000)/4+1)%7;
	   if(year<2000)n=7-n;                                                     //�����С��2000��һ��һ�����ڼ�
	   for(k=0;k<12;++k){
	      printf("%s\n�� һ �� �� �� �� ��\n",mon[k]);
          if(n==0) n+=7;
		  else 
			  if(n==8)
				  n=1;
	      m=1;
		  for(j=0;j<n-1;++j)					
			  printf("   ");
		  for(j=n-1;j<7;++j){
			  printf("%2d%c",m,j==6? '\n': ' ');
			  m=m+1;
		  }	
		  for(i=1;i<=5;++i){
			  for(j=0;j<7&&m<=NUM(year,k);++j){
			  	   printf("%2d%c",m,j==6? '\n': ' ');
				   m=m+1;
                   if(m-1==NUM(year,k)){n=j+2;printf("\n");break;}                //�������
			  }
		  }
		 }
return 0;
}
