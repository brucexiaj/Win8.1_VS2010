// AINCodeProblem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MAXN 6//最大的维度
#define MAX MAXN*MAXN//最大的码数
#define NODES 6000//存储最多结构体数量
struct state
{
	int middle[MAXN][MAXN];
	int deepth;//深度
	int front;//是不是前沿节点
	int father;//父节点的下标
	int deleted;//1表示该节点已经作废
};

typedef struct state State;

//判断两个二维数组是否相等
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

//获得0在二维数组中的位置
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

//0上移
void moveUp(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2],int n)
{
	int x=zero[0];
	int y=zero[1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==x&&j==y)
			{
			}
			else
			{
				if(i==x-1&&j==y)
				{
				}
				else
				{
					tempArray[i][j]=start[i][j];
				}
			}
		}
	}
	tempArray[x][y]=start[x-1][y];
	tempArray[x-1][y]=start[x][y];
}

//0下移
void moveDown(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2],int n)
{
	int x=zero[0];
	int y=zero[1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==x&&j==y)
			{
			}
			else
			{
				if(i==x+1&&j==y)
				{
				}
				else
				{
					tempArray[i][j]=start[i][j];
				}
			}
		}
	}
	tempArray[x][y]=start[x+1][y];
	tempArray[x+1][y]=start[x][y];
}

//0左移
void moveLeft(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2],int n)
{
	int x=zero[0];
	int y=zero[1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==x&&j==y)
			{
			}
			else
			{
				if(i==x&&j==y-1)
				{
				}
				else
				{
					tempArray[i][j]=start[i][j];
				}
			}
		}
	}
	tempArray[x][y]=start[x][y-1];
	tempArray[x][y-1]=start[x][y];
}
//0右移
void moveRight(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2],int n)
{
	int x=zero[0];
	int y=zero[1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==x&&j==y)
			{
			}
			else
			{
				if(i==x&&j==y+1)
				{
				}
				else
				{
					tempArray[i][j]=start[i][j];
				}
			}
		}
	}
	tempArray[x][y]=start[x][y+1];
	tempArray[x][y+1]=start[x][y];
}

//计算两个八码状态之间的曼哈顿距离
int distance(int temp[MAXN][MAXN],int end[MAXN][MAXN],int n)
{
	int totalDistance=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(temp[i][j]==0)
			{
				continue;
			}
			else
			{
				int value=temp[i][j];
				for(int x=0;x<n;x++)
				{
					for(int y=0;y<n;y++)
					{
						if(value==end[x][y])
						{
							totalDistance=abs(i-x)+abs(j-y)+totalDistance;

						}
					}
				}
			}
		}
	}
	return totalDistance;
}

//判断是否有解
int solveAble(int s[MAXN][MAXN],int e[MAXN][MAXN],int n)
{
	int start[MAX]={0},end[MAX]={0};
	int count=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			start[count]=s[i][j];
			end[count++]=e[i][j];
		}
	}
	int startNumber=0,endNumber=0;
	//求初始状态的逆序数
	for(int i=0;i<n*n;i++)
	{
		for(int j=i+1;j<n*n;j++)
		{
			if(start[i]&&start[j]&&start[i]<start[j])
				startNumber++;
		}
	}
	//求结束状态的逆序数
	for(int i=0;i<n*n;i++)
	{
		for(int j=i+1;j<n*n;j++)
		{
			if(end[i]&&end[j]&&end[i]<end[j])
				endNumber++;
		}
	}
	if((startNumber+endNumber)%2==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//求出此时应该扩展的前沿节点的下标
int extendNodeIndex(State state[NODES],int n,int end[MAXN][MAXN],int currentIndex)
{
	int minCost=10000;
	int minFlag=0;
	for(int i=0;i<currentIndex;i++)
	{
		
		if(!state[i].deleted&&state[i].front&&minCost>=state[i].deepth+distance(state[i].middle,end,n))
		{
			minCost=state[i].deepth+distance(state[i].middle,end,n);
			minFlag=i;
		}
		
	}
	return minFlag;
}

//判断某个节点在结构体数组中是不是出现过，出现过则删掉他
int isRepeat(State state[NODES],int currentUsedIndex,State current,int n)
{
	for(int i=0;i<currentUsedIndex;i++)
	{
		if(!state[i].deleted&&!toTarget(state[i].middle,current.middle,n))//与之前的某一个节点重合
		{
			if(!state[i].front)//如果是非前沿节点
			{
				if(current.deepth<state[i].deepth)
				{
					state[i].deleted=1;
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				if(current.deepth<state[i].deepth)
				{
					state[i].deleted=1;
					return 0;
				}
				else
				{
					return 1;
				}
			}
			
		}
			
	}
	return 0;
}

//将State对象回复出厂模式
void toZero(State temp,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			temp.middle[i][j]=-1;
		}
	}
	temp.deepth=0;
	temp.front=0;
	temp.father=0;
}

//根据下标扩展前沿节点中的某一个，返回扩展后结构体数组的有效下标
int extendSpecificFrontier(int index,State state[NODES],int n,int currentUsedIndex)
{
	//获取0的位置
	int zero[2];
	locationOfZero(state[index].middle,zero,n);
	int x=zero[0];
	int y=zero[1];
	int deleteIndex=0;
	//上移
	if(x==0)
	{
	}
	else
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveUp(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
	}
	//下移
	if(x==n-1)
	{}
	else
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveDown(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
	}
	//左移
	if(y==0)
	{}
	else
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveLeft(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
	}
	//右移
	if(y==n-1)
	{}
	else
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveRight(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
		
	}
	//对父节点处理
	state[index].front=0;
	return currentUsedIndex;
}

//判断是否结束
int isResult(State state[NODES],int end[MAXN][MAXN],int currentUsedIndex,int n,int *re)
{
	//从刚刚扩展的四个节点中查询，看看是否有和目标节点相同的值
	for(int i=currentUsedIndex-1;i>=currentUsedIndex-4;i--)
	{
		if(!toTarget(state[i].middle,end,n))
		{
			*re=i;
			/*
			printf("**********************************\n");
			for(int k=0;k<n;k++)
			{
				for(int j=0;j<n;j++)
				{
					printf("%d\t",state[i].middle[k][j]);
				}
				printf("\n");
			}
			*/
			return 1;//结束
		}
			
	}
	return 0;
}


int main()
{
	int start[MAXN][MAXN],end[MAXN][MAXN];
	int i,j,k,a=0;
	int step=0;
	int currentUsedIndex=0;
	State myState[NODES];
	//初始化结构体数组
	for(i=0;i<NODES;i++)
	{
		for(k=0;k<MAXN;k++)
		{
			for(j=0;j<MAXN;j++)
			{
				myState[i].middle[k][j]=-1;
			}
		}
		myState[i].deepth=0;
		myState[i].front=0;
		myState[i].father=0;
		myState[i].deleted=0;
	}
	
	//从文件中获取数据
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
	fclose(file);

	//printf("to:%d\n",toTarget(start,end,n));
	//判断是否有解
	if(!solveAble(start,end,n))
	{
		printf("无解\n");
		exit(0);
	}

	//将初始状态加入到结构体数组中
	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
		{
			myState[0].middle[k][j]=start[k][j];
		}
	}
	myState[i].deepth=0;
	myState[i].front=1;
	myState[i].father=0;
	currentUsedIndex++;

	int re=0;
	while(!isResult(myState,end,currentUsedIndex,n,&re))
	{
		//求出此时应该扩展的前沿节点的下标
		int extendIndex=extendNodeIndex(myState,n,end,currentUsedIndex);
		//printf("extendIndex:%d\n",extendIndex);
		
		//扩展该节点
		currentUsedIndex=extendSpecificFrontier(extendIndex,myState,n,currentUsedIndex);
		/*
		int test=extendIndex;
		
		for(i=0;i<MAXN;i++)
		{
			for(j=0;j<MAXN;j++)
			{
				printf("%d\t",myState[test].middle[i][j]);
			}
			printf("\n");
		}
		printf("deepth:%d\n",myState[test].deepth);
		printf("front:%d\n",myState[test].front);
		
		printf("father:%d\n",myState[test].father);
		*/
		//if(step==9)
		//break;
		
	}
	//printf("步数:%d\n",step);
	//printf("re:%d\n",re);
	int printIndex[100];
	for(i=0;i<100;i++)
	{
		printIndex[i]=-1;
	}
	//计算从终点到起点的路径上的所有点的下标并存储
	while(myState[re].father!=0)
	{
		
		re=myState[re].father;
		printIndex[step]=re;
		step++;
	}
	//打印结果到文件中
	FILE *out=fopen("Npuzzle_out.txt","w");
	printf("共%d步\n",step+1);
	fprintf(out,"共%d步\n",step+1);
	//打印初始状态
	printf("初始状态\n");
	fprintf(out,"初始状态\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",myState[0].middle[i][j]);
			fprintf(out,"%d ",myState[0].middle[i][j]);
		}
		printf("\n");
		fprintf(out,"\n");
	}
	
	step=1;
	//打印每一个步骤
	for(k=99;k>=0;k--)
	{
		if(printIndex[k]!=-1)
		{
			printf("第%d步\n",step);
			fprintf(out,"第%d步\n",step);
			step++;
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					printf("%d ",myState[printIndex[k]].middle[i][j]);
					fprintf(out,"%d ",myState[printIndex[k]].middle[i][j]);
				}
				printf("\n");
				fprintf(out,"\n");
			}
		}
	}
	//打印终点状态
	printf("目标状态\n");
	fprintf(out,"目标状态\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",end[i][j]);
			fprintf(out,"%d ",end[i][j]);
		}
		printf("\n");
		fprintf(out,"\n");
	}
	
	fclose(out);
	return 0;
}

