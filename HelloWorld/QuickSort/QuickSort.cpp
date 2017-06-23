// QuickSort.cpp : �������̨Ӧ�ó������ڵ㡣
//
//���������㷨����������ͽ�������
#include "stdafx.h"

//�������
int Partion(int r[],int low,int high)
{
	r[0]=r[low];
	while(low<high)
	{
		while(low<high&&r[high]>r[0])//ֻҪhigh����λ�õ�ֵ����Ŧֵ��highֵ��һֱ��С
		{
			high--;
		}
		if(low<high)//��high���ڵ�ֵ����ŦֵС��ʱ�򣬽�low����λ�õ�ֵ�滻Ϊhigh����λ�õ�ֵ�����ʱ��low����λ�õ�ֵʵ�����Ѿ���¼������Ŧλ��
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
		
		return low;//���ش�ʱ��Ŧ���ڵ�λ��
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

//�������,���ϵĴ���
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

//��ԭ�������������һ�¾��ǽ��������ˣ�������д
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
	printf("������ŵĽ����:\n");
	QuickSortASC(a,1,6);
	for(i=1;i<7;i++)
		printf("%3d",a[i]);
	printf("\n");
	printf("������ŵĽ���ǣ�\n");
	MyQuickSortDES(b,1,6);
	//��Ȼ����Ҳ������QuickSortDES(b,1,6);
	for(i=1;i<7;i++)
		printf("%3d",b[i]);
}



