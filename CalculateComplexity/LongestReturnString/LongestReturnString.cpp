// LongestReturnString.cpp : �������̨Ӧ�ó������ڵ㡣
/**
�쳧2017ʵϰ��������
������ַ���
��������̬�滮��������������⣩
�����㷨���ۡ�
20170722
**/

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

char c[1000],d[1000];
int e[1000][1000];
int i=0,j=0,length=0;

int main()
{
	//��ȡ������ַ���
	scanf("%s",c);
	length=strlen(c);
	for(i=0;i<length;i++)
	{
		d[i]=c[length-i-1];
	}
	d[length]='0';
	
	for(i=1;i<=length;i++)
	{
		for(j=1;j<=length;j++)
		{
			if(c[i-1]==d[j-1])
			{
				e[i][j]=e[i-1][j-1]+1;
			}
			else
			{
				e[i][j]=e[i][j-1]>e[i-1][j]?e[i][j-1]:e[i-1][j];
			}
		}
	}
	printf("%d\n",length-e[length][length]);
	
	return 0;
}

