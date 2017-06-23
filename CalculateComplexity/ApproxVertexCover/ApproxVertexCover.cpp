// AdjacencyMatrixGraphicBFS.cpp : �������̨Ӧ�ó������ڵ㡣
//����ͼ���㸲�ǽ����㷨
//û����ͼ�Ľṹ
//ͼ�Ķ���ʱABCDEFGHI
//ͼ�ı���AB AD AE BC BE CE CF CI DG EF EG EH FH��FI GH HI
//ͼ�оŸ����㣬��Ϊ�ǽ����㷨�����صĽ��һ����7����
//��Ȩ��������

#include "stdafx.h"
#define EdgesNumber 16//����Ŀ
#define VertexNumber 9//������Ŀ

//ѡȡE'�е����һ���ߣ����������ߵ�����
int createRandomEdge(int remainingEdgesNumber,int *edgesFlag,int edgesNumber)
{
	//���������������0��remainingEdgesNumber֮��������
	
     time_t t;
     srand((unsigned) time(&t));
    
	 int randomNumber=rand()%remainingEdgesNumber;
	 int j=0;
	 //��ʣ��ı��У����ѡ��һ���ߣ����ظñߵ�����
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

//����E'��ʣ��ıߵ���Ŀ
int calculateRemainingEdgesNumber(int *edgesFlag,int edgesNumber)
{
	int remainingEdgesNumber=0;
	for(int i=0;i<edgesNumber;i++)
	{
		if(edgesFlag[i]==0)//��û�б�ɾ��
		{
			remainingEdgesNumber++;
		}
	}
	return remainingEdgesNumber;
}

void main()
{
	
	
	char vertex[]="ABCDEFGHI";//9������
	int side[]={0,1,0,3,0,4,1,2,1,4,2,4,2,5,2,8,3,6,4,5,4,6,4,7,5,7,5,8,6,7,7,8};//16S����
	int edgesFlag[EdgesNumber]={0};
	int optimizeVertex[VertexNumber]={0};
	
	while(calculateRemainingEdgesNumber(edgesFlag,EdgesNumber)>0)//��E'�л����ڱ�ʱ
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
	printf("��С���㸲�ǵĶ�����:\n");
	for(int i=0;i<VertexNumber;i++)
	{
		if(optimizeVertex[i]==1)
		{
			printf("%c\n",vertex[i]);
		}
	}

	

}