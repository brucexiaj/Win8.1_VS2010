// DijkstraMinPath.cpp : �������̨Ӧ�ó������ڵ㡣
//������˹�����㷨
//20170424 ����Сʱ
//��Ȩ����
#include "stdafx.h"

#define MAXVEX 6//ͼ�Ķ������Ŀ
#define MAXEDGE 9//ͼ�ıߵ���Ŀ
#define MAX 9999
#define INFINITY 32767
#define MAXCHILDNODE 10//������Ҫ�����Ĵ洢��

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

//���ø��������㷨���������·�������Ƿ���ڿ�����·
bool CreateAddAblePath(MGraph G,int P[MAXVEX][MAXVEX],int D[MAXVEX][MAXVEX],int *addAblePath,char *vertex,int *side,int *ww)
{
	int i=0;
	int j=MAXVEX-1;
	//��G����һ����ʱ��������
	MGraph GCopy;
	GCopy=*(MGraph *)malloc(sizeof(MGraph));
	GCopy=G;
	//��G�д��ڵ�����ߵľ����Ϊ1
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
	
	//�����·��
	int v,w,k;
	for(v=0;v<G.numVertexes;++v)
	{
		for(w=0;w<G.numVertexes;++w)
		{
			D[v][w]=G.edges[v][w];
			P[v][w]=w;
		}
	}
	//��һ�μ������·��
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
	//��ִ��һ�飬����ȷʵ��Ҫִ�����Σ���������Ϊ���������㷨��������������ͼ����̾����
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
	
	//�Կ�����·��һ����մ���
	for(int x=0;x<MAXVEX;x++)
	{
		addAblePath[x]=-1;
	}
	bool flag=true;
	int next;
	int index=0;
	next=P[i][j];
	//����������·
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
	//�ָ�G
	G=GCopy;


	if(addAblePath[0]==0&&addAblePath[1]==MAXVEX-1)
	{
		flag=false;
	}
	return flag;
}

//���cfp�ľ���
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

//path[v]��ֵ��ʾ���Ϊv�Ķ��������ɵ����·����ǰһ��������±�
//dist[v]��ʾ��㵽�±�Ϊv���յ�����·��
void main()
{
	int start=0;//���Ķ�Ӧ���±꣬0��ʾA��1��ʾB����������
	int end=MAXVEX-1;//�յ�Ķ�Ӧ���±꣬0��ʾA��1��ʾB����������
	MGraph G;//ͼ
	char vertex[]="SABCDT";
	int side[]={0,1,0,2,1,3,2,1,2,4,3,2,3,5,4,3,4,5};
	
	int w[]={16,13,12,4,14,9,20,7,4};
	
	int addAblePath[MAXVEX];//������·
	for(int i=0;i<MAXVEX;i++)
	{
		addAblePath[i]=-1;
	}
	CreateMyGraph(&G,MAXVEX,MAXEDGE,vertex,side,w);
	
	int path[MAXVEX][MAXVEX],dist[MAXVEX][MAXVEX];
	while(CreateAddAblePath(G,path,dist,addAblePath,vertex,side,w))//��ӡ���·��
	{
		
		int cfp=minPath(addAblePath,&G);
		//���������·����ʵ����
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
	printf("������������:\n");
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

