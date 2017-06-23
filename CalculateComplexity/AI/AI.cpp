// AINCodeProblem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define MAXN 6//����ά��
#define MAX MAXN*MAXN//��������
#define NODES 6000//�洢���ṹ������
struct state
{
	int middle[MAXN][MAXN];
	int deepth;//���
	int front;//�ǲ���ǰ�ؽڵ�
	int father;//���ڵ���±�
	int deleted;//1��ʾ�ýڵ��Ѿ�����
};

typedef struct state State;

//�ж�������ά�����Ƿ����
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

//���0�ڶ�ά�����е�λ��
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

//0����
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

//0����
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

//0����
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
//0����
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

//������������״̬֮��������پ���
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

//�ж��Ƿ��н�
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
	//���ʼ״̬��������
	for(int i=0;i<n*n;i++)
	{
		for(int j=i+1;j<n*n;j++)
		{
			if(start[i]&&start[j]&&start[i]<start[j])
				startNumber++;
		}
	}
	//�����״̬��������
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

//�����ʱӦ����չ��ǰ�ؽڵ���±�
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

//�ж�ĳ���ڵ��ڽṹ���������ǲ��ǳ��ֹ������ֹ���ɾ����
int isRepeat(State state[NODES],int currentUsedIndex,State current,int n)
{
	for(int i=0;i<currentUsedIndex;i++)
	{
		if(!state[i].deleted&&!toTarget(state[i].middle,current.middle,n))//��֮ǰ��ĳһ���ڵ��غ�
		{
			if(!state[i].front)//����Ƿ�ǰ�ؽڵ�
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

//��State����ظ�����ģʽ
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

//�����±���չǰ�ؽڵ��е�ĳһ����������չ��ṹ���������Ч�±�
int extendSpecificFrontier(int index,State state[NODES],int n,int currentUsedIndex)
{
	//��ȡ0��λ��
	int zero[2];
	locationOfZero(state[index].middle,zero,n);
	int x=zero[0];
	int y=zero[1];
	int deleteIndex=0;
	//����
	if(x==0)
	{
	}
	else
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveUp(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
	}
	//����
	if(x==n-1)
	{}
	else
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveDown(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
	}
	//����
	if(y==0)
	{}
	else
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveLeft(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
	}
	//����
	if(y==n-1)
	{}
	else
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveRight(state[index].middle,state[currentUsedIndex].middle,zero,n);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(state,currentUsedIndex-1,state[currentUsedIndex],n))
		{
			toZero(state[currentUsedIndex],n);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
		
	}
	//�Ը��ڵ㴦��
	state[index].front=0;
	return currentUsedIndex;
}

//�ж��Ƿ����
int isResult(State state[NODES],int end[MAXN][MAXN],int currentUsedIndex,int n,int *re)
{
	//�Ӹո���չ���ĸ��ڵ��в�ѯ�������Ƿ��к�Ŀ��ڵ���ͬ��ֵ
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
			return 1;//����
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
	//��ʼ���ṹ������
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
	
	//���ļ��л�ȡ����
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
	//�ж��Ƿ��н�
	if(!solveAble(start,end,n))
	{
		printf("�޽�\n");
		exit(0);
	}

	//����ʼ״̬���뵽�ṹ��������
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
		//�����ʱӦ����չ��ǰ�ؽڵ���±�
		int extendIndex=extendNodeIndex(myState,n,end,currentUsedIndex);
		//printf("extendIndex:%d\n",extendIndex);
		
		//��չ�ýڵ�
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
	//printf("����:%d\n",step);
	//printf("re:%d\n",re);
	int printIndex[100];
	for(i=0;i<100;i++)
	{
		printIndex[i]=-1;
	}
	//������յ㵽����·���ϵ����е���±겢�洢
	while(myState[re].father!=0)
	{
		
		re=myState[re].father;
		printIndex[step]=re;
		step++;
	}
	//��ӡ������ļ���
	FILE *out=fopen("Npuzzle_out.txt","w");
	printf("��%d��\n",step+1);
	fprintf(out,"��%d��\n",step+1);
	//��ӡ��ʼ״̬
	printf("��ʼ״̬\n");
	fprintf(out,"��ʼ״̬\n");
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
	//��ӡÿһ������
	for(k=99;k>=0;k--)
	{
		if(printIndex[k]!=-1)
		{
			printf("��%d��\n",step);
			fprintf(out,"��%d��\n",step);
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
	//��ӡ�յ�״̬
	printf("Ŀ��״̬\n");
	fprintf(out,"Ŀ��״̬\n");
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

