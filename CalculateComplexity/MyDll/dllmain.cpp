// dllmain.cpp : 定义 DLL 应用程序的入口点。
/*
DLL注入攻击待注入的DLL
高级信息安全编程作业
Dll远程注入+API挂钩
*/
#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>

BOOL APIENTRY DllMain(HINSTANCE hInstDll, DWORD fdwReason, PVOID fImpLoad)
{
	switch (fdwReason)
    {
       case DLL_PROCESS_ATTACH :
	   {
		   //打开计算器，证明远程注入攻击成功，这里是为了使注入效果更加明显
		   system("calc");
	       //DLL映射到目标进程的地址空间
		   MessageBox(NULL, L"DLL映射成功!", L"1st RemoteThread", MB_OK);
       }
      
       case DLL_THREAD_ATTACH:
       MessageBox(NULL, L"远程线程创建成功!", L"2nd RemoteThread", MB_OK);
       break;

       case DLL_THREAD_DETACH:
       MessageBox(NULL, L"远程线程已经退出!", L"13rd RemoteThread", MB_OK);
       break;

       case DLL_PROCESS_DETACH:
       MessageBox(NULL, L"DLL退出成功!", L"4th RemoteThread", MB_OK);
       break;
    }
    return TRUE;  //Used only for DLL_PROCESS_ATTACH
}
 


