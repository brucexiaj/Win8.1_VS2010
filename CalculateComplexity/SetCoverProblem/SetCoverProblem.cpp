// SetCoverProblem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define VertexNumber 12//顶点数
#define ChildSetNumber 6//子集合数

bool everyVertexCover(int *vertexFlag)
{
	for(int i=0;i<VertexNumber;i++)
	{
		if(vertexFlag[i]==0)
		{
			return false;
		}
	}
	return true;
}

void main()
{
	int vertex[VertexNumber];//顶点里面的数值
	int vertexFlag[VertexNumber]={0};//顶点是否已被覆盖
	int childSetFlag[ChildSetNumber]={0};//该集合是否已被加入到结果中
	int commonVertexBetweenChildSetAndRemainingVertex[ChildSetNumber]={0};//当前集合与剩余顶点的共有的顶点数量
	int childSetArray[ChildSetNumber][VertexNumber]={{1,2,3,4,5,6},{5,6,8,9},{1,4,7,10},{2,5,7,8,11},{3,6,9,12},{10,11}};
	
	for(int i=0;i<VertexNumber;i++)
	{
		vertex[i]=i+1;
	}
	while(!everyVertexCover(vertexFlag))
	{
		//对共有的顶点数进行一次清零的处理
		for(int i=0;i<ChildSetNumber;i++)
		{
			commonVertexBetweenChildSetAndRemainingVertex[i]=0;
		}

		//求出每个暂时不在结果集中的子集合与剩余顶点的共有顶点数
		for(int i=0;i<ChildSetNumber;i++)
		{
			int commonVertex=0;
			if(childSetFlag[i]==0)//该集合还不再结果集中
			{
				for(int j=0;j<VertexNumber;j++)
				{
					int vertexValue=childSetArray[i][j];
					if(vertexValue>0&&vertexFlag[vertexValue-1]==0)
					{
						commonVertex++;
					}
				}
				commonVertexBetweenChildSetAndRemainingVertex[i]=commonVertex;
				
			}
			
		}
		int childSetIndex=-1;
		int commonMax=0;
		//判断哪个子集合共有顶点最多
		for(int i=0;i<ChildSetNumber;i++)
		{
			if(childSetFlag[i]==0&&commonVertexBetweenChildSetAndRemainingVertex[i]>commonMax)
			{
				commonMax=commonVertexBetweenChildSetAndRemainingVertex[i];
				childSetIndex=i;
			}
		}
	
		//从剩余顶点中删除那些被覆盖的顶点
		for(int j=0;j<VertexNumber;j++)
		{
			int vertexValue=childSetArray[childSetIndex][j];
			if(vertexValue>0)
			{
				vertexFlag[vertexValue-1]=1;
			}
			
		}
		

		//,并将该子集合加入到结果集中
		childSetFlag[childSetIndex]=1;
		
	}
	//打印结果
	printf("结果是(子集合从S1开始计数):\n");
	for(int i=0;i<ChildSetNumber;i++)
	{
		if(childSetFlag[i]==1)
		{
			printf("S%d\n",i+1);
		}
	}
}


