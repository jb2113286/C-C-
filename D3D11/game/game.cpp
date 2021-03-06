// game.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "game.h"
#include <D3D11.h>
#include <D3DX11.h>

HHOOK hook = NULL;
DWORD jmpto = 0;

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

GAME_API void SetHook()
{
	hook = SetWindowsHookEx(WH_CBT, CBTProc, GetModuleHandle(L"GAME.dll"), 0);
}

GAME_API void UnHook()
{
	if(hook)
		::UnhookWindowsHookEx(hook);
}

void check()
{
	HWND hwnd = ::FindWindow(L"CoDBlackOps", NULL);
	DWORD pid = 0;
	GetWindowThreadProcessId(hwnd, &pid);
	if (GetCurrentProcessId() == pid)
	{
		MessageBox(hwnd, L"OK", L"注入成功!!", MB_OK);
		HookDrawIndexedPrimitive();
	}
}

ULONG_PTR GetDrawIndexedAddress()
{
	HANDLE handle = GetModuleHandle(L"D3D11.dll");
	if (handle == INVALID_HANDLE_VALUE)
		return NULL;
	return (ULONG_PTR)handle + 0x58780;
}

__declspec(naked) void STDMETHODCALLTYPE Orginal_DrawIndexedPrimitive(ID3D11DeviceContext* m_pDevice, UINT IndexCount, UINT StartIndexLocation, INT  BaseVertexLocation)
{
	_asm
	{
		mov eax,dword ptr[esp + 0x4]
		lea ecx,[eax + 62C4h]
		mov eax, dword ptr[eax + 1E8h]
		mov dword ptr[esp + 0x4], ecx
		jmp eax
	}
}

void STDMETHODCALLTYPE MyDrawIndexed(ID3D11DeviceContext* m_pDevice, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	Orginal_DrawIndexedPrimitive(m_pDevice,IndexCount, StartIndexLocation, BaseVertexLocation);
}

void HookDrawIndexedPrimitive()
{
	ULONG_PTR address = GetDrawIndexedAddress();
	jmpto = address + 10;
	DWORD oldProtect = 0;
	VirtualProtect((LPVOID)address, 10, PAGE_EXECUTE_READWRITE, &oldProtect);
	DWORD value = (DWORD)MyDrawIndexed - (DWORD)address - 5;
	_asm
	{
		mov eax, address
		mov byte ptr[eax], 0xE9
		add eax, 1
		mov ecx, value
		mov dword ptr[eax], ecx
		add eax, 4
		mov dword ptr[eax], 0x90909090
		add eax, 1
		mov byte ptr[eax], 0x90

	}
	VirtualProtect((LPVOID)address, 10, oldProtect, &oldProtect);
}

void UnHookDrawIndexedPrimitive()
{
	ULONG_PTR address = GetDrawIndexedAddress();
	DWORD oldProtect = 0;
	VirtualProtect((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	_asm
	{
		mov eax, address
		mov dword ptr[eax], 0x8B442404
		add eax, 4
		mov dword ptr[eax], 0x8D88C462
		add eax, 4
		mov word ptr[eax], 0x0000
	}
	VirtualProtect((LPVOID)address, 5, oldProtect, &oldProtect);
}