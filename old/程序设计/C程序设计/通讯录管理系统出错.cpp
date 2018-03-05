#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{                                                        //����ṹ��
      char name[20],sex[4],phone[20],email[20],address[30];
	  int id;
	  struct node *next;
}Listnode;
typedef Listnode * Linklist;
void printf_title();                                                        //��������
int menu();
int slect_menu();
Listnode *read_file();
void write_file(Linklist head);
void printf_file();
void delet_file();
void add_file();
void modify_file();
void printf_title()
{	                                                    //���⺯��
	printf("\t\t\t\tͨ��¼����ϵͳ\n");
}

int menu()
{                                                                 //�˵�����
	  int select;
      system("cls");
	  printf_title();
	  printf("\t\t\t1.��Ա��ѯ\n");
	  printf("\t\t\t2.��Ա����\n");
	  printf("\t\t\t3.��Աɾ��\n");
	  printf("\t\t\t4.��Ա��Ϣ�޸�\n");
	  printf("\t\t\t5.ϵͳ�˳�\n");
	  printf("\t\t\t����Ҫ�����Ĺ��ܺ�:");
	  scanf("%d",&select);
	  while(select<1||select>5){
	     printf("����ѡ�������⣬����������\n");	  
		 scanf("%d",&select);
	  }
	  return select;                                                           //����Ҫ�����ı��
}

int select_menu()
{                                                              //�˵���ѡ����
       int sel=menu(),a=0;
	   switch(sel)
	   {
	   case 1:printf_file();system("PAUSE");break;
       case 2:add_file();system("PAUSE");break;
       case 3:delet_file();system("PAUSE");break;
       case 4:modify_file();system("PAUSE");break;
	   case 5:a=1;break;
	   }
	   
	   return a;
}

Listnode *read_file()
{                                                          //�ļ���ȡ����
        FILE *np;
		Listnode *p,*q,*head,A;
		head=p=NULL;
		if((np=fopen("a.txt","r"))==NULL)
			printf("wrong\n");
	    fscanf(np,"%d%s%s%s%s%s",&A.id,A.name,A.sex,A.phone,A.email,A.address);
		while(!feof(np))
		{
			p=(Listnode*)malloc(sizeof(Listnode));		
			p->id=A.id,strcpy(p->name,A.name);strcpy(p->sex,A.sex);
			strcpy(p->phone,A.phone);strcpy(p->email,A.email);strcpy(p->address,A.address);
			if(head==NULL) head=p;
			else q->next=p;
			q=p;
	        fscanf(np,"%d%s%s%s%s%s",&A.id,A.name,A.sex,A.phone,A.email,A.address);
		}
		q->next=NULL;fclose(np);
		return head;
}

void write_file(Linklist head)
{                                                //�ļ�����д�뺯��
	Linklist p=head;FILE *np;
		if((np=fopen("a.txt","w"))==NULL)
			printf("wrong\n");
		while(p!=NULL)
		{
		      fprintf(np,"%d\t%s\t\t%s\t%s\t%s\t%s\n",p->id,p->name,p->sex,p->phone,p->email,p->address);
				  p=p->next;		
		}
		fclose(np);
}

void printf_file()
{                                                              //��Ϣ��ѯ����
    Linklist p=read_file();system("cls");
    printf_title();
	printf("���\t����\t�Ա�\t�绰\t\temail\t\t\t��ַ\n");
	while(p!=NULL)
	{
	      printf("%d\t%s\t%s\t%s\t%s\t%s\n",p->id,p->name,p->sex,p->phone,p->email,p->address);
		  p=p->next;
	}
}

void delet_file()
{                                                             //��Աɾ������
      int i,n=1;
	  Linklist head,p=read_file(),q=p;head=p; 
      printf_file();
	  printf("������Ҫɾ������Ա���\n");scanf("%d",&i);
      while(p!=NULL)
	  {
          if(i==p->id)
			  if(n==1)
			  {
				  head=p->next;break;
			  }
			  else break;	 
	       q=p;
		   p=p->next; 
		   ++n;
	  }
	  q->next=p->next;
	  printf("ɾ���ɹ�\n");
      write_file(head);
}

void add_file()
{                                                         //��Ա��Ӻ���
      Linklist head,p=read_file(),q;
	  head=p;
      printf_file();
	  printf("����Ҫ��ӵ���Ա����Ϣ\n");		
	  q=(Listnode*)malloc(sizeof(Listnode));
	  scanf("%d%s%s%s%s%s",&q->id,q->name,q->sex,q->phone,q->email,q->address);
      while(1)
	  {
		   if(p->next!=NULL)p=p->next;
		   else {p->next=q;break;
		   }
	  }
	  q->next=NULL;
	  printf("��ӳɹ�\n");
      write_file(head);
}

void modify_file()
{
      Linklist head,p=read_file(),q,f;
	  int i;
	  head=p;
      printf_file();
	  printf("����Ҫ�޸ĵ���Ա�ı��\n");
	  scanf("%d",&i);
	  while((i!=p->id)&&p!=NULL
		  ){
		  f=p;p=p->next;
	  }
	  printf("�����޸ĺ����Ϣ\n");
	  q=(Listnode*)malloc(sizeof(Listnode));
	  scanf("%d%s%s%s%s%s",&q->id,q->name,q->sex,q->phone,q->email,q->address);
      if(i==head->id){head=q;q->next=p->next;
	  }
	  else{f->next=q;q->next=p->next;
	  }
	  printf("�޸ĳɹ�\n");
	  write_file(head);
}


int main()
{
	int a;
	while(a!=1)
	  a=select_menu();
	printf("\t\t\t�˳��ɹ�\n");
return 0;
}
