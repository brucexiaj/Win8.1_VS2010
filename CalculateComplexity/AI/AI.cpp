// AINCodeProblem.cpp : 定义控制台应用程序的入口点。
/**
人工智能实验——N码问题
夏军20170616
输入：Npuzzle_in.txt
输出：Npuzzle_out.txt
如果程序运行异常请减小宏NODES的值
**/

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 6//最大的维度
#define MAX MAXN*MAXN//最大的码数
#define NODES 150000//存储最多结构体数量
struct state
{
	int middle[MAXN][MAXN];
	int deepth;//深度
	int front;//是不是前沿节点
	int father;//父节点的下标
	
};

typedef struct state State;

int n=0;//码数
State state[NODES];//存储所有节点的结构体数组
int end[MAXN][MAXN];


//判断两个二维数组是否相等，相等返回1
int isArrayEqual(int array1[MAXN][MAXN],int array2[MAXN][MAXN])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(array1[i][j]!=array2[i][j])
				return 0;
		}
	}
	return 1;
}

//获得0在二维数组中的位置
void locationOfZero(int start[MAXN][MAXN],int zero[2])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
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
void moveUp(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			tempArray[i][j]=start[i][j];
		}
	}
	tempArray[zero[0]][zero[1]]=tempArray[zero[0]-1][zero[1]];
	tempArray[zero[0]-1][zero[1]]=0;
}

//0下移
void moveDown(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			tempArray[i][j]=start[i][j];
		}
	}
	tempArray[zero[0]][zero[1]]=tempArray[zero[0]+1][zero[1]];
	tempArray[zero[0]+1][zero[1]]=0;
}

//0左移
void moveLeft(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			tempArray[i][j]=start[i][j];
		}
	}
	tempArray[zero[0]][zero[1]]=tempArray[zero[0]][zero[1]-1];
	tempArray[zero[0]][zero[1]-1]=0;
}
//0右移
void moveRight(int start[MAXN][MAXN],int tempArray[MAXN][MAXN],int zero[2])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			tempArray[i][j]=start[i][j];
		}
	}
	tempArray[zero[0]][zero[1]]=tempArray[zero[0]][zero[1]+1];
	tempArray[zero[0]][zero[1]+1]=0;
}

//计算两个八码状态之间的曼哈顿距离(第一种启发式，本程序实际使用的启发式)
int distance(int temp[MAXN][MAXN])
{
	int totalDistance=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(temp[i][j]!=0)
			{
				int value=temp[i][j];
				for(int x=0;x<n;x++)
				{
					for(int y=0;y<n;y++)
					{
						if(value==end[x][y])
						{
							totalDistance=abs(i-x)+abs(j-y)+totalDistance;
							break;
						}
					}
				}
			}
		}
	}
	return totalDistance;
}

//计算两个二维数组对应元素不相等的总数目（第二种启发式，本程序测试过程中使用）
int falseLocationNumber(int start[MAXN][MAXN])
{
	int temp=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(start[i][j]!=end[i][j])
				temp++;
		}
	}
	return temp;
}

//判断是否有解，用逆序数的改加上0的位置的改变综合考虑
//返回0表示无解
int solveAble(int s[MAXN][MAXN])
{
	int startArray[MAX]={0},endArray[MAX]={0};
	int count=0;
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			startArray[count]=s[i][j];
			endArray[count++]=end[i][j];
		}
	}
	int startNumber=0,endNumber=0;
	//求初始状态的逆序数（0也考虑在内）
	for(i=0;i<n*n;i++)
	{
		for(j=i+1;j<n*n;j++)
		{
			if(startArray[i]<startArray[j])
				startNumber++;
		}
	}
	//求结束状态的逆序数（0也考虑在内）
	for(i=0;i<n*n;i++)
	{
		for(j=i+1;j<n*n;j++)
		{
			if(endArray[i]<endArray[j])
				endNumber++;
		}
	}
	//求开始的0与结束的0之间的曼哈顿距离
	int startZero[2]={0,0};
	int endZero[2]={0,0};
	locationOfZero(s,startZero);
	locationOfZero(end,endZero);
	int distanceOfZero=abs(startZero[0]-endZero[0])+abs(startZero[1]-endZero[1]);
	if((startNumber+endNumber+distanceOfZero)%2==0)
	{
		return 1;//有解
	}
	else
	{
		return 0;
	}
}

//求出此时应该扩展的前沿节点的下标
//整个程序中，对于不同的启发式，代码只有这里是不一样的
int extendNodeIndex(int currentIndex)
{
	int minCost=10000;
	int minFlag=0;
	//这里采用的是曼哈顿距离和的启发式
	for(int i=0;i<currentIndex;i++)
	{
		
		if(state[i].front&&minCost>=state[i].deepth+distance(state[i].middle))
		{
			minCost=state[i].deepth+distance(state[i].middle);
			minFlag=i;
		}
		
	}
	
	
	/*	这里是不在位的棋子数的启发式
	for(int i=0;i<currentIndex;i++)
	{
		
		if(state[i].front&&minCost>=state[i].deepth+falseLocationNumber(state[i].middle))
		{
			minCost=state[i].deepth+falseLocationNumber(state[i].middle);
			minFlag=i;
		}
		
	}
	*/
	return minFlag;
}

//判断某个节点在结构体数组中是不是出现过，出现过则删掉他
//返回1表示删除该节点
int isRepeat(int currentUsedIndex,State current)
{
	for(int i=0;i<currentUsedIndex;i++)
	{
		if(isArrayEqual(state[i].middle,current.middle))//与之前的某一个节点重合
		{
			if(!state[i].front)//如果与非前沿节点重合，删除该节点
			{
				return 1;
			}
			else
			{
				if(current.deepth<state[i].deepth)//如果与前沿节点重合而且它的深度比前沿节点小，删除前沿节点
				{
					state[i].front=0;
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
void toZero(State temp)
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
int extendSpecificFrontier(int index,int currentUsedIndex)
{
	//获取0的位置
	int zero[2]={0};
	locationOfZero(state[index].middle,zero);
	//上移
	if(zero[0]!=0)
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveUp(state[index].middle,state[currentUsedIndex].middle,zero);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
	}
	//下移
	if(zero[0]!=n-1)
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveDown(state[index].middle,state[currentUsedIndex].middle,zero);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
	}
	//左移
	if(zero[1]!=0)
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveLeft(state[index].middle,state[currentUsedIndex].middle,zero);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
	}
	//右移
	if(zero[1]!=n-1)
	{
		//分配一个节点给新的扩展
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveRight(state[index].middle,state[currentUsedIndex].middle,zero);
		//判断这个节点是不是之前出现过，出现过则删掉它
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
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
int isResult(int currentUsedIndex,int *re)
{
	//从刚刚扩展的四个节点中查询，看看是否有和目标节点相同的值
	for(int i=currentUsedIndex-1;i>=currentUsedIndex-4;i--)
	{
		if(isArrayEqual(state[i].middle,end))
		{
			*re=i;
			return 1;//结束
		}
			
	}
	return 0;
}


int main()
{
	
    clock_t startTime, finishTime;
    double  duration;
    startTime = clock();

	int start[MAXN][MAXN];
	int i,j,k,a=0;
	int step=0;
	int currentUsedIndex=0;
	//初始化结构体数组
	for(i=0;i<NODES;i++)
	{
		for(k=0;k<MAXN;k++)
		{
			for(j=0;j<MAXN;j++)
			{
				state[i].middle[k][j]=-1;
			}
		}
		state[i].deepth=0;
		state[i].front=0;
		state[i].father=0;
		
	}
	
	//从文件中获取数据
	FILE *file=fopen("Npuzzle_in.txt","r");
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
	if(!solveAble(start))
	{
		printf("无解\n");
		exit(0);
	}

	//将初始状态加入到结构体数组中
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			state[0].middle[i][j]=start[i][j];
		}
	}
	state[0].front=1;
	currentUsedIndex++;

	int re=0;
	while(!isResult(currentUsedIndex,&re))
	{
		//求出此时应该扩展的前沿节点的下标
		int extendIndex=extendNodeIndex(currentUsedIndex);
		
		//扩展该节点
		currentUsedIndex=extendSpecificFrontier(extendIndex,currentUsedIndex);
		
		
	}
	
	int printIndex[100];
	for(i=0;i<100;i++)
	{
		printIndex[i]=-1;
	}
	//计算从终点到起点的路径上的所有点的下标并存储
	while(state[re].father!=0)
	{
		
		re=state[re].father;
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
			printf("%d ",state[0].middle[i][j]);
			fprintf(out,"%d ",state[0].middle[i][j]);
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
					printf("%d ",state[printIndex[k]].middle[i][j]);
					fprintf(out,"%d ",state[printIndex[k]].middle[i][j]);
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
	
    finishTime = clock();
    duration = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	printf("总共扩展节点的数量:%d\n",currentUsedIndex);
    printf( "耗时%f秒\n", duration);
	return 0;
}

