// HaffmanTreeAndEncode.cpp : �������̨Ӧ�ó������ڵ㡣
//���������룬�����Ѿ��������ַ������ֵ�Ƶ�ʽ��б���

#include "stdafx.h"

#define M 15//Ҷ�ӽڵ�ĸ���
#define N 2*M-1//�ڵ������
#define MaxWeight 32767

//���徲̬����Ĺ��������洢�ṹ
typedef struct//��ʾÿһ���ڵ�
{
	int weight;
	int parent;
	int lchild;
	int rchild;
	
}Htype;


typedef struct//ֻ��ʾҶ�ӽڵ�
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

//������д
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

//������д
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







//���Թ��������Ĵ���
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


