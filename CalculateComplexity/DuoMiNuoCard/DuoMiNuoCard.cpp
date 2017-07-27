// DuoMiNuoCard.cpp : 定义控制台应用程序的入口点。
/**
清华大学OJ试题，多米诺骨牌问题
程序运行结果正确，但是时间超时
注释掉的为网上的参考答案
试题网址https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=1
**/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *c;
int x = 0,y = 0,i = 0,j = 0,k = 0;
char z;
char *d;
char *tempResult = "4";
char *f[10003],*t[10003];
char *middleVariable = "4";

char *add(char *a,char *b)
{
	int len_a = strlen(a)-1;
	int len_b = strlen(b)-1;
	int enter = 0;
	int len = (len_a > len_b) ? (len_a+1) : (len_b+1) ;
	c = (char *)malloc((len+2)*sizeof(char));
	for(i=len-1;i>=0;i--)
	{
		if(0 > len_a )
		{
			x = 0;
		}
		else
		{

			x = a[len_a--]-48;
		}
		if(0 > len_b)
		{
			y = 0;
		}
		else
		{
			y = b[len_b--]-48;
		}
	
		if(10<=x+y+enter)
		{
			z = x+y+enter-10+48;
			enter=1;
			
		}
		else
		{
			z = x+y+enter+48;
			enter=0;
		}
		c[i+1]=z;
	}
	
	if(enter)
	{
		c[0]='1';
		c[len+1] = '\0';
		return c;
	}
	else
	{
		
		 d = (char *)malloc((len+1)*sizeof(char));
		
		 for(i=0;i<len;i++)
		 {
			 d[i]=c[i+1];
		 }
		 d[len]='\0';
		 return d;
	}
	
}

char *sub(char *a,char *b)
{
	int aLength = strlen(a)-1;
	int bLength = strlen(b)-1;
	int borrow = 0;
	int length = (aLength>bLength)?aLength:bLength;
	c = (char *)malloc((length+2)*sizeof(char));
	
	for(i=length;i>=0;i--)
	{
		if(0>aLength)
		{
			x = 0;
		}
		else
		{
			x = a[aLength--]-48;
		}

		if(bLength<0)
		{
			y = 0;
		}
		else
		{
			y = b[bLength--]-48;
		}
		if((x-borrow)<y)
		{
			z = x+10-y-borrow+48;
			borrow = 1;
			
		}
		else
		{
			z = x-y-borrow+48;
			borrow = 0;
		}
		c[i] = z;
	}
	c[length+1] = '\0';
	if(c[0]!='0')
	{
		return c;
	}

	int k=0;
	for(k=0;k<length+1;k++)
	{
		if(c[k]!='0')
			break;
	}
	int count = length+1-k;
	d = (char *)malloc((count+1)*sizeof(char));
	for(i=0;i<=count;i++)
	{
		d[i] = c[i+k];
	}
	return d;

}

/*char *myCharPow(int k)
{
	char *temp="1";
	for(j=0;j<k;j++)
	{
		temp = add(temp,temp);
		
	}
	return temp;
}*/



int main()
{
	clock_t startTime, finishTime;
    double  duration;
   

	int n=0;
	//char *t = "2",*f1="2",*f2="6",*f3="0";
	f[3] = "2",t[3] = "2",f[4] = "6";
	scanf("%d",&n); 
	startTime = clock();
	if(n==3)
	{
		printf("2\n");
	}
	else
	{
		if(n==4)
		{
			printf("6\n");
		}
		else
		{
			for(int j=3;j<n-1;j++)
			{
				
				tempResult = add(tempResult,tempResult);
			
				//t[j+1] = sub(sub(tempResult,f[j]),t[j]);
				t[j+1] = sub(tempResult,middleVariable);
				middleVariable = add(f[j+1],t[j+1]);
				f[j+2] = add(middleVariable,f[j+1]);
				//f[j+2] = add(add(f[j+1],f[j+1]),t[j+1]);
				
			}
			printf("%s\n",f[n]);
		}
	}

	finishTime = clock();
    duration = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
    printf( "耗时%f秒\n", duration);
	
	return 0;
}


/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

char *add(char a[], char b[])
{
    int len, i, j, k, up, x, y, z;
    char *c, *back;

    len = (strlen(a) > strlen(b)) ? strlen(a) + 2 : strlen(b) + 2;
    c = (char *)malloc(len*sizeof(char));
    back = (char *)malloc(len*sizeof(char));

    i = strlen(a) - 1;
    j = strlen(b) - 1;
    k = 0; up = 0;

    while (i >= 0 || j >= 0)
    {
        if (i<0) x = '0'; else x = a[i];
        if (j<0) y = '0'; else y = b[j];
        z = x - '0' + y - '0';
        if (up == 1) z += 1;
        if (z>9) 
        { 
            up = 1; z %= 10; 
        }
        else up = 0;
        c[k++] = z + '0';
        i--; j--;
    }
    if (up) c[k++] = '1';
    c[k] = '\0'; 
    
    //reverse
    i = 0;
    for (k -= 1; k >= 0; k--) back[i++] = c[k];   
    back[i] = '\0';

    return back;
}

char *sub(char a[], char b[])
{
    int len, i, j, k, down, x, y, z;
    char *c, *back;

    len = strlen(a);
    c = (char *)malloc(len*sizeof(char));
    back = (char *)malloc(len*sizeof(char));

    i = strlen(a) - 1;
    j = strlen(b) - 1;
    k = 0; down = 0;

    while (i >= 0 || j >= 0)
    {
        if (i<0) x = '0'; else x = a[i];
        if (j<0) y = '0'; else y = b[j];
        z = x - '0' - (y - '0') - down;
        if ( z < 0 )
        {
            down = 1;
            z = z + 10;
        }
        else down = 0;
        c[k++] = z + '0'; 
        i--; j--;
    }
    while (c[--k] == '0') ;

    //reverse
    i = 0;
    for (k; k >= 0; k--)
    {
        back[i++] = c[k];
    }

    return back;
}

char *power(int n)
{
    int i;
    char *temp="2";
    
    for (i = 2; i <= n; i++)
    {
        temp = add(temp, temp);
    }

    return temp;
}

char *fib(int n)
{
    char *p = "1", *q = "1";
    char *s = "1";
    int i;

    for (i = 0; i < n - 1; i++)
    {
        s = add(p, q);
        p = q;
        q = s;
    }

    return s;
}

int main()
{
    int n;
    char *mi, *f;

    scanf("%d\n", &n);

    mi = power(n);
    f = fib(n);
    f = add(f, f);

    printf("%s\n", sub(mi, f));

    return 0;
}
*/
