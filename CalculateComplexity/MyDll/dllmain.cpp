// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>









BOOL APIENTRY DllMain(HINSTANCE hInstDll, DWORD fdwReason, PVOID fImpLoad)
{
	
    switch (fdwReason)
    {
       case DLL_PROCESS_ATTACH :
    {
		system("calc");
	
       //The DLL is being mapped into the process's address space.
       //DWORD ThreadId;
       //CreateThread(NULL, NULL, MessageThread, NULL, NULL, &ThreadId);
       MessageBox(NULL, L"DLL has been mapped!", L"1st RemoteThread", MB_OK);
       //打开文件，定义文件指针，指定打开方式为写+追加
       FILE *fp = fopen("G:\\test.txt", "w");     //打开方式参数为字符串
       //文件读写函数：
       //读写字符：getc(), putc(); 读写字符串：fgets(), fputs()
       //向标准输入输出读入写出：
       //getchar(), putchar();  gets(0, puts(0;
        fputs("一个DLL测试文本\n", fp);
        //printf("Test finished\n");
       //关闭文件指针，释放内存
        fclose(fp);
		
    }
      
       case DLL_THREAD_ATTACH:
       //A Thread is being created.
       MessageBox(NULL, L"RemoteThread has been created!", L"2nd RemoteThread", MB_OK);
       break;
       case DLL_THREAD_DETACH:
       //A Thtread is exiting cleanly.
       MessageBox(NULL, L"RemoteThread exit!", L"13rd RemoteThread", MB_OK);
       break;
       case DLL_PROCESS_DETACH:
       //The DLL is being ummapped from the process' address space
       MessageBox(NULL, L"DLL has been unmapped!", L"4th RemoteThread", MB_OK);
       break;
    }
    return TRUE;  //Used only for DLL_PROCESS_ATTACH
}
 


