// AdjacencyMatrixGraphicBFS.cpp : 定义控制台应用程序的入口点。
//无向图顶点覆盖近似算法
//没有用图的结构
//图的顶点时ABCDEFGHI
//图的边是AB AD AE BC BE CE CF CI DG EF EG EH FH　FI GH HI
//图有九个顶点，因为是近似算法，返回的结果一般是7条边
//版权个人所有

#include "stdafx.h"
#define EdgesNumber 16//边数目
#define VertexNumber 9//顶点数目

//选取E'中的随机一条边，返回这条边的索引
int createRandomEdge(int remainingEdgesNumber,int *edgesFlag,int edgesNumber)
{
	//计算随机数，生成0到remainingEdgesNumber之间的随机数
	
     time_t t;
     srand((unsigned) time(&t));
    
	 int randomNumber=rand()%remainingEdgesNumber;
	 int j=0;
	 //在剩余的边中，随机选择一条边，返回该边的索引
	 for(int i=0;i<edgesNumber;i++)
	 {
		 if(edgesFlag[i]==0)
		 {
			 
			 if(j==randomNumber)
			 {
				return i;
			 }
			 j++;

		 }
	 }
	 return -1;

}

//计算E'中剩余的边的数目
int calculateRemainingEdgesNumber(int *edgesFlag,int edgesNumber)
{
	int remainingEdgesNumber=0;
	for(int i=0;i<edgesNumber;i++)
	{
		if(edgesFlag[i]==0)//边没有被删除
		{
			remainingEdgesNumber++;
		}
	}
	return remainingEdgesNumber;
}

void main()
{
	
	
	char vertex[]="ABCDEFGHI";//9个顶点
	int side[]={0,1,0,3,0,4,1,2,1,4,2,4,2,5,2,8,3,6,4,5,4,6,4,7,5,7,5,8,6,7,7,8};//16S条边
	int edgesFlag[EdgesNumber]={0};
	int optimizeVertex[VertexNumber]={0};
	
	while(calculateRemainingEdgesNumber(edgesFlag,EdgesNumber)>0)//当E'中还存在边时
	{
		int remainingEdgesNumber=calculateRemainingEdgesNumber(edgesFlag,EdgesNumber);
		//printf("%d\n",remainingEdgesNumber);
		int randomEdgeIndex=createRandomEdge(remainingEdgesNumber,edgesFlag,EdgesNumber);
		//printf("%d\n",randomEdgeIndex);
		int startVertexIndex=side[randomEdgeIndex*2];
		//printf("%d\n",startVertexIndex);
		int endVertexIndex=side[randomEdgeIndex*2+1];
		//printf("%d\n",endVertexIndex);
		optimizeVertex[startVertexIndex]=1;
		optimizeVertex[endVertexIndex]=1;
		for(int i=0;i<EdgesNumber;i++)
		{
			if(side[2*i]==startVertexIndex||side[2*i]==endVertexIndex||side[2*i+1]==startVertexIndex||side[2*i+1]==endVertexIndex)
			{
				edgesFlag[i]=1;
				//printf("%d",i);
			}
		}
			//printf("\n");


	}
	printf("最小顶点覆盖的顶点是:\n");
	for(int i=0;i<VertexNumber;i++)
	{
		if(optimizeVertex[i]==1)
		{
			printf("%c\n",vertex[i]);
		}
	}

	

}