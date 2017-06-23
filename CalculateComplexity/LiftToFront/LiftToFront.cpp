// LiftToFront.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MAXVEX 6//图的顶点的数目
#define MAXEDGE 9//图的边的数目

#define INFINITY 32767

//定义链表的结构
typedef struct node
{
	int data;
	struct node *next;
}List;

//尾插法创建单链表
List *CreateListFromTail(int n,int *x)
{
	List *head,*s,*r;
	
	head=(List *)malloc(sizeof(List));
	if(head==NULL)
	{
		return head;
	}
	r=head;
	for(int i=0;i<n;i++)
	{
		s=(List *)malloc(sizeof(List));
		if(s==NULL)
		{
			return s;
		}
		s->data=*(x+i);
		r->next=s;
		r=s;
	}
	r->next=NULL;
	return head;
}

//在链表的尾部插入元素
void insertToTail(List *head,int x)
{
	List *s,*r;
	head=(List *)malloc(sizeof(List));
	r=head;
	s=(List *)malloc(sizeof(List));
	s->data=x;
	r->next=s;
	r=s;
	r->next=NULL;

}

//定义图的结构
typedef struct
{
	char vexs[MAXVEX];//顶点的名字
	int height[MAXVEX];//顶点的高度
	int e[MAXVEX];//顶点的过剩流
	int edges[MAXVEX][MAXVEX];//边的权重
	int edgesFlow[MAXVEX][MAXVEX];//边的流
	List * current[MAXVEX];//邻接链表中当前正在考虑的节点
	List * adjcentList[MAXVEX];//每个顶点的邻接链表
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
	//初始化顶点高度，过剩流为0
	for(i=0;i<G->numVertexes;i++)
	{
		G->height[i]=0;
		G->e[i]=0;
	}
	//初始化边的流为0,不存在的边预流为无穷
	for(i=0;i<G->numVertexes;i++)
	{
		for(j=0;j<G->numVertexes;j++)
		{
			if(G->edges[i][j]==0||G->edges[i][j]==INFINITY)
			{
				G->edgesFlow[j][i]=INFINITY;
			}
			else
			{
				G->edgesFlow[j][i]=0;
			}
		}
	}
	//初始化所有顶点的邻接链表和邻接链表中当前考虑的节点，s和t的这两项设为空
	
	//给邻接链表赋值
	for(i=0;i<G->numVertexes;i++)
	{
		for(j=0;j<G->numVertexes;j++)
		{
			if(G->edges[i][j]!=0||G->edges[i][j]!=INFINITY)
			{
				insertToTail(G->adjcentList[i],j);
				insertToTail(G->adjcentList[j],i);
			}
			
		}
	}
	G->current[0]=NULL;
	G->current[G->numVertexes-1]=NULL;
	//给当前链表赋值
	for(i=1;i<G->numVertexes-1;i++)
	{
		G->current[i]=G->adjcentList[i];
		G->current[i]->next=NULL;
	}
}

//初始化预流
void InitializePreflow(MGraph *G)
{
	G->height[0]=MAXVEX;
	for(int i=0;i<MAXVEX;i++)
	{
		if(G->edges[0][i]!=0&&G->edges[0][i]!=INFINITY)
		{
			G->edgesFlow[0][i]=G->edges[0][i];
			G->e[i]=G->edges[0][i];
			G->e[0]=G->e[0]-G->edges[0][i];
		}
	}

}

void Relabel(int u,MGraph *G)
{
	int min=INFINITY;
	for(int i=0;i<MAXVEX;i++)
	{
		if(G->edges[u][i]!=0&&G->edges[u][i]!=INFINITY)
		{
			int cfuv=G->edges[u][i]-G->edgesFlow[u][i];
			if(cfuv>0)
			{
				int vh=G->height[i];
				min=(vh<min)?vh:min;
			}
		}
	}
	G->height[u]=1+min;
}

void push(int u,int v,MGraph *G)
{
	int deta=((G->e[u])<(G->edges[u][v]-G->edgesFlow[u][v]))?G->e[u]:(G->edges[u][v]-G->edgesFlow[u][v]);
	if(G->edges[u][v]!=0&&G->edges[u][v]!=INFINITY)
	{
		G->edgesFlow[u][v]=G->edgesFlow[u][v]+deta;
	}
	else
	{
		G->edgesFlow[u][v]=G->edgesFlow[u][v]-deta;
	}
	G->e[u]=G->e[u]-deta;
	G->e[v]=G->e[v]-deta;
}
//排空顶点
void Discharge(int u,MGraph *G)
{
	while(G->e[u]>0)
	{
		int v=G->current[u]->data;
		if(v==NULL)
		{
			Relabel(u,G);
			G->current[u]=G->adjcentList[u];
			G->current[u]->next=NULL;
		}
		else if((G->edges[u][v]-G->edgesFlow[u][v]>0)&&(G->height[u]==G->height[v]+1))
		{
			push(u,v,G);
		}
		else
		{
			G->current[u]=G->adjcentList[u]->next;
		}
	}

}

void moveToTheFront(int u,List *head)
{
	//先从链表中删除这个节点
	List *prev;
	List *p=head->next;
	while(p&&p->data!=u)
	{
		prev=p;
		p=p->next;
	}
	prev->next=p->next;
	//将这个节点插入链表的头部
	List *prevFirstElement=head->next;
	head->next=p;
	p->next=prevFirstElement;

}
void main()
{
	
	MGraph G;//图
	char vertex[]="SABCDT";
	int side[]={0,1,0,2,1,3,2,1,2,4,3,2,3,5,4,3,4,5};
	int x[MAXVEX-2];
	for(int i=0;i<MAXVEX-2;i++)
	{
		x[i]=i+1;
	}
	int w[]={16,13,12,4,14,9,20,7,4};//每条边的容量
	
	
	//生成图
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	//初始化预流
	InitializePreflow(&G);
	//创建链表L
	List *L=CreateListFromTail(MAXVEX-2,x);
	List *temp=L;
	int u=temp->data;
	while(temp!=NULL)
	{
		int old_height=G.height[u];
		Discharge(u,&G);
		if(G.height[u]>old_height)
		{
			moveToTheFront(u,L);
			temp=L->next;
			u=temp->data;
		}
	}
	//计算最大流
	int maxFlow=0;
	for(int i=0;i<MAXVEX;i++)
	{
		if(G.edgesFlow[0][i]!=INFINITY)
		{
			maxFlow+=G.edgesFlow[0][i];
		}
	}
	printf("最大流的是:\n%4d",maxFlow);
	
}

