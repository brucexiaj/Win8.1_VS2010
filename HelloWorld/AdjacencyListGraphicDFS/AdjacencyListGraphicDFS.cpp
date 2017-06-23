// AdjacencyListGraphicDFS.cpp : 定义控制台应用程序的入口点。
//邻接表表示的所有边的权值为1的无向图的深度优先遍历

#include "stdafx.h"


#define MAXVEX 6//图的顶点的数目
#define MAXSIZE 18
#define MAXEDGE 9
typedef struct node
{
	int adjvex;
	struct node *next;
}Anode;

typedef struct
{
	char vertex;
	Anode *link;
}Vnode;

typedef struct
{
	Vnode adjlist[MAXSIZE];
	int vexnum,edjenum;
}Adjgraph;

int visited[MAXSIZE]={0};

void CreateALGraph(Adjgraph *G,int n,int ed,char *ver,int *side)
{
	int i,s,d,k,m=0;
	Anode *p;
	G->vexnum=n;
	G->edjenum=ed;
	for(i=0;i<G->vexnum;i++)
	{
		G->adjlist[i].vertex=ver[i];
		G->adjlist[i].link=NULL;
	}
	for(k=0;k<G->edjenum;k++)
	{
		s=side[m++];
		d=side[m++];
		p=(Anode *)malloc(sizeof(Anode));
		p->adjvex=d;
		p->next=G->adjlist[s].link;
		G->adjlist[s].link=p;
		p=(Anode *)malloc(sizeof(Anode));
		p->adjvex=s;
		p->next=G->adjlist[d].link;
		G->adjlist[d].link=p;
	}
}

//实现邻接表表示的图的深度优先遍历的代码
void DFS(Adjgraph *G,int i)
{
	Anode *p;
	printf("%c",G->adjlist[i].vertex);
	visited[i]=1;
	p=G->adjlist[i].link;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			DFS(G,p->adjvex);
		p=p->next;
	}
}

void  DFSTraverse(Adjgraph *G)
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		visited[i]=0;
	}
	for(i=0;i<G->vexnum;i++)
	{
		if(visited[i]==0)
		{
			DFS(G,i);
		}
	}
}

void main()
{
	Adjgraph ag,*g;
	g=(Adjgraph *)malloc(sizeof(Adjgraph));
	char vertex[]="ABCDEFG";
	int side[]={0,1,0,3,1,2,1,3,1,4,2,4,3,4,3,5,4,5};
	CreateALGraph(g,MAXVEX,MAXEDGE,vertex,side);
	printf("Depth first traverse result:");
	DFSTraverse(g);
	
}