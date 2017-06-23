// HelloWorld.cpp : 定义控制台应用程序的入口点。
//
/*关于二叉树的操作
20170224
*/
#include "stdafx.h"
#define NodeNumber 7//节点的总数
#define StackSize 20

//二叉树的定义
typedef struct node
{
	char data;
	struct node *lchild,*rchild;
}BTreeNode;

//栈的定义
typedef struct 
{
	BTreeNode data[StackSize];
	int top;
}SeqStack;

//栈的初始化
void InitStack(SeqStack *s)
{
	s->top=-1;
}

//判断栈是否为空
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

//判断栈是否为满
int StackFull(SeqStack *S)
{
	return S->top==StackSize-1;
}

//入栈操作
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

//出栈操作
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
//前序遍历二叉树
void PreOrderTraverse(BTreeNode *bt)
{
	if(bt!=NULL)
	{
		printf("%c",bt->data);
    	PreOrderTraverse(bt->lchild);
	    PreOrderTraverse(bt->rchild);
	}
}

//前序非递归遍历
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
			q=(BTreeNode *)malloc(sizeof(BTreeNode));//这句话害的我调了一个中午
			Pop(s,q);
		
			q=q->rchild;
		}
	}
}

//中序非递归遍历
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


//应用递归算法创建二叉树
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

//输出各个字符节点位于二叉树中的层数
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

//查找二叉树结点指定的层次
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

//计算二叉树的深度
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

//计算二叉树中双孩子节点的个数
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

//二叉树的层序遍历
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
	
	printf("前序遍历的结果是:\n");
	PreOrderTraverse(q[0]);
	*/

	/*int level=1;
	BTreeNode *bt=NULL;
	char str[]={' ','A','B','D','#','#','E','#','#','C','F','#','#','G','#','#'};
	char search='D';
	CreateBTree(&bt,str);
	printf("先根遍历二叉树的结果是：");
	PreOrderTraverse(bt);
	printf("\n");
	PrintLevel(bt,level);
	printf("%c结点在二叉树的第%d层\n",search,SearchLevel(bt,level,search));
	printf("二叉树的深度是%d\n",BTreeDepth(bt));
	printf("二叉树双孩子节点个数是%d\n",TwoChildCount(bt));
	printf("层序遍历的结果是：");
	LevelOrderTraverse(bt);
	*/

	BTreeNode *bt=NULL;
	char str[]={' ','A','B','D','#','#','E','#','#','C','F','#','#','G','#','#'};
	CreateBTree(&bt,str);
	printf("前序非递归遍历:\n");
	PreOrderNR(bt);
	printf("\n");  
	printf("中序非递归遍历\n");
	InOrderNR(bt);
}

