// StraightInsertSort.cpp : �������̨Ӧ�ó������ڵ㡣
//ֱ�Ӳ�������
//������д
#include "stdafx.h"

void DirectInsertSort(int a[],int n)
{
	int temp=0,m=0;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(a[i]<=a[j])//�ҵ�����ĵط�
			{
				temp=a[i];//��ʱ����������ֵ
				for(m=i;m>j;m--)//����ƶ����ݿ�ʼ����
				{
					
					a[m]=a[m-1];
				}
				a[m]=temp;

			}
		}
	}
}
				
//���ϵĴ��룬�����ο�
void InsertSortASC(int s[],int n)
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		s[0]=s[i];
		j=i-1;
		while(s[0]<s[j]&&j>0)
		{
			s[j+1]=s[j];
			j--;
		}
		s[j+1]=s[0];
	}
}


void main()
{
	int a[]={3,2,6,-2,-4,22,0,4,-33,45,23,2};
	int b[]={-1,3,2,6,-2,-4,22,0,4,-33,45,23,2};//��ͷ��Ԫ����Ϊ�����ڣ������
	DirectInsertSort(a,12);
	InsertSortASC(b,12);
	for(int i=0;i<12;i++)
		printf("%3d",a[i]);
	printf("\n");
	for(int i=1;i<=12;i++)
		printf("%3d",b[i]);

}

