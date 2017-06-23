// HaffmanEcodeDocument.cpp : �������̨Ӧ�ó������ڵ㡣
//����������
//��Ӳ����ָ���ĵ���������Ӳ�̣�Ȼ����룬���������̨����
//���˽������������Ĵ���������ԭ�е��⣬��������Ϊ������д

#include "stdafx.h"

#define MaxLeafNum 30//�ַ��������Ŀ��ܵ����ֵ������������Ҷ�ӽڵ�ĸ���
#define MaxNodeNum 2*MaxLeafNum-1//���������ܵĽڵ���
#define MaxWeight 32767
#define MaxEcodeLength 10//�������Ŀ���ֵ
#define WFILE "E:\\IDE\\VC6.0\\MyProject\\HelloWorld\\HaffmanEcodeDocument\\ecode.txt"//��Ŵ�������ĵ�
#define RFILE "E:\\IDE\\VC6.0\\MyProject\\HelloWorld\\HaffmanEcodeDocument\\test.txt"//����ĵ������Ժ��ֵ

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
	char data;//ԭ�����ַ�
	int length;//����ĳ���
	char code[7];//����
}HCode;

typedef struct//ͳ���ַ����ֵĴ���
{
	char node;//�ַ�ֵ
	int fre;//���ֵĴ���
}EChar;


//������������
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
	for(i=0;i<M;i++)//Ҷ�ӽڵ��ʼ��
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
//Ϊÿһ���ַ������ַ�����ƻ��������룬�����ڡ�001011��
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

//������д
//��ӡ��ÿһ���������ַ������Ƕ�Ӧ�Ļ���������
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

//��ȡӲ�����ĵ�����ͳ��ÿһ���ַ����ֵĴ�������¼��EChar���͵�������
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
			for(int i=0;i<member;i++)//�ж��ǲ���֮ǰ���ֹ�
			{
				if(echar[i].node==temp)//������ֹ��������ַ������ֵĴ�����һ
				{
					echar[i].fre++;
					flag=0;
					break;
				}
			}
			if(flag)//����һ���µĽڵ�
			{
				echar[member].fre=1;
				echar[member].node=temp;
				member++;
			}
		}
	}
	fclose(file);
	return member;//�����ַ����������
}

//���ĵ����ջ�������ʽ���룬Ȼ����������
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
					//����ĸת��Ϊ���ִ洢��Ӳ����
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
			
//���������Ѿ�������ļ����룬Ȼ�����������̨����	
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
					//����Ѿ�������Ҷ�ӽڵ�
					if(htype[rchild].rchild==-1&&htype[rchild].lchild==-1)
					{
						printf("%c",hcode[rchild].data);
						parent=N-1;
					}
					//û�еĻ���������Ҷ�ӽڵ��ƽ�
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
	



//���Թ��������Ĵ���
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



