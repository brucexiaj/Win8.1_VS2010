// APIHook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

int WINAPI MyMessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)  
{  
    //�����APIʱ������ĺ����������ʱ�ɲ�д...  
    return 0;  
} 

//�������ӵĺ���  
void HookOn()   
{   
 ASSERT(hProcess!=NULL);  
  
 DWORD dwTemp=0;  
 DWORD dwOldProtect;  
   
 //�޸�API�������ǰ5���ֽ�Ϊjmp xxxxxx  
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,PAGE_READWRITE,&dwOldProtect);   
 WriteProcessMemory(hProcess,pfOldMsgBoxW,NewCode,5,0);  
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,dwOldProtect,&dwTemp);  
  
}  

	//�رչ��ӵĺ���  
void HookOff()  
{   
 ASSERT(hProcess!=NULL);  
  
 DWORD dwTemp=0;  
 DWORD dwOldProtect;  
  
 //�ָ�API�������ǰ5���ֽ�  
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,PAGE_READWRITE,&dwOldProtect);   
 WriteProcessMemory(hProcess,pfOldMsgBoxW,OldCode,5,0);   
 VirtualProtectEx(hProcess,pfOldMsgBoxW,5,dwOldProtect,&dwTemp);    
}  

//ԭ�������Ͷ���  
typedef int (WINAPI* MsgBoxW)(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType);



int main(int argc, _TCHAR* argv[])
{
	MsgBoxW OldMsgBoxW=NULL;//ָ��ԭ������ָ�� 
	FARPROC pfOldMsgBoxW;  //ָ������Զָ��

	//��ȡԭAPI��ڵ�ַ  
	HMODULE hmod=::LoadLibrary(_T("User32.dll"));  
	OldMsgBoxW=(MsgBoxW)::GetProcAddress(hmod,"MessageBoxW");  
	pfOldMsgBoxW=(FARPROC)OldMsgBoxW;  

	// ��ԭAPI�����ǰ5���ֽڴ��뱣�浽OldCode[]  
	BYTE OldCode[5];  
	_asm   
	{   
	lea edi,OldCode      //��ȡOldCode����ĵ�ַ,�ŵ�edi  
	mov esi,pfOldMsgBoxW //��ȡԭAPI��ڵ�ַ���ŵ�esi  
	cld    //�����־λ��Ϊ��������ָ����׼��  
	movsd //����ԭAPI���ǰ4���ֽڵ�OldCode����  
	movsb //����ԭAPI��ڵ�5���ֽڵ�OldCode����  
	}  

	//��ȡMyMessageBoxW����Ե�ַ,ΪJmp��׼��  
	//int nAddr= UserFunAddr �C SysFunAddr - �����Ƕ��Ƶ�����ָ��Ĵ�С��;  
	//Jmp nAddr;  
	//�����Ƕ��Ƶ�����ָ��Ĵ�С��, ������5��5���ֽ���  
	BYTE NewCode[5];  
	_asm   
	{   
	lea eax,MyMessageBoxW //��ȡ���ǵ�MyMessageBoxW������ַ  
	mov ebx,pfOldMsgBoxW  //ԭϵͳAPI������ַ  
	sub eax,ebx           //int nAddr= UserFunAddr �C SysFunAddr  
	sub eax,5             //nAddr=nAddr-5  
	mov dword ptr [NewCode+1],eax //������ĵ�ַnAddr���浽NewCode����4���ֽ�  
                                 //ע��һ��������ַռ4���ֽ�  
	} 

	//�����ϣ�����NewCode[]���ָ���൱��Jmp MyMessageBoxW  
	//��Ȼ�Ѿ���ȡ����Jmp MyMessageBoxW  
	//���ڸ��ǽ�Jmp MyMessageBoxWд��ԭAPI���ǰ5���ֽڵ�ʱ����  
	//֪��Ϊʲô��5���ֽ���  
	//Jmpָ���൱��0xe9,ռһ���ֽڵ��ڴ�ռ�  
	//MyMessageBoxW��һ����ַ����ʵ��һ��������ռ4���ֽڵ��ڴ�ռ�  
	//int n=0x123;   nռ4���ֽں�MyMessageBoxWռ4���ֽ���һ����  
	//1+4=5��֪��Ϊʲô��5���ֽ��˰�  
	HookOn();  

	//�ָ�ԭ����API�����Ĵ�������


	return 0;
}

