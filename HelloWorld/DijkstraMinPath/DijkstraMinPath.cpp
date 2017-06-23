// DijkstraMinPath.cpp : 定义控制台应用程序的入口点。
//迪杰斯特拉算法求解最短路径问题

#include "stdafx.h"

#define MAXVEX 12//图的顶点的数目
#define MAXEDGE 15//图的边的数目
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


//final[v]表示目前下标为v的顶点有没有找到最短路径，1表示已经确认了最短路径
void ShortestPathDijkstra(MGraph G,int s,int path[],int dist[])
{
	int v,i,j,k,min;
	int final[MAXVEX];
	for(v=0;v<G.numVertexes;v++)//初始化数据
	{
		final[v]=0;             //将全部顶点初始化为未知最短路径状态
		dist[v]=G.edges[s][v];  //将于v0点有连线的顶点加上权值
		path[v]=MAX;			//初始化路径数组path为MAX
	}
	dist[s]=0;
	final[s]=1;
	/*开始主循环，每次求得v0到某个顶点的最短路径*/
	for(v=1;v<G.numVertexes;v++)
	{
		min=MAX;//离v0顶点的最近距离
		for(i=0;i<G.numVertexes;i++)//寻找离v0最近的顶点
		{
			if(!final[i]&&dist[i]<min)
			{
				k=i;
				min=dist[i];//w顶点离v0顶点更近
			}
		}
		final[k]=1;//将目前找到的最近的顶点置为1
		for(j=0;j<G.numVertexes;j++)//修正当前的最短路径及距离
		{
			//如果经过v顶点的最短路径比现在的更短
			if(!final[j]&&(min+G.edges[k][j]<dist[j]))
			{
				dist[j]=min+G.edges[k][j];//修改当前路径长度
				path[j]=k;
			}
		}
	}
}

void PrintShortestPath(MGraph G,int start,int end,int path[],int dist[])
{
	int j,k;
	int str[MAXVEX];
	
	printf("The lenght of the shortest path is:");
	printf("(%c-%c):%d\n",G.vexs[start],G.vexs[end],dist[end]);
	printf("The shortest path:");
	j=end;
	k=0;
	printf("%c-",start+65);
	while(path[j]!=MAX)
	{
		str[k]=path[j];
		j=path[j];
		k++;
	}
	k--;
	while(k>=0)
	{
		printf("%c-",str[k]+65);
		k--;
	}
	printf("%c",end+65);
}

//path[v]的值表示标号为v的顶点在生成的最短路径中前一个顶点的下标
//dist[v]表示起点到下标为v的终点的最短路劲
void main()
{
	int start=0;//起点的对应的下标，0表示A，1表示B，依次类推
	int end=11;//终点的对应的下标，0表示A，1表示B，依次类推
	MGraph G;//图
	int path[MAXVEX],dist[MAXVEX];
	char vertex[]="ABCDEFGHIJKL";
	int side[]={0,1,1,2,2,3,3,4,4,5,1,6,6,7,3,6,3,8,4,7,4,8,5,9,8,9,9,10,10,11};
	int w[]={6,4,5,3,5,7,3,5,2,5,5,2,5,5,6};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	ShortestPathDijkstra(G,start,path,dist);//求出最短路径
	PrintShortestPath(G,start,end,path,dist);//打印最短路径
	
}

