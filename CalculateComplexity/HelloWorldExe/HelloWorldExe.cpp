// HelloWorldExe.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include "resource.h"
//ԭ�������Ͷ���
typedef int (WINAPI* MsgBoxW)(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType);
FARPROC pfOldMsgBoxW;  //ԭAPI�����ĵ�ַ
BYTE OldCode[5]; //ԭAPI��ڴ���
BYTE NewCode[5]; //ԭAPI���µ���ڵ�ַ��������ת���µ�API��

HANDLE hProcess=NULL;//��������̾��

int WINAPI MyMessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)
{
	int nRet=::MessageBoxW(hWnd,_T("������MessageBoxW��HOOK��"),_T("�ٵ�MessageBox"),uType);
	return nRet;
}

//�������ӵĺ���
void StartHook() 
{ 
 DWORD dwTemp=0;
 DWORD dwOldProtect;
 
 //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,PAGE_READWRITE,&dwOldProtect); 
 WriteProcessMemory(hProcess,pfOldMsgBoxW,NewCode,5,0);
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,dwOldProtect,&dwTemp);

}

//��ȡAPI�������ǰ5���ֽ�
//�����ǰ5���ֽڱ�����ǰ�涨����ֽ�����BYTE OldCode[5]
//�����ǰ5���ֽڱ�����ǰ�涨����ֽ�����BYTE NewCode[5]
void ChangeAPIEntrance()
{
 
  //��ȡԭAPI��ڵ�ַ
  HMODULE hmod=::LoadLibrary(_T("User32.dll"));
  MsgBoxW OldMsgBoxW=(MsgBoxW)::GetProcAddress(hmod,"MessageBoxA");
  pfOldMsgBoxW=(FARPROC)OldMsgBoxW;
  
  if (pfOldMsgBoxW==NULL)
  {
	MessageBox(NULL,_T("��ȡԭAPI��ڵ�ַ����"),_T("error!"),0);
	return;
  }

  // ��ԭAPI�����ǰ5���ֽڴ��뱣�浽OldCode[]
  _asm 
  { 
   lea edi,OldCode		//��ȡOldCode����ĵ�ַ,�ŵ�edi
   mov esi,pfOldMsgBoxW //��ȡԭAPI��ڵ�ַ���ŵ�esi
   cld	  //�����־λ��Ϊ��������ָ����׼��
   movsd //����ԭAPI���ǰ4���ֽڵ�OldCode����
   movsb //����ԭAPI��ڵ�5���ֽڵ�OldCode����
  }


  NewCode[0]=0xe9;//��jump����浽��API��ڴ���ĵ�һ���ֽ�

  //��ȡMyMessageBoxW����Ե�ַ,ΪJmp��׼��
  //int nAddr= UserFunAddr �C SysFunAddr - �����Ƕ��Ƶ�����ָ��Ĵ�С��;
  //Jmp nAddr;
  //�����Ƕ��Ƶ�����ָ��Ĵ�С��, ������5��5���ֽ�
  _asm 
  { 
   lea eax,MyMessageBoxW //��ȡ���ǵ�MyMessageBoxW������ַ
   mov ebx,pfOldMsgBoxW  //ԭϵͳAPI������ַ
   sub eax,ebx			 //int nAddr= UserFunAddr �C SysFunAddr
   sub eax,5			 //nAddr=nAddr-5
   mov dword ptr [NewCode+1],eax //������ĵ�ַnAddr���浽NewCode����4���ֽ�
								 //ע��һ��������ַռ4���ֽ�
  } 

  
}


int main()
{
	int i=10;
	while(i>0)
	{
		i--;
		printf("hello,world\n");
		Sleep(2000);
	}

	//����hook API
	DWORD dwPid=::GetCurrentProcessId();
	hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid); 
	ChangeAPIEntrance();
	StartHook(); 

	MessageBoxA(NULL,"������User32.dll��̬���ӿ�","API�ҹ�����",MB_OK);
	return 0;
}
