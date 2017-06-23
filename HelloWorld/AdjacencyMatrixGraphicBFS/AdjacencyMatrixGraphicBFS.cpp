// AdjacencyMatrixGraphicBFS.cpp : 定义控制台应用程序的入口点。
//无向图邻接矩阵表示的宽度优先遍历
//队列版权个人所有

#include "stdafx.h"

#define MAXVEX 6//图的顶点的数目
#define MAXEDGE 9//图的边的数目
#define MAXCHILDNODE 10//队列需要的最大的存储空间

typedef char VertexType;
typedef int EdgeType;

//定义图的结构
typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

//定义队列
typedef struct
{
	int member[MAXCHILDNODE];
	int head;
	int tail;
}MyQueue;

//判断队列是否为空
int IsEmpty(MyQueue *queue)
{
	return (queue->head==queue->tail)?1:0;
}

//进入队列的操作
void EnterQueue(MyQueue *queue,int i)
{
	queue->member[queue->tail++]=i;
}

//出队列操作
int DeQueue(MyQueue *queue)
{
	int temp=queue->member[queue->head];//从头部出队列
	queue->head++;
	return  temp;
}

//队列的初始化
void InitialQueue(MyQueue *queue)
{
	for(int i=0;i<MAXCHILDNODE;i++)
	{
		queue->member[i]=0;
	}
	queue->head=0;
	queue->tail=0;
}

//建立无向图的邻接矩阵表示
//条件：边的权值都是1，无向图
//两个顶点不存在边，或者两个顶点时同一个顶点，则赋值为0
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

	for(k=0;k<G->numEdges;k++)//给所有直接连接的顶点赋值
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