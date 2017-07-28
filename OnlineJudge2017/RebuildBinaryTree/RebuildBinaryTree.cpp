// RebuildBinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
int n=0,i=0,j=0,k=0;
int pre[4000000];
int post[4000000];
int leftChildRoot=0,leftChildSize=0;

struct BinaryTree
{
	int root;
	BinaryTree *leftChild;
	BinaryTree *rightChild;
};

typedef BinaryTree BTree;

void createBinaryTree(int aStart,int aEnd,int bStart,int bEnd,BTree *bTree)
{
	if(aStart>=aEnd)
	{
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
	leftChildRoot=pre[aStart+1];
	printf("leftChildRoot:%d\n",leftChildRoot);
	for(i=bStart;i<bEnd-1;i++)
	{
		if(post[i]==leftChildRoot)
		{
			leftChildSize=i;
			break;
		}
	}
	createBinaryTree(aStart+1,leftChildSize+1,aStart,leftChildSize,leftTree);
	createBinaryTree(leftChildSize+2,bEnd,leftChildSize+1,bEnd-1,rightTree);
}

void printTree(BTree *bTree)
{
	if(bTree->root!=0)
	{
		printf("%d\n",bTree->root);
		printTree(bTree->leftChild);
		printTree(bTree->rightChild);
	}
}

int main()
{
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&pre[i]);
	}
	for(i=0;i<n;i++)
	{
		scanf("%d",&post[i]);
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
	leftChildRoot=pre[1];
	for(i=0;i<n-2;i++)
	{
		if(post[i]==leftChildRoot)
		{
			leftChildSize=i;
			break;
		}
	}
	//创建左子数
	createBinaryTree(1,leftChildSize+1,0,leftChildSize,leftTree);
	//创建右子树
	createBinaryTree(leftChildSize+2,n-1,leftChildSize+1,n-2,rightTree);
	/*
	printf("%d\n",bTree->leftChild->leftChild->root);
	printf("%d\n",bTree->leftChild->leftChild->rightChild->root);
	printf("%d\n",bTree->rightChild->root);
	printf("%d\n",bTree->rightChild->leftChild->root);
	printf("%d\n",bTree->rightChild->leftChild->leftChild->root);
	*/
	//printTree(bTree);
	return 0;
}

