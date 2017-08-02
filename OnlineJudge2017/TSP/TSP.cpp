// TSP.cpp : 定义控制台应用程序的入口点。
/*
20170802
TsingHua Online Judge
https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=58
旅行商问题
思路：拓扑排序的过程中，对当前点的每一个邻接点，不断更新终点为该点的所有路径的最大村庄数，同时
更新整个地图的最大村庄数目。
!!!!!!!这个题目表明了在C语言中也可以实现类似动态数组（定义时不指定数组大小）的
机制——使用指针实现
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct TSPNode
{
	int nodeNumber;//点的编号，从1开始
	int inDegree;//入度
	int outDegree;//出度
	int *neighborNode;//所有邻接点的编号组成的数组（动态数组）
	int maxVillage;//终点为该点的所有路径的最大村庄数
	int index;//邻接点的索引
};

typedef TSPNode TNode;

int n,m=0;
int i,j,k=0;
int maxVillageNumber=0;
int start[1000001],end[1000001],empty[1000001];//empty存储当前的入度为0的店
TNode tNode[1000001];

int main()
{
	
	scanf("%d",&n);
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		scanf("%d",&start[i]);
		scanf("%d",&end[i]);
	}
	

	/*
	//从文件中获取数据
	FILE *file=fopen("in.txt","r");
	fscanf(file,"%d",&n);
	fscanf(file,"%d",&m);
	for(i=0;i<m;i++)
	{

			fscanf(file,"%d",&(start[i]));
			fscanf(file,"%d",&(end[i]));

	}
	fclose(file);
	*/

	for(i=1;i<=n;i++)
	{
		tNode[i].nodeNumber=i;
		tNode[i].inDegree=0;
		tNode[i].outDegree=0;
		tNode[i].maxVillage=1;
		tNode[i].index=0;
	}

	//计算所有的入度和出度
	for(i=0;i<m;i++)
	{
		tNode[start[i]].outDegree++;
		tNode[end[i]].inDegree++;
	}

	//计算邻接点编号数组需要的空间，并初始化该数组
	for(i=1;i<=n;i++)
	{
		tNode[i].neighborNode=(int *)malloc(tNode[i].outDegree*sizeof(int));

	}
	//计算出所有点的邻接点数组
	for(i=0;i<m;i++)
	{
		int startNodeNumber=start[i];
		tNode[startNodeNumber].neighborNode[tNode[startNodeNumber].index++]=end[i];
	}
	//将入读为0的点存入empty数组
	for(i=1;i<=n;i++)
	{
		if(tNode[i].inDegree==0)
		{
			empty[k++]=i;
		}
	}
	//遍历所有入度为0的点
	for(i=0;i<k;i++)
	{
		int number=empty[i];
		//遍历该点的所有邻接点
		//printf("%d\n",number);
		for(j=0;j<tNode[number].outDegree;j++)
		{
			int nextNode=tNode[number].neighborNode[j];
			//更新邻接点的最大村庄数
			if(tNode[number].maxVillage+1>tNode[nextNode].maxVillage)
			{
				tNode[nextNode].maxVillage=tNode[number].maxVillage+1;
			}
			//邻接点入度减去1，如果减为0，加入empty数组
			if(--tNode[nextNode].inDegree==0)
			{
				empty[k++]=nextNode;
			}
		}
		//实时更新总的最大村庄数
		if(tNode[number].maxVillage>maxVillageNumber)
		{
			maxVillageNumber=tNode[number].maxVillage;
		}
	}
	//printf("%d\n",tNode[3].maxVillage);
	printf("%d\n",maxVillageNumber);

	return 0;
}