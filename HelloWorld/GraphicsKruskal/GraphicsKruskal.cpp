// GraphicsKruskal.cpp : �������̨Ӧ�ó������ڵ㡣
/**��С������
��³˹�����㷨
20170304
**/
#include "stdafx.h"


#define MAXVEX 16//ͼ�Ķ������Ŀ
#define MAXEDGE 19//ͼ�ıߵ���Ŀ
#define INFINITY 32767

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

/*Ӧ�ÿ�³˹�����㷨������С�������Ĵ���*/
typedef struct 
{
	int begin;
	int end;
	int weight;
}Edge;

//�����ߵ�Ȩֵ�Լ��ߵ�ͷ��β����ֵ
void Swapn(Edge *edges,int i,int j)
{
	int temp;
	temp=edges[i].begin;
	edges[i].begin=edges[j].begin;
	edges[j].begin=temp;
	temp=edges[i].end;
	edges[i].end=edges[j].end;
	edges[j].end=temp;
	temp=edges[i].weight;
	edges[i].weight=edges[j].weight;
	edges[j].weight=temp;
}

//��Ȩֵ��������
void Sort(Edge edges[],MGraph *G,char *ver)
{
	int i,j;
	for(i=0;i<G->numEdges;i++)
	{
		for(j=i+1;j<G->numEdges;j++)
		{
			if(edges[i].weight>edges[j].weight)
			{
				Swapn(edges,i,j);
			}
		}
	}
	
}

//�������Ӷ����β���±�
int Find(int *parent,int f)
{
	while(parent[f]>0)
	{
		f=parent[f];
	}
	return f;
}

//������С������
void MiniSpanTree_Kruskal(MGraph G,char *ver)
{
	int i,j,n,m;
	int k=0;
	int parent[MAXVEX];
	Edge edges[MAXEDGE];
	for(i=0;i<G.numVertexes-1;i++)
	{
		for(j=i+1;j<G.numVertexes;j++)
		{
			if(G.edges[i][j]<INFINITY)
			{
				edges[k].begin=i;
				edges[k].end=j;
				edges[k].weight=G.edges[i][j];
				k++;
			}
		}
	}
	Sort(edges,&G,ver);
	for(i=0;i<G.numVertexes;i++)
	{
		parent[i]=0;
	}
	printf("Minimum spanning tree\n");
	for(i=0;i<G.numEdges;i++)
	{
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		if(n!=m)
		{
			parent[n]=m;
			printf("(%c,%c):%d-",ver[edges[i].begin],ver[edges[i].end],edges[i].weight);
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

	
	printf("\n��С������:\n");
	MiniSpanTree_Kruskal(G,vertex);
}
