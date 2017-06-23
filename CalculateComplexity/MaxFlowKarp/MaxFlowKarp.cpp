// DijkstraMinPath.cpp : 定义控制台应用程序的入口点。
//埃德蒙斯卡谱算法
//20170424 六个小时
//版权所有
#include "stdafx.h"

#define MAXVEX 6//图的顶点的数目
#define MAXEDGE 9//图的边的数目
#define MAX 9999
#define INFINITY 32767
#define MAXCHILDNODE 10//队列需要的最大的存储空

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

//采用弗洛伊德算法计算可增道路，返回是否存在可增道路
bool CreateAddAblePath(MGraph G,int P[MAXVEX][MAXVEX],int D[MAXVEX][MAXVEX],int *addAblePath,char *vertex,int *side,int *ww)
{
	int i=0;
	int j=MAXVEX-1;
	//将G放在一个临时变量里面
	MGraph GCopy;
	GCopy=*(MGraph *)malloc(sizeof(MGraph));
	GCopy=G;
	//将G中存在的有向边的距离改为1
	for(int a=0;a<MAXVEX;a++)
	{
		for(int b=0;b<MAXVEX;b++)
		{
			if(G.edges[a][b]!=0&&G.edges[a][b]!=INFINITY)
			{
				G.edges[a][b]=1;
			}
		}
	}
	
	//求最短路径
	int v,w,k;
	for(v=0;v<G.numVertexes;++v)
	{
		for(w=0;w<G.numVertexes;++w)
		{
			D[v][w]=G.edges[v][w];
			P[v][w]=w;
		}
	}
	//第一次计算最短路径
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
	//再执行一遍，这里确实需要执行两次，可能是因为弗洛伊德算法是用来计算无向图的最短距离的
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
	
	//对可增道路做一次清空处理
	for(int x=0;x<MAXVEX;x++)
	{
		addAblePath[x]=-1;
	}
	bool flag=true;
	int next;
	int index=0;
	next=P[i][j];
	//创建可增道路
	if(next==MAX)
	{
		
	}
	else
	{
		
		addAblePath[index++]=i;
		while(next!=j)
		{
			
			addAblePath[index++]=next;
			next=P[next][j];
		}
	
		addAblePath[index++]=j;
	}
	//恢复G
	G=GCopy;


	if(addAblePath[0]==0&&addAblePath[1]==MAXVEX-1)
	{
		flag=false;
	}
	return flag;
}

//求出cfp的距离
int minPath(int *addAblePath,MGraph *G)
{ 
	int min=G->edges[0][1];
	for(int i=1;i<MAXVEX;i++)
	{
		if(addAblePath[i+1]==-1)
		{
			break;
		}
		int start=addAblePath[i];
		int end=addAblePath[i+1];
		if(G->edges[start][end]<min)
		{
			min=G->edges[start][end];
		}
	}
	return min;
}

//path[v]的值表示标号为v的顶点在生成的最短路径中前一个顶点的下标
//dist[v]表示起点到下标为v的终点的最短路劲
void main()
{
	int start=0;//起点的对应的下标，0表示A，1表示B，依次类推
	int end=MAXVEX-1;//终点的对应的下标，0表示A，1表示B，依次类推
	MGraph G;//图
	char vertex[]="SABCDT";
	int side[]={0,1,0,2,1,3,2,1,2,4,3,2,3,5,4,3,4,5};
	
	int w[]={16,13,12,4,14,9,20,7,4};
	
	int addAblePath[MAXVEX];//可增道路
	for(int i=0;i<MAXVEX;i++)
	{
		addAblePath[i]=-1;
	}
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	
	int path[MAXVEX][MAXVEX],dist[MAXVEX][MAXVEX];
	while(CreateAddAblePath(G,path,dist,addAblePath,vertex,side,w))//打印最短路径
	{
		
		int cfp=minPath(addAblePath,&G);
		//求出可增道路的真实长度
		int length=0;
		for(int i=0;i<MAXVEX;i++)
		{
			if(addAblePath[i]==-1)
			{
				break;
			}
			length++;
		}
		//for each edge in p
		for(int i=0;i<length-1;i++)
		{
			int start=addAblePath[i];
			int end=addAblePath[i+1];
			G.edges[start][end]=G.edges[start][end]-cfp;
			if(G.edges[start][end]==0)
			{
				G.edges[start][end]=INFINITY;
			}
			if(G.edges[end][start]==INFINITY)
			{
				G.edges[end][start]=cfp;
			}
			else
			{
				G.edges[end][start]=G.edges[end][start]+cfp;
				
			}
			
		}
		
		
		
		
	}
	printf("求出的最大流是:\n");
	int maxFlow=0;
	for(int i=0;i<MAXVEX;i++)
	{
		if(G.edges[MAXVEX-1][i]!=0&&G.edges[MAXVEX-1][i]!=INFINITY)
		{
			maxFlow+=G.edges[MAXVEX-1][i];
		}
	}
	printf("%2d",maxFlow);
	
}

