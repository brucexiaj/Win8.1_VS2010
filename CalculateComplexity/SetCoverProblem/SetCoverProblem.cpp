// SetCoverProblem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define VertexNumber 12//������
#define ChildSetNumber 6//�Ӽ�����

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
	int vertex[VertexNumber];//�����������ֵ
	int vertexFlag[VertexNumber]={0};//�����Ƿ��ѱ�����
	int childSetFlag[ChildSetNumber]={0};//�ü����Ƿ��ѱ����뵽�����
	int commonVertexBetweenChildSetAndRemainingVertex[ChildSetNumber]={0};//��ǰ������ʣ�ඥ��Ĺ��еĶ�������
	int childSetArray[ChildSetNumber][VertexNumber]={{1,2,3,4,5,6},{5,6,8,9},{1,4,7,10},{2,5,7,8,11},{3,6,9,12},{10,11}};
	
	for(int i=0;i<VertexNumber;i++)
	{
		vertex[i]=i+1;
	}
	while(!everyVertexCover(vertexFlag))
	{
		//�Թ��еĶ���������һ������Ĵ���
		for(int i=0;i<ChildSetNumber;i++)
		{
			commonVertexBetweenChildSetAndRemainingVertex[i]=0;
		}

		//���ÿ����ʱ���ڽ�����е��Ӽ�����ʣ�ඥ��Ĺ��ж�����
		for(int i=0;i<ChildSetNumber;i++)
		{
			int commonVertex=0;
			if(childSetFlag[i]==0)//�ü��ϻ����ٽ������
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
		//�ж��ĸ��Ӽ��Ϲ��ж������
		for(int i=0;i<ChildSetNumber;i++)
		{
			if(childSetFlag[i]==0&&commonVertexBetweenChildSetAndRemainingVertex[i]>commonMax)
			{
				commonMax=commonVertexBetweenChildSetAndRemainingVertex[i];
				childSetIndex=i;
			}
		}
	
		//��ʣ�ඥ����ɾ����Щ�����ǵĶ���
		for(int j=0;j<VertexNumber;j++)
		{
			int vertexValue=childSetArray[childSetIndex][j];
			if(vertexValue>0)
			{
				vertexFlag[vertexValue-1]=1;
			}
			
		}
		

		//,�������Ӽ��ϼ��뵽�������
		childSetFlag[childSetIndex]=1;
		
	}
	//��ӡ���
	printf("�����(�Ӽ��ϴ�S1��ʼ����):\n");
	for(int i=0;i<ChildSetNumber;i++)
	{
		if(childSetFlag[i]==1)
		{
			printf("S%d\n",i+1);
		}
	}
}


