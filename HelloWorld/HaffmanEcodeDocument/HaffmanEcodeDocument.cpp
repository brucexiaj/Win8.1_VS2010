// HaffmanEcodeDocument.cpp : 定义控制台应用程序的入口点。
//霍夫曼编码
//将硬盘中指定文档编码后存入硬盘，然后解码，输出到控制台上面
//除了建立霍夫曼树的代码是书上原有的外，其余代码均为本人所写

#include "stdafx.h"

#define MaxLeafNum 30//字符种类数的可能的最大值，即霍夫曼树叶子节点的个数
#define MaxNodeNum 2*MaxLeafNum-1//霍夫曼树总的节点数
#define MaxWeight 32767
#define MaxEcodeLength 10//编码的最长的可能值
#define WFILE "E:\\IDE\\VC6.0\\MyProject\\HelloWorld\\HaffmanEcodeDocument\\ecode.txt"//存放代编码的文档
#define RFILE "E:\\IDE\\VC6.0\\MyProject\\HelloWorld\\HaffmanEcodeDocument\\test.txt"//存放文档编码以后的值

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
	char data;//原来的字符
	int length;//编码的长度
	char code[7];//编码
}HCode;

typedef struct//统计字符出现的次数
{
	char node;//字符值
	int fre;//出现的次数
}EChar;


//建立霍夫曼树
void HufTree(Htype hf[],int *w,int M,int N)
{
	int i,j,m1,m2,n1,n2;
	for(i=0;i<N;i++)
	{
		hf[i].weight=0;
		hf[i].parent=-1;
		hf[i].lchild=-1;
		hf[i].rchild=-1;
	}
	for(i=0;i<M;i++)//叶子节点初始化
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
//为每一个字符或者字符串设计霍夫曼编码，类似于“001011”
void CreateHoffmanCode(Htype htype[],HCode hcode[],char d[],int M)
{
	char code[MaxEcodeLength];
	for(int i=0;i<M;i++)
	{
		int parent=0,length=0,temp=i;;
		hcode[i].data=d[i];
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
//打印出每一个单独的字符和他们对应的霍夫曼编码
void PrintHuffmanCode(HCode hcode[],int M)
{
	for(int i=0;i<M;i++)
	{
		printf("%c\t",hcode[i].data);
	
		for(int j=0;j<hcode[i].length;j++)
		{
			printf("%c",hcode[i].code[j]);
		}
		printf("\n");
	}
}

//读取硬盘中文档，并统计每一个字符出现的次数，记录在EChar类型的数组中
int ReadFile(char *filename,EChar echar[])
{
	
	FILE *file=fopen(filename,"r");
	int member=0;
	char temp;
	if(file==NULL)
	{
		printf("File not exist\n");
	}
	else
	{
		
		while((temp=fgetc(file))!=EOF)
		{
			int flag=1;
			for(int i=0;i<member;i++)//判断是不是之前出现过
			{
				if(echar[i].node==temp)//如果出现过，将该字符串出现的次数加一
				{
					echar[i].fre++;
					flag=0;
					break;
				}
			}
			if(flag)//增加一个新的节点
			{
				echar[member].fre=1;
				echar[member].node=temp;
				member++;
			}
		}
	}
	fclose(file);
	return member;//返回字符的种类个数
}

//将文档按照霍夫曼方式编码，然后存入磁盘中
void EncodeSaveToDisk(char *rFile,char *wFile,HCode hcode[],int M)
{
	FILE *rfile=fopen(rFile,"r");
	FILE *wfile=fopen(wFile,"w");
	int member=0;
	char temp;
	if(rfile==NULL||wfile==NULL)
	{
		printf("File not exist\n");
	}
	else
	{
		while((temp=fgetc(rfile))!=EOF)
		{
			for(int i=0;i<M;i++)
			{
				if(temp==hcode[i].data)
				{
					//将字母转化为数字存储到硬盘上
					for(int j=0;j<hcode[i].length;j++)
					{
						fprintf(wfile,"%c",hcode[i].code[j]);
						
					}
					break;
				}
			}
		}
	}
	fclose(rfile);
	fclose(wfile);
}
			
//将磁盘中已经编码的文件解码，然后输出到控制台上面	
void DecodeFromDiskFile(char *rFile,Htype htype[],HCode hcode[],int N)
{
	FILE *file=fopen(rFile,"r");
	int rchild,lchild=0,parent=N-1;
	char temp;
	if(file==NULL)
	{
		printf("File not exist\n");
	}
	else
	{
		while((temp=fgetc(file))!=EOF)
		{
			if(temp=='1')
				{
					rchild=htype[parent].rchild;
					//如果已经遍历到叶子节点
					if(htype[rchild].rchild==-1&&htype[rchild].lchild==-1)
					{
						printf("%c",hcode[rchild].data);
						parent=N-1;
					}
					//没有的话，继续向叶子节点推进
					else
					{
						parent=rchild;
					}
				}
				else
				{
					lchild=htype[parent].lchild;
					if(htype[lchild].rchild==-1&&htype[lchild].lchild==-1)
					{
						printf("%c",hcode[lchild].data);
						parent=N-1;
					}
					else
					{
						parent=lchild;
					}
				}
			}
		}
	fclose(file);
}
	



//测试哈夫曼树的创建
void main()
{
	
	
	EChar echar[MaxLeafNum];
	Htype ht[MaxLeafNum];
	HCode hc[MaxNodeNum];
	char str[MaxLeafNum];
	int fnum[MaxLeafNum];
	int kindOfCharacter=ReadFile(RFILE,echar);
	
	for(int i=0;i<kindOfCharacter;i++)
	{
		str[i]=echar[i].node;
		fnum[i]=echar[i].fre;
	
	}

	
	HufTree(ht,fnum,kindOfCharacter,kindOfCharacter*2-1);
	CreateHoffmanCode(ht,hc,str,kindOfCharacter);
	
	PrintHuffmanCode(hc,kindOfCharacter);
	EncodeSaveToDisk(RFILE,WFILE,hc,kindOfCharacter);
	DecodeFromDiskFile(WFILE,ht,hc,kindOfCharacter*2-1);

	
}



