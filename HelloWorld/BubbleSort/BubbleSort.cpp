// BubbleSort.cpp : �������̨Ӧ�ó������ڵ㡣
//ð������ð�������ѡ�������һ�������ǣ�ð�������ڱȽ���������Ԫ�صĴ�С��ύ������ѡ������ֻ�Ǽ�¼�½ϴ�Ļ��߽�С��Ԫ�����ڵ�λ�ã����ǲ�������
//������д
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

