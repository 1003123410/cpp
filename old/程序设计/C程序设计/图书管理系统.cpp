#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define pause system("pause");
#define cls system("cls");

struct lib{										//ͼ����Ϣ�ṹ��
	char book[50];
	char hao[20];
	float jia;
	char zuo[30];
	int zhuang;
	char name[30];
	int sex;
	char stuhao[10];
};

struct zhu{										//�û���Ϣ�ṹ��
	char name[10];
	char code[30];
	int sex;
	char mingzi[30];
}baocun;

int deng=0;							//��ͨ�û������Ա�ĵ�¼״̬

int main();
void zhuce();
void denglu();
void chashu();
void huanshu();
void zhuxiao();
void jieshu(lib,zhu);
void jian(char *,char *);
int cha(char *,char *);
void zhuijia(char *,char *);
void gaimi();
void guihuan(lib);
void zengshu();
void shanshu();
void xiushu();
void chaalib();
void biaoti();
void gllib();
using namespace std;
int main(){										//���
	cls
		biaoti();
		jian("book.list"," ");
	jian("name.dat"," ");
	cout<<"				  ���˵�\n\n\n"<<endl;
	cout<<"				*1.ע��		*\n				*2.��½		*\n				*3.����		*\n				*4.����		*\n				*5.ע��		*\n				*6.����		*\n				*7.�˳�		*\n				*8.�����鼮	*\n				��ѡ��:";
	char xuan[50];
	cin>>xuan;
	switch(xuan[0]){
		case '8':gllib();
		break;
	case '1':zhuce();
		break;
	case '2':denglu();
		break;
	case '3':chashu();
		break;
	case '4':huanshu();
		break;
	case '5':zhuxiao();
		break;
	case '6':gaimi();
		break;
	case '7':exit(0);
	default:cout<<"\a\a��������!"<<endl;
		pause
			main();
	}
	main();
	return 0;
}

void denglu(){									//��ͨ�û���½����
	FILE *p;
	struct zhu temp;
	struct zhu mess;
	cls
		printf("������ѧ��:");
	cin>>mess.name;
	if(cha("black.list",mess.name)==1){
		printf("\a\a���û�������Ա���������������ϵ����Ա!\n");
		pause
			main();
	}
	printf("����������:");
	cin>>mess.code;
	p=fopen("name.dat","r");
	for(;;){
		fscanf(p,"%s",temp.name);
		fscanf(p,"%s",temp.code);
		fscanf(p,"%s",temp.mingzi);
		fscanf(p,"%d",&temp.sex);
		if(strcmp(temp.name,mess.name)==0&&strcmp(temp.code,mess.code)==0){
			fclose(p);
			baocun=temp;
			deng=1;								//��½�ɹ�
			return;
		}
		if(feof(p)){
			fclose(p);
			printf("\a\aѧ�Ż��������!�����������������Ա��ϵ\n");		//��¼ʧ��
			pause
				main();
		}
	}
}
void zhuce(){															//���û�ע�ắ��
	FILE *p;
	char temp1[30],temp2[30];
	struct zhu temp;
	struct zhu mess;
	cls
		printf("������ѧ��:");
	cin>>mess.name;
	if(cha("black.list",mess.name)==1){
		printf("\a\a���û�������Ա���������������ϵ����Ա!\n");
		pause
			main();
	}
	p=fopen("name.dat","r");
	for(;;){
		fscanf(p,"%s",temp.name);
		fscanf(p,"%s",temp.code);
		if(strcmp(temp.name,mess.name)==0){
			fclose(p);
			printf("\a\a���û��Ѵ���!\n");									//ע��ʧ��
			pause
				main();
		}
		if(feof(p)){
			fclose(p);
			break;
		}
	}
	printf("����������:");
	cin>>temp1;
	printf("���ٴ�����:");
	cin>>temp2;
	if(strcmp(temp1,temp2)!=0){
		printf("\a\a�����������벻һ��!\n");									//ע��ʧ��
		pause
			main();
	}
	else{
		strcpy(mess.code,temp1);
		printf("����������:");
		cin>>mess.mingzi;
		printf("�������Ա�(1.Ů2.��):");
		cin>>mess.sex;
		p=fopen("name.dat","a");
		fprintf(p,"%s\n%s\n%s\n%d\n",mess.name,mess.code,mess.mingzi,mess.sex);
		fclose(p);
		cls
			cout<<"\a\aע��ɹ�!\n�����û���Ϊ"<<mess.name<<"\n����Ϊ:"<<mess.code<<endl;   //ע��ɹ�
		deng=1;																		//��ס��¼״̬
		baocun=mess;																//�����¼��Ϣ
		pause
			main();
	}
}
void chashu(){																	//���麯��
	int queren;
	int jie;
	struct lib temp1;
	struct lib list[1000];														//������������ͼ����Ϣ
	int i;
	FILE *p;
	cls
		char temp[50];
	printf("����������:");
	cin>>temp;
	p=fopen("book.list","r");
	int shumu;
	shumu=0;
	for(;;){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		if(strstr(temp1.book,temp)!=NULL){
			list[shumu]=temp1;
			shumu++;
		}
	}
	if(shumu==0){
		printf("\a\aû�з����������鼮!\n");
		pause
			main();
	}
	cls
		printf("���\t����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	for(i=0;i<shumu-1;i++){
		printf("%d\t%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",i+1,list[i].book,list[i].hao,list[i].jia,list[i].zuo,list[i].zhuang,list[i].name,list[i].sex,list[i].stuhao);
	}
	printf("������������:");
	cin>>jie;
	cls
		printf("����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",list[jie-1].book,list[jie-1].hao,list[jie-1].jia,list[jie-1].zuo,list[jie-1].zhuang,list[jie-1].name,list[jie-1].sex,list[jie-1].stuhao);
	if(list[jie-1].zhuang==0){
		printf("\a\a�����ѱ��û�%s���!\n",list[jie-1].name);
		pause
			main();
	}
	else{
		if(deng!=0){
			printf("ȷ�Ͻ����\n1.��2.��\n��ѡ��:");
			cin>>queren;
			if(queren==1){

				jieshu(list[jie-1],baocun);
			}
			else{
				cls
					printf("\a\a���ѷ�������!\n");
				pause
					main();
			}
		}
		else{
			printf("\a\a����δ��¼!���¼!\n");
			pause
				denglu();
			cls
				printf("ȷ�Ͻ����\n1.��2.��\n��ѡ��:");
			cin>>queren;
			if(queren==1){

				jieshu(list[jie-1],baocun);
			}
			else{
				cls
					printf("\a\a���ѷ�������!\n");
				pause
					main();
			}
		}
	}
}

void zhuxiao(){
	cls
		int zhu;
	if(deng==0){
		printf("\a\a����δ��¼!\n");
		pause
			main();
	}
	printf("ȷ��ע����\n1.��2.��\n��ѡ��:");
	cin>>zhu;
	if(zhu==1){
		deng=0;
		printf("\a\a����ע��!\n");
		pause
			main();
	}
	else{
		printf("\a\a��δ��ע��!\n");
		pause
			main();
	}
}
void jieshu(lib shu,zhu ren){
	cls
		FILE *p;
	int i,j;
	struct lib temp1[1000];
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1[i].book,temp1[i].hao,&temp1[i].jia,temp1[i].zuo,&temp1[i].zhuang,temp1[i].name,&temp1[i].sex,temp1[i].stuhao);
	}
	for(j=0;j<i;j++){
		if(strcmp(shu.hao,temp1[j].hao)==0&&strcmp(shu.book,temp1[j].book)==0){
			temp1[j].zhuang=0;
			strcpy(temp1[j].name,ren.mingzi);
			strcpy(temp1[j].stuhao,ren.name);
			temp1[j].sex=ren.sex;
			break;
		}
	}
	p=fopen("book.list","w");
	for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",temp1[j].book,temp1[j].hao,temp1[j].jia,temp1[j].zuo,temp1[j].zhuang,temp1[j].name,temp1[j].sex,temp1[j].stuhao);
	}
	fclose(p);
	printf("\a\a%s����%s�ɹ�!\n",ren.mingzi,shu.book);
	pause
		main();
}
void jian(char *file,char *name){
	FILE *p;
	if((p=fopen(file,"r"))==NULL){
		if(strcmp(name," ")==0){
			p=fopen(file,"w");
			fclose(p);
			return;
		}
		else{
			p=fopen(file,"w");
			fprintf(p,"%s\n",name);
			fclose(p);
			return;
		}
	}
	else{
		fclose(p);
		return;
	}
}
void huanshu(){
	cls
		lib temp1;
	lib list[1000];
	char shu[50];
	int shumu=0,jie,queren,i;
	FILE *p;
	printf("������Ҫ�黹������:");
	cin>>shu;
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		if(strstr(temp1.book,shu)!=NULL&&temp1.zhuang==0){
			list[shumu]=temp1;
			shumu++;
		}
	}
	if(shumu==0){
		printf("\a\aû�з����������鼮!\n");
		pause
			main();
	}
	cls
		printf("���\t����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	for(i=0;i<shumu;i++){
		printf("%d\t%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",i+1,list[i].book,list[i].hao,list[i].jia,list[i].zuo,list[i].zhuang,list[i].name,list[i].sex,list[i].stuhao);
	}
	printf("�����뻹�����:");
	cin>>jie;
	cls
		printf("����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",list[jie-1].book,list[jie-1].hao,list[jie-1].jia,list[jie-1].zuo,list[jie-1].zhuang,list[jie-1].name,list[jie-1].sex,list[jie-1].stuhao);

		printf("ȷ�Ϲ黹��\n1.��2.��\n��ѡ��:");
		cin>>queren;
		if(queren==1){
			guihuan(list[jie-1]);
		}
		else{
			cls
				printf("\a\a���ѷ�������!\n");
			pause
				main();
		}
}
int cha(char *file,char *str){
	FILE *p;
	char temp[100];
	p=fopen(file,"r");
	for(;;){
		fscanf(p,"%s",temp);
		if(strcmp(temp,str)==0){
			fclose(p);
			return 1;
		}
		if(feof(p)){
			fclose(p);
			return 0;
		}
	}
}
void guihuan(lib shu){
	FILE *p;
	int i,j;
	lib temp1[1000];
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1[i].book,temp1[i].hao,&temp1[i].jia,temp1[i].zuo,&temp1[i].zhuang,temp1[i].name,&temp1[i].sex,temp1[i].stuhao);
	}
	for(j=0;j<i;j++){
		if(strcmp(shu.hao,temp1[j].hao)==0&&strcmp(shu.book,temp1[j].book)==0){
			temp1[j].zhuang=1;
			strcpy(temp1[j].name,"0");
			strcpy(temp1[j].stuhao,"0");
			temp1[j].sex=0;
			break;
		}
	}
	p=fopen("book.list","w");
	for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",temp1[j].book,temp1[j].hao,temp1[j].jia,temp1[j].zuo,temp1[j].zhuang,temp1[j].name,temp1[j].sex,temp1[j].stuhao);
	}
	fclose(p);
	printf("\a\a����%s�ɹ�!\n",shu.book);
	pause
		main();
}
void zhuijia(char *file,char *str){
	FILE *p;
	p=fopen(file,"a");
	fprintf(p,"%s\n",str);
	fclose(p);
}
void zhuijia(char *file,float str){
	FILE *p;
	p=fopen(file,"a");
	fprintf(p,"%g\n",str);
	fclose(p);
}
void gaimi(){
	cls
		FILE *p;
	zhu temp[1000];
	int i,j;
	char temp1[30],temp2[30];
	if(deng==0){
		printf("\a\a����δ��¼�����ܽ��и��ܲ���!\n");
		pause
			main();
	}
	else{
		printf("������������:");
		cin>>temp1;
		printf("���ٴ�����:");
		cin>>temp2;
		if(strcmp(temp1,temp2)!=0){
			printf("\a\a�����������벻һ��������ʧ��!\n");
			pause
				main();
		}
		else{
			p=fopen("name.dat","r");
			for(i=0;;i++){
				if(feof(p)){
					fclose(p);
					break;
				}
				fscanf(p,"%s%s%s%d",temp[i].name,temp[i].code,temp[i].mingzi,&temp[i].sex);
			}
			for(j=0;j<i;j++){
				if(strcmp(temp[j].name,baocun.name)==0){
					strcpy(temp[j].code,temp1);
					break;
				}
			}
			p=fopen("name.dat","w");
			for(j=0;j<i-1;j++){
				fprintf(p,"%s\n%s\n%s\n%d\n",temp[j].name,temp[j].code,temp[j].mingzi,temp[j].sex);
			}
			fclose(p);
			deng=0;
			printf("\a\a���ܳɹ�!�����µ�¼!\n");
			pause
				main();
		}
	}
}

void gllib(){
	cls
		char xuan[20];
	printf("				 ����ͼ��\n");
	printf("			*************************\n			*1.����ͼ��		*\n			*2.�޸�ͼ����Ϣ		*\n			*3.ɾ��ͼ��		*\n			*4.�鿴ȫ��ͼ����Ϣ	*\n			*5.����			*\n			*************************\n��ѡ��:");
	cin>>xuan;
	switch (xuan[0]){
	case '1':zengshu();
		break;
	case '2':xiushu();
		break;
	case '3':shanshu();
		break;
	case '4':chaalib();
		break;
	case '5':main();
		break;
	default:printf("\a\a��������!\n");
		pause
			gllib();
	}
}
void biaoti(){
	char titles[100]="ͼ�����ϵͳ ";
	if(deng==1){
	strcat(titles,"��ͨ�û�");
	strcat(titles,baocun.name);
	strcat(titles,"�ѵ�¼");
	}
	else{
	strcat(titles,"��ͨ�û�δ��¼  ");
	}

	char temp[100]="title ";
	strcat(temp,titles);
	system(temp);
}

void zengshu(){
	cls
		lib shu;
	printf("����������:");
	cin>>shu.book;
	printf("������ISBN��:");
	cin>>shu.hao;
	if(cha("book.list",shu.hao)==1){
		printf("\a\a����鼮ʧ��!��ISBN���Ѵ���!\n");
		pause
			gllib();
	}
	else{
		printf("�����뵥��:");
		cin>>shu.jia;
		printf("����������:");
		cin>>shu.zuo;
		printf("������״̬(1.�ټ���0.�ѽ��):");
		cin>>shu.zhuang;
		printf("�������������(��δ�������0):");
		cin>>shu.name;
		printf("����������Ա�(1.��2.Ů,��δ�������0):");
		cin>>shu.sex;
		printf("���������ѧ��(��δ�������0)");
		cin>>shu.stuhao;
		zhuijia("book.list",shu.book);
		zhuijia("book.list",shu.hao);
		zhuijia("book.list",shu.jia);
		zhuijia("book.list",shu.zuo);
		zhuijia("book.list",(float)shu.zhuang);
		zhuijia("book.list",shu.name);
		zhuijia("book.list",(float)shu.sex);
		zhuijia("book.list",shu.stuhao);
		printf("\a\aͼ��%s�����ɹ�!\n",shu.book);
		pause
			gllib();
	}
}
void xiushu(){
	cls
		FILE *p;
	char shu[50],book[50],hao[50];
	lib shus[1000];
	int i,j,k=0,xuan;
	printf("��������Ҫ�޸���Ϣ������:");
	cin>>shu;
		p=fopen("book.list","r");
		for(i=0;;i++){
			if(feof(p)){
				fclose(p);
				break;
			}
			fscanf(p,"%s%s%f%s%d%s%d%s",shus[i].book,shus[i].hao,&shus[i].jia,shus[i].zuo,&shus[i].zhuang,shus[i].name,&shus[i].sex,shus[i].stuhao);
		}
		for(j=0;j<i-1;j++){
			if(strstr(shus[j].book,shu)!=NULL){
				k++;
				cls
		printf("����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
	printf("�Ƿ��޸�?(1.��2.��):");
	cin>>xuan;
	if(xuan==2){
	cls
		continue;
	}
	printf("����������:");
	cin>>book;
	printf("������ISBN��:");
	cin>>hao;
	if(cha("book.list",hao)==1){
		printf("\a\a�޸��鼮ʧ��!��ISBN���Ѵ���!\n");
		pause
	}
	else{
		strcpy(shus[j].book,book);
		strcpy(shus[j].hao,hao);
		printf("�����뵥��:");
		cin>>shus[j].jia;
		printf("����������:");
		cin>>shus[j].zuo;
		printf("������״̬(1.�ټ���0.�ѽ��):");
		cin>>shus[j].zhuang;
		printf("�������������(��δ�������0):");
		cin>>shus[j].name;
		printf("����������Ա�(1.��2.Ů,��δ�������0):");
		cin>>shus[j].stuhao;
		printf("���������ѧ��(��δ�������0)");
		cin>>shus[j].stuhao;
		printf("�Ƿ����?(1.��2.��):");
		cin>>xuan;
		if(xuan==1){
		cls
			continue;
		}
		else{
		break;
		}
	}

			}
		}
		if(k==0){
		printf("\a\aδ�ҵ���ͼ��!\n");
		pause
			gllib();
		}
		else{
		p=fopen("book.list","w");
		for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
		}
		fclose(p);
		printf("\a\a�޸ĳɹ�!\n");
		pause
			gllib();
		}
}
void shanshu(){
		cls
		FILE *p;
	char shu[50];
	lib shus[1000];
	int i,j,k=0,l=0,xuan,shanxu[1000],m,you;
	printf("��������Ҫɾ��������:");
	cin>>shu;
		p=fopen("book.list","r");
		for(i=0;;i++){
			if(feof(p)){
				fclose(p);
				break;
			}
			fscanf(p,"%s%s%f%s%d%s%d%s",shus[i].book,shus[i].hao,&shus[i].jia,shus[i].zuo,&shus[i].zhuang,shus[i].name,&shus[i].sex,shus[i].stuhao);
		}
		for(j=0;j<i-1;j++){
			if(strstr(shus[j].book,shu)!=NULL){
				k++;
				cls
		printf("����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
	printf("�Ƿ�ɾ��?(1.��2.��):");
	cin>>xuan;
	if(xuan==2){
	cls
		continue;
	}
shanxu[l]=j;
l++;
		printf("�Ƿ����?(1.��2.��):");
		cin>>xuan;
		if(xuan==1){
		cls
			continue;
		}
		else{
		break;
		}
			}
		}
		if(k==0){
		printf("\a\aδ�ҵ���ͼ��!\n");
		pause
			gllib();
		}
		else{
		p=fopen("book.list","w");
		for(j=0;j<i-1;j++){
			you=0;
			for(m=0;m<l;m++){
				if(shanxu[m]==j){
					you=1;
					break;
				}
			}
			if(you==0)fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
		}
		fclose(p);
		printf("\a\aɾ���ɹ�!\n");
		pause
			gllib();
		}
}
void chaalib(){
	cls
	FILE *p;
	lib temp1;
		printf("����\t\tISBN��\t����\t����\t״̬\t����\t�Ա�\tѧ��\n");
		p=fopen("book.list","r");
		for(;;){
			if(feof(p)){
			fclose(p);
			break;
			}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",temp1.book,temp1.hao,temp1.jia,temp1.zuo,temp1.zhuang,temp1.name,temp1.sex,temp1.stuhao);
		}
		pause
			gllib();
}

void chaazhu(){
		cls
	FILE *p;
	zhu shus;
		printf("ѧ��\t\t����\t�Ա�\n");
		p=fopen("name.dat","r");
		for(;;){
			if(feof(p)){
			fclose(p);
			break;
			}
		fscanf(p,"%s%s%s%d",shus.name,shus.code,shus.mingzi,&shus.sex);
		printf("%s\t%s\t%d\n",shus.name,shus.mingzi,shus.sex);
		}
		pause
			main();
}
