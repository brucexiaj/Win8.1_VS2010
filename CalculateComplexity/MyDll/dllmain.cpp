// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
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
       //���ļ��������ļ�ָ�룬ָ���򿪷�ʽΪд+׷��
       FILE *fp = fopen("G:\\test.txt", "w");     //�򿪷�ʽ����Ϊ�ַ���
       //�ļ���д������
       //��д�ַ���getc(), putc(); ��д�ַ�����fgets(), fputs()
       //���׼�����������д����
       //getchar(), putchar();  gets(0, puts(0;
        fputs("һ��DLL�����ı�\n", fp);
        //printf("Test finished\n");
       //�ر��ļ�ָ�룬�ͷ��ڴ�
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
 


