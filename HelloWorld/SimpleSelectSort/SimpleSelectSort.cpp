// SimpleSelectSort.cpp : �������̨Ӧ�ó������ڵ㡣
//�򵥵�ѡ������
//��������20170312
#include "stdafx.h"


void SimpleSelectSort(int a[],int n)
{
	int min=0,min_loc=0,temp=0;
	for(int i=0;i<n;i++)
	{
		min=a[i];//��ǰ��Сֵ��ʼ��
		min_loc=i;//��ǰ��Сֵ�±��ʼ��
		for(int j=i+1;j<n;j++)
		{
			if(a[j]<min)
			{
				min=a[j];
				min_loc=j;//��¼�µ�ǰ��Сֵ���ڵ��±�
			}
		}
		//����
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

