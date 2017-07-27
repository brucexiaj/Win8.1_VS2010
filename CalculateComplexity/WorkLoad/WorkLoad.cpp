// WorkLoad.cpp : 定义控制台应用程序的入口点。
//
/**清华大学oj试题
工作分配问题
回溯算法
这个算法不太好理解
链接：https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=1
**/
#include "stdafx.h"
#include "stdio.h"
int n,cost=0;
int x[100],c[100][100];

void work(int i,int count)
{
    if(i>n && count<cost)
	{
      cost = count;
      return ;
    }
    if(count<cost)
	{
      for(int j=1;j<=n;j++)
	  {
        if(x[j] == 0)
		{  
          x[j] = 1;  
          work(i+1,count+c[i][j]);  
          x[j] = 0;  
         }
	  }
	}
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
        scanf("%d",&c[i][j]);
        x[j] = 0;  
      }
      cost+=c[i][i];  
    }
    work(1,0);
    printf("%d\n",cost);
    return 0;
}