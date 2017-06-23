// AdjacencyMatrixGraphicBFS.cpp : �������̨Ӧ�ó������ڵ㡣
//����ͼ�ڽӾ����ʾ�Ŀ�����ȱ���
//���а�Ȩ��������

#include "stdafx.h"

#define MAXVEX 6//ͼ�Ķ������Ŀ
#define MAXEDGE 9//ͼ�ıߵ���Ŀ
#define MAXCHILDNODE 10//������Ҫ�����Ĵ洢�ռ�

typedef char VertexType;
typedef int EdgeType;

//����ͼ�Ľṹ
typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

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

//��������ͼ���ڽӾ����ʾ
//�������ߵ�Ȩֵ����1������ͼ
//�������㲻���ڱߣ�������������ʱͬһ�����㣬��ֵΪ0
void CreateMyGraph(MGraph *G,int n,int e,char *ver,int *side)
{
	int i,j,k,m=0;
	
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
		G->edges[i][j]=1;
		G->edges[j][i]=1;
	}
	
}

int visited[MAXVEX];

void BFS(MGraph G)
{
	for(int i=0;i<G.numVertexes;i++)
	{
		visited[i]=0;
	}
	MyQueue myQueue;
	InitialQueue(&myQueue);
	printf("%c",G.vexs[0]);
	visited[0]=1;
	EnterQueue(&myQueue,0);
	while(!IsEmpty(&myQueue))
	{
		int j=DeQueue(&myQueue);
		for(int i=0;i<G.numVertexes;i++)
		{
			if(G.edges[j][i]==1&&!visited[i])
			{
				printf("%c",G.vexs[i]);
				visited[i]=1;
				
				EnterQueue(&myQueue,i);
			}
		}
	}

}


void main()
{
	MGraph G;
	char vertex[]="ABCDEF";
	int side[]={0,1,0,3,1,2,1,3,1,4,2,4,3,4,3,5,4,5};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side);
	printf("Depth first traverse result;\n");
	BFS(G);
}