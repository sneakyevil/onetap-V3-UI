#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Psapi.h>
#include <string>
#include <sstream>
#include <vector>
#include "3rdParty/MinHook/MinHook.h"
#include "3rdParty/ImGui/imgui_impl_win32.h"
#include "3rdParty/FindSignature.hpp"
#include "EndScene.hpp"

namespace WndProc
{
	typedef LRESULT(__stdcall* tHook)(HWND, UINT, WPARAM, LPARAM); tHook oHook;
	LRESULT __stdcall Hook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!UI::KeyBind::pKey)
		{
			if (wParam == VK_INSERT)
			{
				static bool bInsert = false;
				if (uMsg == WM_KEYDOWN && !bInsert)
				{
					EndScene::m_bMenuOpen = !EndScene::m_bMenuOpen;
					bInsert = true;
				}
				else if (uMsg == WM_KEYUP) bInsert = false;
			}
		}
		UI::WndProc(hWnd, uMsg, wParam, lParam);

		return CallWindowProcA(oHook, hWnd, uMsg, wParam, lParam);
	}
}

DWORD __stdcall Thread(void* m_pReserved)
{
	UI::hWindow = FindWindowA("Valve001", 0);
	UI::bUseWinWndProc = false;
	WndProc::oHook = WNDPROC(SetWindowLongA(UI::hWindow, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProc::Hook)));

    MODULEINFO m_mInfo = { 0 };
    K32GetModuleInformation(reinterpret_cast<HANDLE>(-1), GetModuleHandleA("shaderapidx9.dll"), &m_mInfo, sizeof(MODULEINFO));

    DWORD m_dDevice = FindSignature(reinterpret_cast<DWORD>(m_mInfo.lpBaseOfDll), reinterpret_cast<DWORD>(m_mInfo.lpBaseOfDll) + m_mInfo.SizeOfImage, "A1 ? ? ? ? 50 8B 08 FF 51 0C");
    m_dDevice = **reinterpret_cast<DWORD**>(m_dDevice + 0x1);
    void** m_pVTable = *reinterpret_cast<void***>(m_dDevice);
	void* m_pEndScene = m_pVTable[42];

	MH_Initialize();
    MH_CreateHook(m_pEndScene, EndScene::Hook, (void**)&EndScene::oHook);
    MH_EnableHook(m_pEndScene);

    return 0x0;
}

int __stdcall DllMain(HMODULE m_hMod, DWORD m_dCall, void* m_pReserved)
{
    if (m_dCall == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, Thread, m_hMod, 0, 0);
        return 1;
    }

    return 0;
}
