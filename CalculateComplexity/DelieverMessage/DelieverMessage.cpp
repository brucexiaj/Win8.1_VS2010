// DelieverMessage.cpp : 定义控制台应用程序的入口点。
/**
20170722
清华大学OJ试题https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=1
传纸条问题
双向动态规划
上传到OJ平台时，请去掉#include "stdafx.h"
**/


#include "stdio.h"
#include "stdafx.h"

int T[51][51][51][51];
int A[51][51];
int m = 0,n = 0,i = 0,j = 0,k = 0;

int max(int a,int b,int c,int d)
{
	int temp = a;
	if(b>temp)
	{
		temp = b;
	}
	if(c>temp)
	{
		temp = c;
	}
	if(d>temp)
	{
		temp = d;
	}
	return temp;
}
int main()
{
	scanf("%d",&m);  
	scanf("%d",&n); 
    for(i=1;i<=m;i++)  
    {  
        for(j=1;j<=n;j++)  
        {  
            scanf("%d",&A[i][j]);  
        }  
    } 
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			for(k=1;k<=m;k++)
			{
				if(i+j-k<1)
				{
					break;
				}
				else
				{
					T[i][j][k][i+j-k] = max(T[i-1][j][k-1][i+j-k],T[i-1][j][k][i+j-k-1],T[i][j-1][k-1][i+j-k],T[i][j-1][k][i+j-k-1])+A[i][j]+A[k][i+j-k];
					
					if(i==k)
					{
						T[i][j][k][i+j-k]-=A[i][j];
					}
				}
				
				
			}
		}
	}
	printf("%d\n",T[m][n][m][n]);
	return 0;

}

