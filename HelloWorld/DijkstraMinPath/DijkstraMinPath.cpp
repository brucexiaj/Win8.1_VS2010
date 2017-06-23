// DijkstraMinPath.cpp : �������̨Ӧ�ó������ڵ㡣
//�Ͻ�˹�����㷨������·������

#include "stdafx.h"

#define MAXVEX 12//ͼ�Ķ������Ŀ
#define MAXEDGE 15//ͼ�ıߵ���Ŀ
#define MAX 9999
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


//final[v]��ʾĿǰ�±�Ϊv�Ķ�����û���ҵ����·����1��ʾ�Ѿ�ȷ�������·��
void ShortestPathDijkstra(MGraph G,int s,int path[],int dist[])
{
	int v,i,j,k,min;
	int final[MAXVEX];
	for(v=0;v<G.numVertexes;v++)//��ʼ������
	{
		final[v]=0;             //��ȫ�������ʼ��Ϊδ֪���·��״̬
		dist[v]=G.edges[s][v];  //����v0�������ߵĶ������Ȩֵ
		path[v]=MAX;			//��ʼ��·������pathΪMAX
	}
	dist[s]=0;
	final[s]=1;
	/*��ʼ��ѭ����ÿ�����v0��ĳ����������·��*/
	for(v=1;v<G.numVertexes;v++)
	{
		min=MAX;//��v0������������
		for(i=0;i<G.numVertexes;i++)//Ѱ����v0����Ķ���
		{
			if(!final[i]&&dist[i]<min)
			{
				k=i;
				min=dist[i];//w������v0�������
			}
		}
		final[k]=1;//��Ŀǰ�ҵ�������Ķ�����Ϊ1
		for(j=0;j<G.numVertexes;j++)//������ǰ�����·��������
		{
			//�������v��������·�������ڵĸ���
			if(!final[j]&&(min+G.edges[k][j]<dist[j]))
			{
				dist[j]=min+G.edges[k][j];//�޸ĵ�ǰ·������
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

//path[v]��ֵ��ʾ���Ϊv�Ķ��������ɵ����·����ǰһ��������±�
//dist[v]��ʾ��㵽�±�Ϊv���յ�����·��
void main()
{
	int start=0;//���Ķ�Ӧ���±꣬0��ʾA��1��ʾB����������
	int end=11;//�յ�Ķ�Ӧ���±꣬0��ʾA��1��ʾB����������
	MGraph G;//ͼ
	int path[MAXVEX],dist[MAXVEX];
	char vertex[]="ABCDEFGHIJKL";
	int side[]={0,1,1,2,2,3,3,4,4,5,1,6,6,7,3,6,3,8,4,7,4,8,5,9,8,9,9,10,10,11};
	int w[]={6,4,5,3,5,7,3,5,2,5,5,2,5,5,6};
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	ShortestPathDijkstra(G,start,path,dist);//������·��
	PrintShortestPath(G,start,end,path,dist);//��ӡ���·��
	
}

