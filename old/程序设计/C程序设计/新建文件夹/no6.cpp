#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pause system("pause");
#define cls system("cls");

void jisuan(char);

main(){
	cls
		char h[20];
	printf("��������������(1.�ӷ�2.����3.�˷�):");
	scanf("%s",h);
	switch(h[0]){
	case '1':jisuan('+');
		break;
	case '2':jisuan('-');
		break;
	case '3':jisuan('*');
		break;
	default:printf("��������!");
		pause
			main();
	}
}


void jisuan(char a){
	int b,c,d,f,i,j=0;
	cls
	printf("�����������Ŀ:");
	scanf("%d",&f);
	for(i=0;i<f;i++){
		cls
		srand(time(0));
		b=rand()%100;
		c=rand()%100;
		printf("%d%c%d=",b,a,c);
		scanf("%d",&d);
		switch(a){
		case '+':
		if(d==b+c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n��ȷ��Ϊ%d",b+c);
			pause
		}
		break;
		case '-':
		if(d==b-c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n��ȷ��Ϊ%d",b-c);
			pause
		}
		break;
		case '*':
		if(d==b*c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n��ȷ��Ϊ%d",b*c);
			pause
		}
		break;
		}
	}
	cls
	printf("������%d������ȷ%d����\n",f,j);
	pause 
}

