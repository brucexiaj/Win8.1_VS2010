// RebuildBinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
/**
Tsinghua Online Judge
https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=58
��������ع�����
��һ������������ʱ�������ͨ��
20170728
**/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
int n=0,i=0,j=0;
int pre[4000000];//����������������
int post[4000000];//��ź������������

//����������Ľṹ
typedef struct BinaryTree
{
	int root;
	BinaryTree *leftChild;
	BinaryTree *rightChild;
}BTree;





//ͨ�������鴴��������
void createBinaryTree(int aStart,int aEnd,int bStart,int bEnd,BTree *bTree)
{
	//printf("%d,%d,%d,%d\n",aStart,aEnd,bStart,bEnd);
	int leftChildSize=0;
	//���������ֻ�и��ڵ���߸ö�����������
	if(aStart>=aEnd)
	{
		if(aStart>aEnd)
		{
			bTree->root=-1;
			bTree->leftChild=NULL;
			bTree->rightChild=NULL;
			return;
		}
		bTree->root=pre[aStart];
		bTree->leftChild=NULL;
		bTree->rightChild=NULL;
		return;
	}
	bTree->root=pre[aStart];
	
	BTree *leftTree;
	BTree *rightTree;
	leftTree=(BTree *)malloc(sizeof(BTree));
	rightTree=(BTree *)malloc(sizeof(BTree));
	bTree->leftChild=leftTree;
	bTree->rightChild=rightTree;
	int leftChildRoot=pre[aStart+1];
	//printf("leftChildRoot:%d\n",leftChildRoot);
	//Ѱ�����������������ķָ��
	for(i=bEnd-1;i>=bStart;i--)
	{
		if(post[i]==leftChildRoot)
		{
			leftChildSize=i;
			break;
		}
	}
	//printf("leftChildSize:%d\n",leftChildSize);
	createBinaryTree(aStart+1,leftChildSize-bStart+aStart+1,bStart,leftChildSize,leftTree);
	createBinaryTree(leftChildSize-bEnd+2+aEnd,aEnd,leftChildSize+1,bEnd-1,rightTree);
}

void printTree(BTree *bTree)
{
	if(bTree!=NULL&&bTree->root!=-1)
	{
		printTree(bTree->leftChild);
		printf("%d ",bTree->root);
		printTree(bTree->rightChild);
	}
}

int main()
{
	int leftChildSize=0;
	
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&pre[i]);
	}
	for(i=0;i<n;i++)
	{
		scanf("%d",&post[i]);
	}
	/*
	//���ļ��л�ȡ����
	FILE *file=fopen("in.txt","r");
	fscanf(file,"%d",&n);
	for(i=0;i<n;i++)
	{
	
			fscanf(file,"%d",&(pre[i]));
		
	}
	for(i=0;i<n;i++)
	{
	
			fscanf(file,"%d",&(post[i]));
		
	}
	fclose(file);
	*/
	if(n==1)
	{
		printf("%d\n",pre[0]);
		return 0;
	}
	BTree *bTree;
	bTree=(BTree *)malloc(sizeof(BTree));
	bTree->root=pre[0];
	BTree *leftTree;
	BTree *rightTree;
	leftTree=(BTree *)malloc(sizeof(BTree));
	rightTree=(BTree *)malloc(sizeof(BTree));
	bTree->leftChild=leftTree;
	bTree->rightChild=rightTree;
	//Ѱ�����������ķָ��
	int leftChildRoot=pre[1];
	for(i=0;i<n-2;i++)
	{
		if(post[i]==leftChildRoot)
		{
			leftChildSize=i;
			break;
		}
	}
	//����������
	createBinaryTree(1,leftChildSize+1,0,leftChildSize,leftTree);
	//����������
	createBinaryTree(leftChildSize+2,n-1,leftChildSize+1,n-2,rightTree);
	//��ӡ������
	printTree(bTree->leftChild);
	printf("%d ",bTree->root);
	printTree(bTree->rightChild);
	return 0;
}

