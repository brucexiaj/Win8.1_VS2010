// BubbleSort.cpp : 定义控制台应用程序的入口点。
//冒泡排序，冒泡排序和选择排序的一个区别是：冒泡排序在比较相邻两个元素的大小后会交换，而选择排序只是记录下较大的或者较小的元素所在的位置，但是不做交换
//本人所写
#include "stdafx.h"

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

void main()
{
	int a[]={4,1,6,-1,22,0,8,1};
	BubbleSort(a,8);
	for(int i=0;i<8;i++)
	{
		printf("%3d",a[i]);
	}

}

