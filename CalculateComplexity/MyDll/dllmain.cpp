// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
/*
DLLע�빥����ע���DLL
�߼���Ϣ��ȫ�����ҵ
DllԶ��ע��+API�ҹ�
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
		   //�򿪼�������֤��Զ��ע�빥���ɹ���������Ϊ��ʹע��Ч����������
		   system("calc");
	       //DLLӳ�䵽Ŀ����̵ĵ�ַ�ռ�
		   MessageBox(NULL, L"DLLӳ��ɹ�!", L"1st RemoteThread", MB_OK);
       }
      
       case DLL_THREAD_ATTACH:
       MessageBox(NULL, L"Զ���̴߳����ɹ�!", L"2nd RemoteThread", MB_OK);
       break;

       case DLL_THREAD_DETACH:
       MessageBox(NULL, L"Զ���߳��Ѿ��˳�!", L"13rd RemoteThread", MB_OK);
       break;

       case DLL_PROCESS_DETACH:
       MessageBox(NULL, L"DLL�˳��ɹ�!", L"4th RemoteThread", MB_OK);
       break;
    }
    return TRUE;  //Used only for DLL_PROCESS_ATTACH
}
 


