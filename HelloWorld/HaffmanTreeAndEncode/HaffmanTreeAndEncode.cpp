// HaffmanTreeAndEncode.cpp : 定义控制台应用程序的入口点。
//霍夫曼编码，根据已经给定的字符串出现的频率进行编码

#include "stdafx.h"

#define M 15//叶子节点的个数
#define N 2*M-1//节点的总数
#define MaxWeight 32767

//定义静态链表的哈夫曼树存储结构
typedef struct//表示每一个节点
{
	int weight;
	int parent;
	int lchild;
	int rchild;
	
}Htype;


typedef struct//只表示叶子节点
{
	char data[5];
	int length;
	char code[7];
}HCode;



void HufTree(Htype hf[],int *w)
{
	int i,j,m1,m2,n1,n2;
	for(i=0;i<N;i++)
	{
		hf[i].weight=0;
		hf[i].parent=-1;
		hf[i].lchild=-1;
		hf[i].rchild=-1;
	}
	for(i=0;i<M;i++)
	{
		hf[i].weight=w[i];
		
	}
	for(i=0;i<M-1;i++)
	{
		m1=m2=MaxWeight;
		n1=n2=0;
		for(j=0;j<M+i;j++)
		{
			if(hf[j].parent==-1&&hf[j].weight<m1)
			{
				m2=m1;
				n2=n1;
				m1=hf[j].weight;
				n1=j;
			}
			else if(hf[j].parent==-1&&hf[j].weight<m2)
			{
				m2=hf[j].weight;
				n2=j;
			}
		}
		hf[n1].parent=M+i;
		hf[n2].parent=M+i;
		hf[M+i].weight=hf[n1].weight+hf[n2].weight;
		hf[M+i].lchild=n1;
		hf[M+i].rchild=n2;
	}
}

//本人所写
void CreateHoffmanCode(Htype htype[],HCode hcode[],char *d[])
{
	char code[6];
	for(int i=0;i<M;i++)
	{
		int parent=0,length=0,temp=i;;
		strcpy(hcode[i].data,d[i]);
		while(htype[temp].parent!=-1)
		{
			parent=htype[temp].parent;
			code[length]=(htype[parent].lchild==temp)?'0':'1';
			length++;
			temp=parent;
		}  
		hcode[i].length=length;
		for(int j=length-1;j>=0;j--)
		{
			hcode[i].code[length-1-j]=code[j];
		}
	}
}

//本人所写
void PrintHuffmanCode(HCode hcode[])
{
	for(int i=0;i<M;i++)
	{
		printf("%s\t",hcode[i].data);
	
		for(int j=0;j<hcode[i].length;j++)
		{
			printf("%c",hcode[i].code[j]);
		}
		printf("\n");
	}
}







//测试哈夫曼树的创建
void main()
{
	char *str[]={"the","of","a","to","and","in","that","he","is","at","on","for","his","are","be"};
	int fnum[]={1192,677,541,518,462,450,242,195,190,181,174,157,138,124,123};
	Htype ht[N];
	HCode hc[M];
	HufTree(ht,fnum);
	
	CreateHoffmanCode(ht,hc,str);
	PrintHuffmanCode(hc);
	

	
}


