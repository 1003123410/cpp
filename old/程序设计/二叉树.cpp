#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct BitNode
{
    char data;
    struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void createBitTree(BitTree &T)//���������
{
    char ch;
    cin>>ch;
    if(ch=='.')T=NULL;
    else
    {
        T=(BitTree)malloc(sizeof(BitNode));
        T->data=ch;
        createBitTree(T->lchild);
        createBitTree(T->rchild);
    }
}
void preOrder(BitTree T)//�������
{
    if(T)
    {
        cout<<T->data<<"  ";
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
void inOrder(BitTree T)//�������
{
    if(T)
    {
        inOrder(T->lchild);
        cout<<T->data<<"  ";
        inOrder(T->rchild);
    }
}
void lastOrder(BitTree T)//�������
{
    if(T)
    {
        lastOrder(T->lchild);
        lastOrder(T->rchild);
        cout<<T->data<<"  ";
    }
}
void display(BitTree &T)//���ű�ʾ
{
    if(T)
    {
        cout<<T->data;
        if(T->lchild||T->rchild)
        {
            cout<<"(";
            display(T->lchild);
            if(T->rchild)
            {
                cout<<",";
                display(T->rchild);
                cout<<")";
            }
        }
    }
}
int main()
{
    BitTree T;
    createBitTree(T);
    cout<<"����";
    preOrder(T);
    cout<<endl<<"����";
    inOrder(T);
    cout<<endl<<"����";
    lastOrder(T);
    cout<<endl<<"���ű�ʾ��";
    display(T);
    cout<<endl;
    return 0;
}
