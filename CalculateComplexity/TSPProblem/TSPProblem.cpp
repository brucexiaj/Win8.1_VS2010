// Graphics.cpp : �������̨Ӧ�ó������ڵ㡣
//��С�������㷨
//����ķ�㷨

#include "stdafx.h"

#define MAXVEX 8//ͼ�Ķ������Ŀ
#define MAXEDGE 28//ͼ�ıߵ���Ŀ
#define INFINITY 32767
#define NodeNumber 79//�ڵ������
#define StackSize 60
#define MAXCHILDNODE 30//������Ҫ�����Ĵ洢�ռ�
//�������Ķ���
typedef struct node
{
	char data;
	struct node *lchild,*rchild;
}BTreeNode;

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

void createBinaryTree(int *edges,char *p,BTreeNode **bt)
{

}

//�������
typedef struct
{
	int member[MAXCHILDNODE];
	int head;
	int tail;
}MyQueue;

//�ж϶����Ƿ�Ϊ��
int IsEmpty(MyQueue *queue)
{
	return (queue->head==queue->tail)?1:0;
}

//������еĲ���
void EnterQueue(MyQueue *queue,int i)
{
	queue->member[queue->tail++]=i;
}

//�����в���
int DeQueue(MyQueue *queue)
{
	int temp=queue->member[queue->head];//��ͷ��������
	queue->head++;
	return  temp;
}

//���еĳ�ʼ��
void InitialQueue(MyQueue *queue)
{
	for(int i=0;i<MAXCHILDNODE;i++)
	{
		queue->member[i]=0;
	}
	queue->head=0;
	queue->tail=0;
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

//����ͼ�Ľṹ
typedef struct
{
	char vexs[MAXVEX];
	int edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

//��������ͼ���ڽӾ����ʾ
void CreateMyGraph(MGraph *G,int n,int e,char *ver,int *side,int *value)
{
	int i,j,k,m=0;
	int start=0;
	G->numVertexes=n;
	G->numEdges=e;
	for(i=0;i<G->numVertexes;i++)
	{
		G->vexs[i]=ver[i];
	}
	for(i=0;i<G->numVertexes;i++)
	{
		for(j=0;j<G->numVertexes;j++)
		{
			G->edges[i][j]=0;
		}
	}

	for(k=0;k<G->numEdges;k++)//������ֱ�����ӵĶ��㸳ֵ
	{
		i=side[m++];
		j=side[m++];
		
		G->edges[i][j]=value[start];
		G->edges[j][i]=value[start];
		start++;
		
	}
	for(i=0;i<G->numVertexes;i++)//��������֮��û��ֱ�����ӵıߣ�����edges[i][j]Ϊ������
	{
		for(j=0;j<G->numVertexes;j++)
		{
			if(i!=j&&G->edges[j][i]==0)
			{
				G->edges[j][i]=INFINITY;
			}
		}
	}
}

//���ͼ���ڽӾ����ʾ
void PrintMgraph(MGraph *G)
{
	int i=0,j=0;
	char space=' ';
	printf("The adjacency matrix is \n");
	printf("%4c",space);
	for(i=0;i<G->numVertexes;i++)
	{
		printf("%4c",G->vexs[i]);
	}
	printf("\n");
	for(i=0;i<G->numVertexes;i++)
	{
		printf("%4c",G->vexs[i]);
		for(j=0;j<G->numVertexes;j++)
		{
			if(G->edges[i][j]==INFINITY)
			{
				printf("  ��");
			}
			else
			{
				printf("%4d",G->edges[i][j]);
			}
		}
		printf("\n");
	}
}

//Ӧ������ķ�㷨������С������
void MiniSpanTree_Prinl(MGraph G,char *ver,int *edgesInMiniTree)
{
	int index=0;
	int min=0,i=0,j=0,k=0,m=0;
	int adjvex[MAXVEX];
	int lowcost[MAXVEX];
	lowcost[0]=0;

	adjvex[0]=0;
	for(i=1;i<G.numVertexes;i++)
	{
		lowcost[i]=G.edges[0][i];
		adjvex[i]=0;
	}

	for(i=1;i<G.numVertexes;i++)
	{
		min=INFINITY;
		j=1;
		k=0;
		while(j<G.numVertexes)
		{
			if(lowcost[j]!=0&&lowcost[j]<min)
			{
				min=lowcost[j];
	
				k=j;
			}
			j++;
		}
		m=adjvex[k];
		printf("(%c,%c):%d-",ver[m],k+65,lowcost[k]);//��ӡ���
		edgesInMiniTree[index++]=m;
		edgesInMiniTree[index++]=k;
		lowcost[k]=0;
		for(j=1;j<G.numVertexes;j++)//����lowcost��adjvex����
		{
			if(lowcost[j]!=0&&G.edges[k][j]<lowcost[j])
			{
				lowcost[j]=G.edges[k][j];
				adjvex[j]=k;
			}
		}
	}
}
//ջ�Ķ���
typedef struct 
{
	int data[StackSize];
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
int Push(SeqStack *s,int a)
{
	if(StackFull(s))
	{
		printf("Stack overflow");
		return 0;
	}
	s->top++;
	s->data[s->top]=a;
	return 1;
}

//��ջ����
int Pop(SeqStack *S)
{
	if(StackEmpty(S))
	{
		printf("stack underflow");
		return -1;
	}

	int a=S->data[S->top];
	
	S->top--;
	return a;
}

int findLeftNodeIndex(int *edges,int nodeIndex,int edgesNumber)
{
	for(int i=0;i<edgesNumber*2;i=i+2)
	{
		if(edges[i]==nodeIndex)
		{
			return edges[i+1];
		}
	}
	return -1;
}

int findRightNodeIndex(int *edges,int nodeIndex,int edgesNumber)
{
	int k=0;
	for(int i=0;i<edgesNumber*2;i=i+2)
	{
		if(edges[i]==nodeIndex)
		{
			k++;
			if(k==2)
			{
				return edges[i+1];
			}
		}
	}
	return -1;
}
//ǰ��ǵݹ����
void PreOrderNR(int *edges,char *p,int edgesNumber,int vertexNumber)
{
	int startVertexIndex=0;
	int printedVertex=0;
	SeqStack *s;

	s=(SeqStack *)malloc(sizeof(SeqStack));
	InitStack(s);
	
	while(printedVertex<vertexNumber)
	{
		if(startVertexIndex!=-1)
		{
			printf("%c",*(p+startVertexIndex));
			printedVertex++;
			
			Push(s,startVertexIndex);
			startVertexIndex=findLeftNodeIndex(edges,startVertexIndex,edgesNumber);
			//printf("%d",*startVertexIndex);
		}
		else
		{
			//printf("%d",StackEmpty(s));
			//startVertexIndex=(int *)malloc(sizeof(int));//��仰�����ҵ���һ������
			startVertexIndex=Pop(s);
		//printf("%d\n",startVertexIndex);
			startVertexIndex=findRightNodeIndex(edges,startVertexIndex,edgesNumber);
			
		}
	}
}




void main()
{
	MGraph G;
	char vertex[]="ABCDEFGH";
	int edgesInMiniTree[56];
	for(int i=0;i<56;i++)
	{
		edgesInMiniTree[i]=-1;
	}
	int side[]={0,1,0,2,0,3,0,4,0,5,0,6,0,7,1,2,1,3,1,4,1,5,1,6,1,7,2,3,2,4,2,5,2,6,2,7,3,4,3,5,3,6,3,7,4,5,4,6,4,7,5,6,5,7,6,7};
	int w[]={20,32,20,32,28,45,41,14,28,32,20,40,22,42,45,32,51,22,14,20,28,41,14,14,36,20,22,41};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	//PrintMgraph(&G);
	printf("\n��С������:\n");
	
	MiniSpanTree_Prinl(G,vertex,edgesInMiniTree);
	printf("\n");
	int temp=0;
	for(int i=0;i<56;i++)
	{
		if(edgesInMiniTree[i]!=-1)
		{
			temp++;
		}
	}
	
	

	PreOrderNR(edgesInMiniTree,vertex,7,8);
	
	

	

}

