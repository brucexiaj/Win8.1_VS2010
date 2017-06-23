// FloydMinPath.cpp : 定义控制台应用程序的入口点。

//弗洛伊德算法求解最短路径问题

#include "stdafx.h"

#define MAXVEX 6//图的顶点的数目
#define MAXEDGE 13//图的边的数目
#define MAX 9999
#define INFINITY 32767

//定义图的结构
typedef struct
{
	char vexs[MAXVEX];
	int edges[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

//建立有向图的邻接矩阵表示
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

	for(k=0;k<G->numEdges;k++)//给所有直接连接的顶点赋值
	{
		i=side[m++];
		j=side[m++];
		
		G->edges[i][j]=value[start];
		G->edges[j][i]=value[start];
		start++;
		
	}
	for(i=0;i<G->numVertexes;i++)//两个顶点之间没有直接连接的边，则置edges[i][j]为正无穷
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


//
void ShortestPathFloyd(MGraph G,int P[MAXVEX][MAXVEX],int D[MAXVEX][MAXVEX])
{
	int v,w,k;
	for(v=0;v<G.numVertexes;++v)
	{
		for(w=0;w<G.numVertexes;++w)
		{
			D[v][w]=G.edges[v][w];
			P[v][w]=w;
		}
	}
	
	for(v=0;v<G.numVertexes;++v)
	{
		for(w=0;w<G.numVertexes;++w)
		{
			for(k=0;k<G.numVertexes;++k)
			{
				if(D[v][w]>D[v][k]+D[k][w])
				{
					D[v][w]=D[v][k]+D[k][w];
					P[v][w]=P[v][k];
				}
			}
		}
	}
}
	
	
	


void PrintShortestPath(MGraph G,int P[][MAXVEX],int D[][MAXVEX],int i,int j)
{
	int next;
	printf("The lenght of the shortest path is");
	printf("(%c-%c):",i+65,j+65);
	printf("%d",D[i][j]);
	printf("\nThe shortest path:");
	next=P[i][j];
	if(next==MAX)
	{
		printf("%c to %c no path.\n",i+65,j+65);
	}
	else
	{
		printf("%c",i+65);
		while(next!=j)
		{
			printf("-%c",next+65);
			next=P[next][j];
		}
		printf("-%c\n",j+65);
	}
}
	




void main()
{
	//int start=0,end=11;
	int start=0,end=5;
	MGraph G;//图
	int path[MAXVEX][MAXVEX],dist[MAXVEX][MAXVEX];
	//char vertex[]="ABCDEFGHIJKL";
	char vertex[]="ABCDEF";
	//int side[]={0,1,1,2,2,3,3,4,4,5,1,6,6,7,3,6,3,8,4,7,4,8,5,9,8,9,9,10,10,11};
	int side[]={0,1,0,2,1,0,2,0,2,1,2,4,3,1,3,2,3,5,4,2,4,3,5,3,5,4};
	//int w[]={6,4,5,3,5,7,3,5,2,5,5,2,5,5,6};
	int w[]={1,1,1,1,1,1,1,1,1,1,1,1,1};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	ShortestPathFloyd(G,path,dist);//求出最短路径
	PrintShortestPath(G,path,dist,start,end);//打印最短路径
	
}



