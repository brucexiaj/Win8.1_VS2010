// HelloWorldExe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "resource.h"
//原函数类型定义
typedef int (WINAPI* MsgBoxW)(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType);
FARPROC pfOldMsgBoxW;  //原API函数的地址
BYTE OldCode[5]; //原API入口代码
BYTE NewCode[5]; //原API的新的入口地址（帮助调转到新的API）

HANDLE hProcess=NULL;//本程序进程句柄

int WINAPI MyMessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)
{
	int nRet=::MessageBoxW(hWnd,_T("哈哈，MessageBoxW被HOOK了"),_T("假的MessageBox"),uType);
	return nRet;
}

//开启钩子的函数
void StartHook() 
{ 
 DWORD dwTemp=0;
 DWORD dwOldProtect;
 
 //修改API函数入口前5个字节为jmp xxxxxx
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,PAGE_READWRITE,&dwOldProtect); 
 WriteProcessMemory(hProcess,pfOldMsgBoxW,NewCode,5,0);
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,dwOldProtect,&dwTemp);

}

//获取API函数入口前5个字节
//旧入口前5个字节保存在前面定义的字节数组BYTE OldCode[5]
//新入口前5个字节保存在前面定义的字节数组BYTE NewCode[5]
void ChangeAPIEntrance()
{
 
  //获取原API入口地址
  HMODULE hmod=::LoadLibrary(_T("User32.dll"));
  MsgBoxW OldMsgBoxW=(MsgBoxW)::GetProcAddress(hmod,"MessageBoxA");
  pfOldMsgBoxW=(FARPROC)OldMsgBoxW;
  
  if (pfOldMsgBoxW==NULL)
  {
	MessageBox(NULL,_T("获取原API入口地址出错"),_T("error!"),0);
	return;
  }

  // 将原API的入口前5个字节代码保存到OldCode[]
  _asm 
  { 
   lea edi,OldCode		//获取OldCode数组的地址,放到edi
   mov esi,pfOldMsgBoxW //获取原API入口地址，放到esi
   cld	  //方向标志位，为以下两条指令做准备
   movsd //复制原API入口前4个字节到OldCode数组
   movsb //复制原API入口第5个字节到OldCode数组
  }


  NewCode[0]=0xe9;//将jump口令存到新API入口代码的第一个字节

  //获取MyMessageBoxW的相对地址,为Jmp做准备
  //int nAddr= UserFunAddr – SysFunAddr - （我们定制的这条指令的大小）;
  //Jmp nAddr;
  //（我们定制的这条指令的大小）, 这里是5，5个字节
  _asm 
  { 
   lea eax,MyMessageBoxW //获取我们的MyMessageBoxW函数地址
   mov ebx,pfOldMsgBoxW  //原系统API函数地址
   sub eax,ebx			 //int nAddr= UserFunAddr – SysFunAddr
   sub eax,5			 //nAddr=nAddr-5
   mov dword ptr [NewCode+1],eax //将算出的地址nAddr保存到NewCode后面4个字节
								 //注：一个函数地址占4个字节
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

	//启动hook API
	DWORD dwPid=::GetCurrentProcessId();
	hProcess=OpenProcess(PROCESS_ALL_ACCESS,0,dwPid); 
	ChangeAPIEntrance();
	StartHook(); 

	MessageBoxA(NULL,"调用了User32.dll动态链接库","API挂钩测试",MB_OK);
	return 0;
}
