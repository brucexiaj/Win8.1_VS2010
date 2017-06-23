// HelloWorld.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*���ڶ������Ĳ���
20170224
*/
#include "stdafx.h"
#define NodeNumber 7//�ڵ������
#define StackSize 20

//�������Ķ���
typedef struct node
{
	char data;
	struct node *lchild,*rchild;
}BTreeNode;

//ջ�Ķ���
typedef struct 
{
	BTreeNode data[StackSize];
	int top;
}SeqStack;

//ջ�ĳ�ʼ��
void InitStack(SeqStack *s)
{
	s->top=-1;
}

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(SeqStack *s)
{
	if(s->top==-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//�ж�ջ�Ƿ�Ϊ��
int StackFull(SeqStack *S)
{
	return S->top==StackSize-1;
}

//��ջ����
int Push(SeqStack *s,BTreeNode *bt)
{
	if(StackFull(s))
	{
		printf("Stack overflow");
		return 0;
	}
	s->top++;
	s->data[s->top]=*bt;
	return 1;
}

//��ջ����
int Pop(SeqStack *S,BTreeNode *x)
{
	if(StackEmpty(S))
	{
		printf("stack underflow");
		return 0;
	}

	*x=S->data[S->top];
	
	S->top--;
	return 1;
}
//ǰ�����������
void PreOrderTraverse(BTreeNode *bt)
{
	if(bt!=NULL)
	{
		printf("%c",bt->data);
    	PreOrderTraverse(bt->lchild);
	    PreOrderTraverse(bt->rchild);
	}
}

//ǰ��ǵݹ����
void PreOrderNR(BTreeNode *bt)
{
	SeqStack *s;
	BTreeNode *q;
	s=(SeqStack *)malloc(sizeof(SeqStack));
	InitStack(s);
	q=bt;
	while(q||!(StackEmpty(s)))
	{
		if(q)
		{
			printf("%c",q->data);
			Push(s,q);
			
			q=q->lchild;
		}
		else
		{
			q=(BTreeNode *)malloc(sizeof(BTreeNode));//��仰�����ҵ���һ������
			Pop(s,q);
		
			q=q->rchild;
		}
	}
}

//����ǵݹ����
void InOrderNR(BTreeNode *bt)
{
	SeqStack *s;
	BTreeNode *q;
	s=(SeqStack *)malloc(sizeof(SeqStack));
	InitStack(s);
	q=bt;
	while(q||!(StackEmpty(s)))
	{
		if(q)
		{
			
			Push(s,q);
			
			q=q->lchild;
		}
		else
		{
			q=(BTreeNode *)malloc(sizeof(BTreeNode));
			Pop(s,q);
			printf("%c",q->data);
			q=q->rchild;
		}
	}
}


//Ӧ�õݹ��㷨����������
void CreateBTree(BTreeNode **bt,char *p)
{
	char ch;
	static int n=1;
	ch=*(p+n);
	n++;
	if(ch=='#')
	{
		*bt=NULL;
	}
	else
	{
		*bt=(BTreeNode *)malloc(sizeof(BTreeNode));
		(*bt)->data=ch;
		CreateBTree(&((*bt)->lchild),p);
		CreateBTree(&((*bt)->rchild),p);
	}
}

//��������ַ��ڵ�λ�ڶ������еĲ���
void VisitTree(char ch,int level)
{
	switch(ch)
	{
	case 'A':
		printf("%c is at %d level at binary tree\n",ch,level);
		break;
	case 'B':
	case 'E':
		printf("%c is at %d level at binary tree\n",ch,level);
		break;
	case 'C':
	case 'D':
	case 'F':
	case 'G':
		printf("%c is at %d level at binary tree\n",ch,level);
		break;
	}
}
void PrintLevel(BTreeNode *bt,int level)
{
	if(bt)
	{
		VisitTree(bt->data,level);
		PrintLevel(bt->lchild,level+1);
		PrintLevel(bt->rchild,level+1);
	}
}

//���Ҷ��������ָ���Ĳ��
int SearchLevel(BTreeNode *bt,int level,char x)
{
	int n;
	if(bt)
	{
		if(bt->data==x)
			return level;
		n=SearchLevel(bt->lchild,level+1,x);
		if(n!=0)
			return  n;
		else
		    return n=SearchLevel(bt->rchild,level+1,x);
	}
	return 0;
}

//��������������
int BTreeDepth(BTreeNode *bt)
{
	int leftDep,rightDep;
	if(bt==NULL)
	{
		return 0;
	}
	else
	{
		leftDep=BTreeDepth(bt->lchild);
		rightDep=BTreeDepth(bt->rchild);

	}
	return leftDep>rightDep?(leftDep+1):(rightDep+1);
}

//�����������˫���ӽڵ�ĸ���
int TwoChildCount(BTreeNode *bt)
{
	if(bt==NULL)
	{
		return 0;
	}
	else if(bt->lchild==NULL||bt->rchild==NULL)
		return (TwoChildCount(bt->lchild)+TwoChildCount(bt->rchild));
	else
		return (TwoChildCount(bt->lchild)+TwoChildCount(bt->rchild)+1);
}

//�������Ĳ������
void LevelOrderTraverse(BTreeNode *bt)
{
	BTreeNode *q[NodeNumber+1]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	BTreeNode *temp[NodeNumber]={NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	printf("%c",bt->data);
	temp[0]=bt->lchild;
	temp[1]=bt->rchild;
	for(int i=0;i<3;i++)
	{
		int k=0;
		for(int j=0;j<NodeNumber;j++)
		{
			if(temp[j]!=NULL)
			{
				printf("%c",temp[j]->data);
				q[k++]=temp[j]->lchild;
				q[k++]=temp[j]->rchild;
			}
		}
		for(int n=0;n<NodeNumber;n++)
		{
				temp[n]=q[n];
		}
	}
}
void main()
{
	/*
	char str[]={'a','b','c','d','e','f','g'};
	BTreeNode *s;
	BTreeNode *q[NodeNumber];
	int j,n;
	for(int i=0;i<NodeNumber;i++)
	{
		s=(BTreeNode *)malloc(sizeof(BTreeNode));
		s->data=str[i];
		s->lchild=NULL;
		s->rchild=NULL;
		q[i]=s;
		if(i!=0)
		{
			j=(i-1)/2;
			if(i%2!=0)
				q[j]->lchild=s;
			else
				q[j]->rchild=s;
		}
		
	}
	
	printf("ǰ������Ľ����:\n");
	PreOrderTraverse(q[0]);
	*/

	/*int level=1;
	BTreeNode *bt=NULL;
	char str[]={' ','A','B','D','#','#','E','#','#','C','F','#','#','G','#','#'};
	char search='D';
	CreateBTree(&bt,str);
	printf("�ȸ������������Ľ���ǣ�");
	PreOrderTraverse(bt);
	printf("\n");
	PrintLevel(bt,level);
	printf("%c����ڶ������ĵ�%d��\n",search,SearchLevel(bt,level,search));
	printf("�������������%d\n",BTreeDepth(bt));
	printf("������˫���ӽڵ������%d\n",TwoChildCount(bt));
	printf("��������Ľ���ǣ�");
	LevelOrderTraverse(bt);
	*/

	BTreeNode *bt=NULL;
	char str[]={' ','A','B','D','#','#','E','#','#','C','F','#','#','G','#','#'};
	CreateBTree(&bt,str);
	printf("ǰ��ǵݹ����:\n");
	PreOrderNR(bt);
	printf("\n");  
	printf("����ǵݹ����\n");
	InOrderNR(bt);
}

