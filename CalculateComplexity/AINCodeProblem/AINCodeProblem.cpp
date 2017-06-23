// AINCodeProblem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MAXN 6
#define MAX MAXN*MAXN

int toTarget(int start[MAXN][MAXN],int end[MAXN][MAXN],int number)
{
	int temp=0;
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<number;j++)
		{
			if(start[i][j]!=end[i][j])
				temp++;
		}
	}
	return temp;
}

void locationOfZero(int start[MAXN][MAXN],int zero[2],int number)
{
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<number;j++)
		{
			if(start[i][j]==0)
			{
				zero[0]=i;
				zero[1]=j;
				return;
			}
		}
	}
}

int moveDirection(int dir[4],int zero[2],int number)
{
	int randomArray[4];
	for(int i=0;i<4;i++)
	{
		randomArray[i]=-1;
	}
	int max=dir[0];
	int flag=0;
	int count=0;
	int ran=0;
	for(int i=1;i<4;i++)
	{
		if(max<=dir[i])
		{
			max=dir[i];
			flag=i;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(dir[i]!=1||dir[i]!=-1)
		{
			count++;
		}
		if(dir[i]!=-11)
		{
			randomArray[ran++]=i;
		}
	}
	if(count==4)
	{
		int randomNumber=rand()%ran;
		printf("randomnumber:%d,ran:%d\n",randomNumber,ran);
		return randomArray[randomNumber];
	}
	return flag;
}

void move(int start[MAXN][MAXN],int dir,int zero[2])
{
	int x=zero[0];
	int y=zero[1];
	switch(dir)
	{
	case 0:start[x][y]=start[x-1][y];
		   start[x-1][y]=0;
		   break;
	case 1:start[x][y]=start[x+1][y];
		   start[x+1][y]=0;
		   break;
	case 2:start[x][y]=start[x][y-1];
		   start[x][y-1]=0;
		   break;
	case 3:start[x][y]=start[x][y+1];
		   start[x][y+1]=0;
		   break;
	default:break;
	}
}
int main()
{
	int start[MAXN][MAXN],end[MAXN][MAXN];
	int i,j,k=0;
	int step=0;
	for(i=0;i<MAXN;i++)
	{
		for(j=0;j<MAXN;j++)
		{
			start[i][j]=-1;
			end[i][j]=-1;
		}
	}
	FILE *file=fopen("npuzzle_in.txt","r");
	int n=0;
	fscanf(file,"%d",&n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(file,"%d",&(start[i][j]));
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(file,"%d",&(end[i][j]));
		}
	}

	/*
	for(i=0;i<MAXN;i++)
	{
		for(j=0;j<MAXN;j++)
		{
			printf("%d\t",start[i][j]);
		}
	}
	printf("\n");
	for(i=0;i<MAXN;i++)
	{
		for(j=0;j<MAXN;j++)
		{
			printf("%d\t",end[i][j]);
		}
	}
	*/
	fclose(file);
	//printf("to:%d\n",toTarget(start,end,n));
	int direction[4]={0};
	int zero[2]={0};
	int beforeChange=0,afterChange=0;
	while(toTarget(start,end,n)!=0)
	{
		locationOfZero(start,zero,n);
		int x=zero[0];
		int y=zero[1];
		
		//printf("i:%d\tj:%d\n",zero[0],zero[1]);
		//上移
		if(x==0)
		{
			direction[0]=1000;
		}
		else
		{
			if(start[x-1][y]==end[x-1][y])
				beforeChange++;
			if(start[x-1][y]==end[x][y])
				afterChange++;
			direction[0]=afterChange-beforeChange;
		}
		//下移
		if(x==n-1)
		{
			direction[1]=1000;
		}
		else
		{
			beforeChange=0;
			afterChange=0;
			
			if(start[x+1][y]==end[x+1][y])
				beforeChange++;
			
			if(start[x+1][y]==end[x][y])
				afterChange++;
			direction[1]=afterChange-beforeChange;
		}
		//左移
		if(y==0)
		{
			direction[2]=1000;
		}
		else
		{
			beforeChange=0;
			afterChange=0;
			
			if(start[x][y-1]==end[x][y-1]&&end[x][y-1]!=0)
				beforeChange++;
			
			if(start[x][y-1]==end[x][y])
				afterChange++;
			direction[2]=afterChange-beforeChange;
		}
		//右移
		if(y==n-1)
		{
			direction[3]=1000;
		}
		else
		{
			beforeChange=0;
			afterChange=0;
			
			if(start[x][y+1]==end[x][y+1])
				beforeChange++;
			
			if(start[x][y+1]==end[x][y])
				afterChange++;
			direction[3]=afterChange-beforeChange;
		}
		printf("d0:%d\td1:%d\td2:%d\td3:%d\n",direction[0],direction[1],direction[2],direction[3]);
		int beatDirection=moveDirection(direction,zero,n);
		move(start,beatDirection,zero);
		printf("beatDirection:%d\n",beatDirection);
		for(i=0;i<MAXN;i++)
		{
			for(j=0;j<MAXN;j++)
			{
				printf("%d\t",start[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		//if(step==6)
			//break;
		step++;
	}
	printf("步数:%d\n",step);
	return 0;
}

