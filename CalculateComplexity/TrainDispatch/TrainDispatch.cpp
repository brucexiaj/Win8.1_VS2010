// TrainDispatch.cpp : 定义控制台应用程序的入口点。
/**
清华大学OJ试题
https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=58
火车调度问题
20170726
这个只用一个小时就完成了，而且一次运行通过
**/

#include "stdafx.h"
#include <stdio.h>
int n,m=0;//车厢总数
int a[1600000];//记录输入的数据
int i=0,j=0;//遍历的索引
int current=0,carriage=1,former=0;
int index=0;
int dir[3200000];//记录最后打印的结果，1表示push，0表示pop
int b[160000];//记录在栈中的车厢
int stackTop=0;//栈顶的位置
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	//用1代表push,0代表pop
	for(i=0;i<n;i++)
	{
		current=a[i];
		//如果当前的车号大于上一次的，则该车厢还没有入栈
		if(current>former)
		{
			//在所有未入栈的车厢里面寻找,carriage表示当前未入栈的车厢里面车厢号最小的
			for(j=carriage;j<=n;j++)
			{
				dir[index++]=1;
				//如果当前的车厢号是，则它需要入栈，出栈两个操作
				if(current==j)
				{
					
					dir[index++]=0;
					carriage=j+1;
					break;
				}
				//如果当前的车厢号不是所求的，则入栈，同时车厢号后移
				else
				{
				
					b[stackTop++]=j;
					//如果栈中车厢的数量超出了限制，失败
					//至于这里为什么是m-1，想一下就明白了
					if(stackTop>m-1)
					{
						printf("No\n");
						return 0;
					}
				}
			}
			//如果移到最后一个车厢还是没有匹配到，判断失败并推出
			if(j==n&&i!=(n-1)&&stackTop==0)
			{
				printf("No\n");
				return 0;
			}
		}
		//如果当前的车号小于上一次的，则可能在栈里面
		else
		{
			//如果栈顶的车厢是所求的，弹出它
			if(current==b[--stackTop])
			{
				dir[index++]=0;
			}
			//不是的话匹配失败
			else
			{
				printf("No\n");
				return 0;
				
			}
		}
		former=current;
		
		
		
	}
	//打印最终的字符串结果
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

