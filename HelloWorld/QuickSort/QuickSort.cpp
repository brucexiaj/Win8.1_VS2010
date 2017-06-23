// QuickSort.cpp : 定义控制台应用程序的入口点。
//
//快速排序算法，升序排序和降序排序
#include "stdafx.h"

//升序快排
int Partion(int r[],int low,int high)
{
	r[0]=r[low];
	while(low<high)
	{
		while(low<high&&r[high]>r[0])//只要high所在位置的值比枢纽值大，high值就一直减小
		{
			high--;
		}
		if(low<high)//当high所在的值比枢纽值小的时候，将low所在位置的值替换为high所在位置的值，这个时候low所在位置的值实际上已经记录在了枢纽位置
		{
			r[low]=r[high];
			low++;
			
		}
		while(low<high&&r[low]<r[0])
		{
			low++;
		}
		if(low<high)
		{
			r[high]=r[low];
			high--;
		}
	}
		r[low]=r[0];
		
		return low;//返回此时枢纽所在的位置
}


void QuickSortASC(int R[],int s,int t)
{
	int i;
	if(s<t)
	{
		i=Partion(R,s,t);
		QuickSortASC(R,s,i-1);
		QuickSortASC(R,i+1,t);
	}
}

//降序快排,书上的代码
void Swap(int *a,int *b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

void QuickSortDES(int k[],int s,int t)
{
	int i,j;
	if(s<t)
	{
		i=s;
		j=t+1;
		while(1)
		{
			do
			{
				i++;
			}while(!(k[s]>=k[i]||i==t));
			do
			{
				j--;
			}while(!(k[s]<=k[j]||j==s));
			if(i<j)
			{
				Swap(&k[i],&k[j]);
			}
			else
			{
				break;
			}
		}
		Swap(&k[s],&k[j]);
		QuickSortDES(k,s,j-1);
		QuickSortDES(k,j+1,t);
	}
}

//把原来的升序排序改一下就是降序排序了，本人所写
int MyPartion(int r[],int low,int high)
{
	r[0]=r[low];
	while(low<high)
	{
		while(low<high&&r[high]<r[0])
		{
			high--;
		}
		if(low<high)
		{
			r[low]=r[high];
			low++;
		}
		while(low<high&&r[low]>r[0])
		{
			low++;
		}
		if(low<high)
		{
			r[high]=r[low];
			high--;
		}
	}
		r[low]=r[0];
		return low;
}


void MyQuickSortDES(int R[],int s,int t)
{
	int i;
	if(s<t)
	{
		i=MyPartion(R,s,t);
		MyQuickSortDES(R,s,i-1);
		MyQuickSortDES(R,i+1,t);
	}
}
void main()
{
	int i;
	int a[7]={-1,6,2,15,8,9,3};
	int b[7]={-1,6,2,15,8,9,3};
	printf("升序快排的结果是:\n");
	QuickSortASC(a,1,6);
	for(i=1;i<7;i++)
		printf("%3d",a[i]);
	printf("\n");
	printf("降序快排的结果是：\n");
	MyQuickSortDES(b,1,6);
	//当然这里也可以用QuickSortDES(b,1,6);
	for(i=1;i<7;i++)
		printf("%3d",b[i]);
}



