// ApproxSubsetSum.cpp : 定义控制台应用程序的入口点。
//20170424 01:20:00

#include "stdafx.h"
#define T 308//目标值
#define TrimAccuracy 0.05//修剪精度
#define Number 4//集合元素个数
#define MaxListSize 16//需要的数组的最大size
//冒泡排序
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
//去除重复元素
void removeRepeatedElement(int *mergeList)
{
	//求出数组的真实长度
	int length=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(mergeList[i]==-1)
		{
			break;
		}
		length++;
	}
	//把所有重复的元素值改为-1
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
	//把不是-1的元素前移
	for(int i=0;i<length;i++)
	{
		if(mergeList[i]!=-1)
		{
			continue;
		}
		for(int j=i+1;j<length;j++)
		{
			if(mergeList[j]!=-1)//开始元素的前移
			{
				mergeList[i]=mergeList[j];
				mergeList[j]=-1;
				break;//结束j层的循环，因为i游标需要前移了
			}
		}
	}
	//求出此时数组的实际长度
	length=0;
	for(int i=0;i<MaxListSize;i++)
	{
		if(mergeList[i]==-1)
		{
			break;
		}
		length++;
	}
	//排序
	BubbleSort(mergeList,length);

}

//修剪操作
void trimList(int *mergeList,int *trimedList)
{
	
	//求出数组的真实长度
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
		//如果到底了还没有找到，说明没有可以代替的
		if(j==lengthOfTrimList)
		{
			trimedList[lengthOfTrimList++]=y;
		}

	}
	
}

//去掉比T大的
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

//求出最大元素
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
	//初始化
	initialList[0]=0;
	for(int i=0;i<Number;i++)
	{
		
		//求出初始化数组每一个元素都增加set[i]后形成的数组
		for(int j=0;j<MaxListSize;j++)
		{
			if(initialList[j]==-1)//元素变为-1时，说明真实的数组到这里就结束了
			{
				break;
			}
			incrementList[j]=initialList[j]+set[i];

		}
		
		//合并初始化数组和自增的数组,还没有去除重复元素
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
		
		//去除重复元素并排序
		removeRepeatedElement(mergeList);
		
		
		//修剪
		trimList(mergeList,trimedList);
		
		//去掉比T大的,剩下的初始数组initialList
		removeAndCopy(trimedList,initialList);
		
		
	}
	
	//求出其中的最大值作为最终的结果
	int finalResult=maxOfTheList(initialList);
	printf("最接近目标值的和是:%d",finalResult);
}

