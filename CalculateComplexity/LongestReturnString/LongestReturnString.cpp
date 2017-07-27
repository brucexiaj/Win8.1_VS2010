// LongestReturnString.cpp : 定义控制台应用程序的入口点。
/**
鹅厂2017实习生面试题
最长回文字符串
方法：动态规划（最长公共序列问题）
见《算法导论》
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
	//获取输入的字符串
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

