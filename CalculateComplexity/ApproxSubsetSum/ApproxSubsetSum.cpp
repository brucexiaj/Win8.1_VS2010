// ApproxSubsetSum.cpp : �������̨Ӧ�ó������ڵ㡣
//20170424 01:20:00

#include "stdafx.h"
#define T 308//Ŀ��ֵ
#define TrimAccuracy 0.05//�޼�����
#define Number 4//����Ԫ�ظ���
#define MaxListSize 16//��Ҫ����������size
//ð������
void BubbleSort(int a[],int n)
{
	int temp=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
//ȥ���ظ�Ԫ��
void removeRepeatedElement(int *mergeList)
{
	//����������ʵ����
	int length=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(mergeList[i]==-1)
		{
			break;
		}
		length++;
	}
	//�������ظ���Ԫ��ֵ��Ϊ-1
	for(int i=0;i<length;i++)
	{
		int compareElement=mergeList[i];
		for(int j=i+1;j<length;j++)
		{
			if(mergeList[j]==compareElement)
			{
				mergeList[j]==-1;
			}
		}
	}
	//�Ѳ���-1��Ԫ��ǰ��
	for(int i=0;i<length;i++)
	{
		if(mergeList[i]!=-1)
		{
			continue;
		}
		for(int j=i+1;j<length;j++)
		{
			if(mergeList[j]!=-1)//��ʼԪ�ص�ǰ��
			{
				mergeList[i]=mergeList[j];
				mergeList[j]=-1;
				break;//����j���ѭ������Ϊi�α���Ҫǰ����
			}
		}
	}
	//�����ʱ�����ʵ�ʳ���
	length=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(mergeList[i]==-1)
		{
			break;
		}
		length++;
	}
	//����
	BubbleSort(mergeList,length);

}

//�޼�����
void trimList(int *mergeList,int *trimedList)
{
	
	//����������ʵ����
	int length=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(mergeList[i]==-1)
		{
			break;
		}
		length++;
	}
	int lengthOfTrimList=1;
	trimedList[0]=mergeList[0];
	for(int i=1;i<length;i++)
	{
		int y=mergeList[i];
		double leftY=y/(1+TrimAccuracy);
		int j=0;
		for(j=0;j<lengthOfTrimList;j++)
		{
			int z=trimedList[j];
			
			if(leftY<=z&&z<=y)
			{
				
				break;
			}
		}
		//��������˻�û���ҵ���˵��û�п��Դ����
		if(j==lengthOfTrimList)
		{
			trimedList[lengthOfTrimList++]=y;
		}

	}
	
}

//ȥ����T���
void removeAndCopy(int *trimedList,int *initialList)
{
	int index=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(trimedList[i]==-1)
		{
			break;
		}
		else 
		{
			if(trimedList[i]<=T)
			{
				initialList[index++]=trimedList[i];
			}
			
		}
	}

}

//������Ԫ��
int maxOfTheList(int *List)
{
	int max=List[0];
	for(int i=0;i<MaxListSize;i++)
	{
		max=(List[i]>max)?List[i]:max;
	}
	return max;
}

void main()
{
	int set[Number]={104,102,201,101};
	int result[Number]={0};
	
	int initialList[MaxListSize];
	int incrementList[MaxListSize];
	int mergeList[MaxListSize];
	int trimedList[MaxListSize];
	for(int i=0;i<MaxListSize;i++)
	{
		initialList[i]=-1;
		incrementList[i]=-1;
		mergeList[i]=-1;
		trimedList[i]=-1;
	}
	//��ʼ��
	initialList[0]=0;
	for(int i=0;i<Number;i++)
	{
		
		//�����ʼ������ÿһ��Ԫ�ض�����set[i]���γɵ�����
		for(int j=0;j<MaxListSize;j++)
		{
			if(initialList[j]==-1)//Ԫ�ر�Ϊ-1ʱ��˵����ʵ�����鵽����ͽ�����
			{
				break;
			}
			incrementList[j]=initialList[j]+set[i];

		}
		
		//�ϲ���ʼ�����������������,��û��ȥ���ظ�Ԫ��
		int index=0;
		for(int m=0;m<MaxListSize;m++)
		{
			if(initialList[m]==-1)
			{
				break;
			}
			mergeList[index++]=initialList[m];
			
		}
		for(int n=0;n<MaxListSize;n++)
		{
			if(incrementList[n]==-1)
			{
				break;
			}
			mergeList[index++]=incrementList[n];
		}
		
		//ȥ���ظ�Ԫ�ز�����
		removeRepeatedElement(mergeList);
		
		
		//�޼�
		trimList(mergeList,trimedList);
		
		//ȥ����T���,ʣ�µĳ�ʼ����initialList
		removeAndCopy(trimedList,initialList);
		
		
	}
	
	//������е����ֵ��Ϊ���յĽ��
	int finalResult=maxOfTheList(initialList);
	printf("��ӽ�Ŀ��ֵ�ĺ���:%d",finalResult);
}

