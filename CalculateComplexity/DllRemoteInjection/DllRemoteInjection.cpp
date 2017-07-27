// ChinaUnixSourceCode.cpp : �������̨Ӧ�ó������ڵ㡣
/**
author:xiajun
time:15th,June.2017
DLLע�빥������
�߼���Ϣ��ȫ�γ̱����ҵ��DLLԶ��ע�빥��+API�ҹ�
�����API�ҹ����õ��Ǳ������ڲ���API�ҹ�
**/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#define DLL_LOCATION "E:\\MyDll.dll"   //ִ��ע���DLL�ĵ�ַ�����Ը���

//��ȡ��ǰϵͳ����
int ListProcess()
{
    //��ȡϵͳ����
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
       printf("CreateToolHelp32Snapshot error!\n");
       return -1;
    }
 
    //�����������̿��սṹ�壬��ʼ����С
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32); 
 
    //��ʼ��������
    WCHAR buff[1024] = {0};
 
    //ö��ϵͳ���������еĵ�һ��������Ŀ
    BOOL bProcess = Process32First(hProcessSnap, &pe32);
    while (bProcess)
    {
	    //��ʽ���������ͽ���ID������Ҫʹ��printf�Ŀ��ַ���
       //��ʽ�ַ�����������Ҫ��Lת��Ϊ���ַ���ʽ
       wsprintf(buff, L"Process:%-30sID:%-6d\r\n", pe32.szExeFile, pe32.th32ProcessID);
       wprintf(L"%s",buff);
       //��������λ
       memset(buff, 0, sizeof(buff));
       //����ö����һ������
       bProcess = Process32Next(hProcessSnap, &pe32);
    }
 
    CloseHandle(hProcessSnap);
    return 0;
}

//����Ȩ��
int EnableDebugPriv(const WCHAR *name)
{
    HANDLE hToken;   //�������ƾ��
    TOKEN_PRIVILEGES tp;  //TOKEN_PRIVILEGES�ṹ�壬���а���һ��������+��������Ȩ������
    LUID luid;       //�����ṹ���е�����ֵ
 
    //�򿪽������ƻ�
    //GetCurrentProcess()��ȡ��ǰ���̵�α�����ֻ��ָ��ǰ���̻����߳̾������ʱ�仯
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
    {
       printf("OpenProcessToken error\n");
       return -8;
    }
 
    //��ñ��ؽ���name�������Ȩ�����͵ľֲ�ΨһID
    if (!LookupPrivilegeValue(NULL, name, &luid))
    {
       printf("LookupPrivilegeValue error\n");
    }
 
    tp.PrivilegeCount = 1;    //Ȩ��������ֻ��һ����Ԫ�ء�
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //Ȩ�޲���
    tp.Privileges[0].Luid = luid;   //Ȩ������
 
    //��������Ȩ��
    if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
       printf("AdjustTokenPrivileges error!\n");
       return -9;
    }
 
    return 0;
}



int main()
{
	
	printf("��ǰϵͳ�е����н���Ϊ:\n");
    //�������ID��ý��̾��
	ListProcess();
    printf("������Ҫע��Ľ���ID��\n");
    DWORD dwRemoteProcessId;
    scanf("%d",&dwRemoteProcessId);
 
    //��õ���Ȩ��
	
    if (EnableDebugPriv(SE_DEBUG_NAME))
    {
       printf("Add Privilege error\n");
       return -1;
    }
	
    //Step1:��ȡҪע���Ŀ����̣�Զ�̽��̣��ľ��
    HANDLE hRemoteProcess;
    if ((hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId)) == NULL)
    {
       printf("��ȡĿ����̾��ʧ��\n");
       return -2;
    }
 
    //Step2:��VirtualAllocEx������Զ�̽��̵ĵ�ַ�ռ��з���һ���ڴ�
    char DllPath[260]; //Windows���·������
    strcpy(DllPath, DLL_LOCATION); //���ӵ�DLL·��
	LPVOID pRemoteDllPath = VirtualAllocEx(hRemoteProcess, NULL, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pRemoteDllPath == NULL)
    {
       printf("��Զ�̽����з����ַ�ռ�ʧ��\n");
       return -3;
    }
 
    //Step3:��WriteProcessMemory������Dll��·�������Ƶ���һ��������ڴ���
    DWORD Size;
    if (WriteProcessMemory(hRemoteProcess, pRemoteDllPath, DllPath, strlen(DllPath) +1, &Size) == NULL)
    {
       printf("д��DLL·������Զ�̽��̵�ַ�ռ�ʧ��\n");
       return -4;
    }
 
    //Step4:��GetProcAddress�����õ�LoadLibraryA������Զ�̽����е�ʵ�ʵ�ַ
    LPTHREAD_START_ROUTINE pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
    if (pLoadLibrary == NULL)
    {
       printf("��ȡLoadLibraryA����ʵ��ַʧ��\n");
       return -5;
    }
 
    //Step5:��CreateRemoteThread������Զ�̽����д���һ���߳�
    DWORD dwThreadId;
    HANDLE hThread;
    if ((hThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pLoadLibrary, pRemoteDllPath, 0, &dwThreadId)) == NULL)
    {
       printf("����Զ���߳�ʧ��\n");
       return -6;
    }
   
    WaitForSingleObject(hThread, INFINITE);
    printf("ע�����\n");
   
 
    //Step6:�ͷ���Զ�̽����з�����ڴ�
    if (VirtualFreeEx(hRemoteProcess, pRemoteDllPath, 0, MEM_RELEASE) == 0)
    {
       printf("�ڴ��ͷ�ʧ��\n");
       return -8;
    }
 
    //Step7:�ͷž��
    if (hThread != NULL) CloseHandle(hThread);
    if (hRemoteProcess != NULL) CloseHandle(hRemoteProcess);
 
    system("pause");
    return 0;
}

