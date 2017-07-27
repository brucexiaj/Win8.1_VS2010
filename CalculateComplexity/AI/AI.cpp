// AINCodeProblem.cpp : �������̨Ӧ�ó������ڵ㡣
/**
�˹�����ʵ�顪��N������
�ľ�20170616
���룺Npuzzle_in.txt
�����Npuzzle_out.txt
������������쳣���С��NODES��ֵ
**/

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 6//����ά��
#define MAX MAXN*MAXN//��������
#define NODES 150000//�洢���ṹ������
struct state
{
	int middle[MAXN][MAXN];
	int deepth;//���
	int front;//�ǲ���ǰ�ؽڵ�
	int father;//���ڵ���±�
	
};

typedef struct state State;

int n=0;//����
State state[NODES];//�洢���нڵ�Ľṹ������
int end[MAXN][MAXN];


//�ж�������ά�����Ƿ���ȣ���ȷ���1
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

//���0�ڶ�ά�����е�λ��
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

//0����
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

//0����
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

//0����
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
//0����
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

//������������״̬֮��������پ���(��һ������ʽ��������ʵ��ʹ�õ�����ʽ)
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

//����������ά�����ӦԪ�ز���ȵ�����Ŀ���ڶ�������ʽ����������Թ�����ʹ�ã�
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

//�ж��Ƿ��н⣬���������ĸļ���0��λ�õĸı��ۺϿ���
//����0��ʾ�޽�
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
	//���ʼ״̬����������0Ҳ�������ڣ�
	for(i=0;i<n*n;i++)
	{
		for(j=i+1;j<n*n;j++)
		{
			if(startArray[i]<startArray[j])
				startNumber++;
		}
	}
	//�����״̬����������0Ҳ�������ڣ�
	for(i=0;i<n*n;i++)
	{
		for(j=i+1;j<n*n;j++)
		{
			if(endArray[i]<endArray[j])
				endNumber++;
		}
	}
	//��ʼ��0�������0֮��������پ���
	int startZero[2]={0,0};
	int endZero[2]={0,0};
	locationOfZero(s,startZero);
	locationOfZero(end,endZero);
	int distanceOfZero=abs(startZero[0]-endZero[0])+abs(startZero[1]-endZero[1]);
	if((startNumber+endNumber+distanceOfZero)%2==0)
	{
		return 1;//�н�
	}
	else
	{
		return 0;
	}
}

//�����ʱӦ����չ��ǰ�ؽڵ���±�
//���������У����ڲ�ͬ������ʽ������ֻ�������ǲ�һ����
int extendNodeIndex(int currentIndex)
{
	int minCost=10000;
	int minFlag=0;
	//������õ��������پ���͵�����ʽ
	for(int i=0;i<currentIndex;i++)
	{
		
		if(state[i].front&&minCost>=state[i].deepth+distance(state[i].middle))
		{
			minCost=state[i].deepth+distance(state[i].middle);
			minFlag=i;
		}
		
	}
	
	
	/*	�����ǲ���λ��������������ʽ
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

//�ж�ĳ���ڵ��ڽṹ���������ǲ��ǳ��ֹ������ֹ���ɾ����
//����1��ʾɾ���ýڵ�
int isRepeat(int currentUsedIndex,State current)
{
	for(int i=0;i<currentUsedIndex;i++)
	{
		if(isArrayEqual(state[i].middle,current.middle))//��֮ǰ��ĳһ���ڵ��غ�
		{
			if(!state[i].front)//������ǰ�ؽڵ��غϣ�ɾ���ýڵ�
			{
				return 1;
			}
			else
			{
				if(current.deepth<state[i].deepth)//�����ǰ�ؽڵ��غ϶���������ȱ�ǰ�ؽڵ�С��ɾ��ǰ�ؽڵ�
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

//��State����ظ�����ģʽ
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

//�����±���չǰ�ؽڵ��е�ĳһ����������չ��ṹ���������Ч�±�
int extendSpecificFrontier(int index,int currentUsedIndex)
{
	//��ȡ0��λ��
	int zero[2]={0};
	locationOfZero(state[index].middle,zero);
	//����
	if(zero[0]!=0)
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveUp(state[index].middle,state[currentUsedIndex].middle,zero);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
	}
	//����
	if(zero[0]!=n-1)
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveDown(state[index].middle,state[currentUsedIndex].middle,zero);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
	}
	//����
	if(zero[1]!=0)
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveLeft(state[index].middle,state[currentUsedIndex].middle,zero);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
		}
		else
		{
			currentUsedIndex++;
		}
		
		
	}
	//����
	if(zero[1]!=n-1)
	{
		//����һ���ڵ���µ���չ
		state[currentUsedIndex].deepth=state[index].deepth+1;
		state[currentUsedIndex].front=1;
		state[currentUsedIndex].father=index;
		moveRight(state[index].middle,state[currentUsedIndex].middle,zero);
		//�ж�����ڵ��ǲ���֮ǰ���ֹ������ֹ���ɾ����
		if(isRepeat(currentUsedIndex-1,state[currentUsedIndex]))
		{
			toZero(state[currentUsedIndex]);
		
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
int isResult(int currentUsedIndex,int *re)
{
	//�Ӹո���չ���ĸ��ڵ��в�ѯ�������Ƿ��к�Ŀ��ڵ���ͬ��ֵ
	for(int i=currentUsedIndex-1;i>=currentUsedIndex-4;i--)
	{
		if(isArrayEqual(state[i].middle,end))
		{
			*re=i;
			return 1;//����
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
	//��ʼ���ṹ������
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
	
	//���ļ��л�ȡ����
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
	//�ж��Ƿ��н�
	if(!solveAble(start))
	{
		printf("�޽�\n");
		exit(0);
	}

	//����ʼ״̬���뵽�ṹ��������
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
		//�����ʱӦ����չ��ǰ�ؽڵ���±�
		int extendIndex=extendNodeIndex(currentUsedIndex);
		
		//��չ�ýڵ�
		currentUsedIndex=extendSpecificFrontier(extendIndex,currentUsedIndex);
		
		
	}
	
	int printIndex[100];
	for(i=0;i<100;i++)
	{
		printIndex[i]=-1;
	}
	//������յ㵽����·���ϵ����е���±겢�洢
	while(state[re].father!=0)
	{
		
		re=state[re].father;
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
			printf("%d ",state[0].middle[i][j]);
			fprintf(out,"%d ",state[0].middle[i][j]);
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
					printf("%d ",state[printIndex[k]].middle[i][j]);
					fprintf(out,"%d ",state[printIndex[k]].middle[i][j]);
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
	
    finishTime = clock();
    duration = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	printf("�ܹ���չ�ڵ������:%d\n",currentUsedIndex);
    printf( "��ʱ%f��\n", duration);
	return 0;
}

