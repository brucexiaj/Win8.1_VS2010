// AdjacencyMatrixGraphicDFS.cpp : �������̨Ӧ�ó������ڵ㡣
//
//�ڽӾ����ʾ��ͼ��������ȱ���
#include "stdafx.h"

#define MAXVEX 6//ͼ�Ķ������Ŀ
#define MAXEDGE 9//ͼ�ıߵ���Ŀ

typedef char VertexType;
typedef int EdgeType;

//����ͼ�Ľṹ
typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

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

