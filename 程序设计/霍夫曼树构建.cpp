#include <iostream>
using namespace std;
typedef struct HFTree
{
	double num;
	struct HFTree *left,*right;
}HFTNode,*HF;
HF connect(HF h,HF t)//����������Ϊһ����
{
	HF p;
	p=new HFTNode;
	p->num=(h->num)+(t->num);
	p->left=h;
	p->right=t;
	return p;
}
void preview(HF t)//���������
{
	if(t)
	{
		cout<<t->num<<endl;
		preview(t->left);
		preview(t->right);
	}
}
int main()
{
	int n;
	cout<<"��������������"<<endl;
	cin>>n;
	cout<<"���������ݣ�";
	HF *h=new HF[n];
	for (int i=0;i<n;++i)
	{
		double temp;
		cin>>temp;
		h[i]=new HFTNode;//�����ڵ�
		h[i]->num=temp;
		h[i]->left=NULL;
		h[i]->right=NULL;
	}
	int max=0,root=0;
	for (int i=0;i<n;++i)
		if (h[max]->num>h[i]->num)
			max=i;
	int *flag=new int[n];//��־���飬����Ѱ����С��������
	for (int i=0;i<n;++i)
		flag[i]=0;
	for(int i=1;i<n;++i)
	{
		int min=0,j=0;
		for (j=0;j<n;++j)
			if (0==flag[j])
			{
				root=j;
				break;
			}//��ʼδ�ù�����
		for (j=0;j<n;++j)
			if(flag[j]==0&&h[root]->num>h[j]->num)
				root=j;//��С����
		for (j=0;j<n;++j)
			if (0==flag[j]&&j!=root)
			{
				min=j;
				break;
			}//��ʼδ�ù�����
		for (j=0;j<n;++j)
			if (flag[j]==0&&j!=root&&h[j]->num<h[min]->num)
				min=j;//�ڶ�С����
		flag[min]=1;
		cout<<"root:"<<root<<" "<<min<<endl;
		h[root]=connect(h[root],h[min]);//������������С����Ϊ��
	}
	preview(h[root]);//�������
	cout<<endl<<endl;
	getchar();
	getchar();
	return 0;
}