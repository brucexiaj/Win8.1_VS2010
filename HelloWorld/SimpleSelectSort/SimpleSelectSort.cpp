// SimpleSelectSort.cpp : 定义控制台应用程序的入口点。
//简单的选择排序
//本人所做20170312
#include "stdafx.h"


void SimpleSelectSort(int a[],int n)
{
	int min=0,min_loc=0,temp=0;
	for(int i=0;i<n;i++)
	{
		min=a[i];//当前最小值初始化
		min_loc=i;//当前最小值下标初始化
		for(int j=i+1;j<n;j++)
		{
			if(a[j]<min)
			{
				min=a[j];
				min_loc=j;//记录下当前最小值所在的下标
			}
		}
		//交换
		temp=a[i];
		a[i]=a[min_loc];
		a[min_loc]=temp;
	}
}
			
void main()
{
	int a[]={8,3,6,-1,34,7,3};
	SimpleSelectSort(a,7);
	for(int i=0;i<7;i++)
	{
		printf("%4d",a[i]);
	}
}

