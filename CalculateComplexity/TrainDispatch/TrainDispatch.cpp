// TrainDispatch.cpp : �������̨Ӧ�ó������ڵ㡣
/**
�廪��ѧOJ����
https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=58
�𳵵�������
20170726
���ֻ��һ��Сʱ������ˣ�����һ������ͨ��
**/

#include "stdafx.h"
#include <stdio.h>
int n,m=0;//��������
int a[1600000];//��¼���������
int i=0,j=0;//����������
int current=0,carriage=1,former=0;
int index=0;
int dir[3200000];//��¼����ӡ�Ľ����1��ʾpush��0��ʾpop
int b[160000];//��¼��ջ�еĳ���
int stackTop=0;//ջ����λ��
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	//��1����push,0����pop
	for(i=0;i<n;i++)
	{
		current=a[i];
		//�����ǰ�ĳ��Ŵ�����һ�εģ���ó��ỹû����ջ
		if(current>former)
		{
			//������δ��ջ�ĳ�������Ѱ��,carriage��ʾ��ǰδ��ջ�ĳ������泵�����С��
			for(j=carriage;j<=n;j++)
			{
				dir[index++]=1;
				//�����ǰ�ĳ�����ǣ�������Ҫ��ջ����ջ��������
				if(current==j)
				{
					
					dir[index++]=0;
					carriage=j+1;
					break;
				}
				//�����ǰ�ĳ���Ų�������ģ�����ջ��ͬʱ����ź���
				else
				{
				
					b[stackTop++]=j;
					//���ջ�г�����������������ƣ�ʧ��
					//��������Ϊʲô��m-1����һ�¾�������
					if(stackTop>m-1)
					{
						printf("No\n");
						return 0;
					}
				}
			}
			//����Ƶ����һ�����ỹ��û��ƥ�䵽���ж�ʧ�ܲ��Ƴ�
			if(j==n&&i!=(n-1)&&stackTop==0)
			{
				printf("No\n");
				return 0;
			}
		}
		//�����ǰ�ĳ���С����һ�εģ��������ջ����
		else
		{
			//���ջ���ĳ���������ģ�������
			if(current==b[--stackTop])
			{
				dir[index++]=0;
			}
			//���ǵĻ�ƥ��ʧ��
			else
			{
				printf("No\n");
				return 0;
				
			}
		}
		former=current;
		
		
		
	}
	//��ӡ���յ��ַ������
	for(i=0;i<n*2;i++)
	{
		if(dir[i])
		{
			printf("push\n");
		}
		else
		{
			printf("pop\n");
		}
		
	}

	return 0;
}

