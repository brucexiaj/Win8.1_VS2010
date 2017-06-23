// AdjacencyMatrixGraphicDFS.cpp : 定义控制台应用程序的入口点。
//
//邻接矩阵表示的图的深度优先遍历
#include "stdafx.h"

#define MAXVEX 6//图的顶点的数目
#define MAXEDGE 9//图的边的数目

typedef char VertexType;
typedef int EdgeType;

//定义图的结构
typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

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

void DFS(MGraph G,int i)
{
	int j;
	visited[i]=1;
	printf("%c",G.vexs[i]);
	for(j=0;j<G.numVertexes;j++)
	{
		if(G.edges[i][j]==1&&!visited[j])
		{
			DFS(G,j);
		}
	}
}

void DFSTraverse(MGraph G)
{
	int i;
	for(i=0;i<G.numVertexes;i++)
	{
		visited[i]=0;
	}
	for(i=0;i<G.numVertexes;i++)
	{
		if(!visited[i])
			DFS(G,i);
	}
}

void main()
{
	MGraph G;
	char vertex[]="ABCDEF";
	int side[]={0,1,0,3,1,2,1,3,1,4,2,4,3,4,3,5,4,5};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side);
	printf("Depth first traverse result;\n");
	DFSTraverse(G);
}

