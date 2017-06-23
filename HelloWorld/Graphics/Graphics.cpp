// Graphics.cpp : 定义控制台应用程序的入口点。
//最小生成树算法
//普里姆算法

#include "stdafx.h"

#define MAXVEX 16//图的顶点的数目
#define MAXEDGE 19//图的边的数目
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

//输出图的邻接矩阵表示
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
				printf("  ∞");
			}
			else
			{
				printf("%4d",G->edges[i][j]);
			}
		}
		printf("\n");
	}
}

//应用普里姆算法生成最小生成树
void MiniSpanTree_Prinl(MGraph G,char *ver)
{
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
		printf("(%c,%c):%d-",ver[m],k+65,lowcost[k]);//打印结果
		lowcost[k]=0;
		for(j=1;j<G.numVertexes;j++)//更新lowcost和adjvex数组
		{
			if(lowcost[j]!=0&&G.edges[k][j]<lowcost[j])
			{
				lowcost[j]=G.edges[k][j];
				adjvex[j]=k;
			}
		}
	}
}
void main()
{
	MGraph G;
	char vertex[]="ABCDEFGHIJKLMNOP";
	int side[]={0,1,0,5,1,2,1,5,1,11,2,3,2,6,2,14,3,4,3,8,3,13,4,10,5,6,6,7,7,8,8,9,9,10,11,12,14,15};
	int w[]={695,814,514,349,511,413,516,1159,854,989,1625,1060,348,301,202,149,564,676,504};
	 
	//char vertex[]="ABCDEF";
	//int side[]={0,1,0,2,0,3,1,2,1,4,2,3,2,4,2,5,3,5,4,5};
	//int w[]={6,1,5,5,3,7,6,4,2,6};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);

	PrintMgraph(&G);
	printf("\n最小生成树:\n");
	MiniSpanTree_Prinl(G,vertex);

}

