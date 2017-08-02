// TSP.cpp : �������̨Ӧ�ó������ڵ㡣
/*
20170802
TsingHua Online Judge
https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=58
����������
˼·����������Ĺ����У��Ե�ǰ���ÿһ���ڽӵ㣬���ϸ����յ�Ϊ�õ������·��������ׯ����ͬʱ
����������ͼ������ׯ��Ŀ��
!!!!!!!�����Ŀ��������C������Ҳ����ʵ�����ƶ�̬���飨����ʱ��ָ�������С����
���ơ���ʹ��ָ��ʵ��
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct TSPNode
{
	int nodeNumber;//��ı�ţ���1��ʼ
	int inDegree;//���
	int outDegree;//����
	int *neighborNode;//�����ڽӵ�ı����ɵ����飨��̬���飩
	int maxVillage;//�յ�Ϊ�õ������·��������ׯ��
	int index;//�ڽӵ������
};

typedef TSPNode TNode;

int n,m=0;
int i,j,k=0;
int maxVillageNumber=0;
int start[1000001],end[1000001],empty[1000001];//empty�洢��ǰ�����Ϊ0�ĵ�
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
	//���ļ��л�ȡ����
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

	//�������е���Ⱥͳ���
	for(i=0;i<m;i++)
	{
		tNode[start[i]].outDegree++;
		tNode[end[i]].inDegree++;
	}

	//�����ڽӵ���������Ҫ�Ŀռ䣬����ʼ��������
	for(i=1;i<=n;i++)
	{
		tNode[i].neighborNode=(int *)malloc(tNode[i].outDegree*sizeof(int));

	}
	//��������е���ڽӵ�����
	for(i=0;i<m;i++)
	{
		int startNodeNumber=start[i];
		tNode[startNodeNumber].neighborNode[tNode[startNodeNumber].index++]=end[i];
	}
	//�����Ϊ0�ĵ����empty����
	for(i=1;i<=n;i++)
	{
		if(tNode[i].inDegree==0)
		{
			empty[k++]=i;
		}
	}
	//�����������Ϊ0�ĵ�
	for(i=0;i<k;i++)
	{
		int number=empty[i];
		//�����õ�������ڽӵ�
		//printf("%d\n",number);
		for(j=0;j<tNode[number].outDegree;j++)
		{
			int nextNode=tNode[number].neighborNode[j];
			//�����ڽӵ������ׯ��
			if(tNode[number].maxVillage+1>tNode[nextNode].maxVillage)
			{
				tNode[nextNode].maxVillage=tNode[number].maxVillage+1;
			}
			//�ڽӵ���ȼ�ȥ1�������Ϊ0������empty����
			if(--tNode[nextNode].inDegree==0)
			{
				empty[k++]=nextNode;
			}
		}
		//ʵʱ�����ܵ�����ׯ��
		if(tNode[number].maxVillage>maxVillageNumber)
		{
			maxVillageNumber=tNode[number].maxVillage;
		}
	}
	//printf("%d\n",tNode[3].maxVillage);
	printf("%d\n",maxVillageNumber);

	return 0;
}