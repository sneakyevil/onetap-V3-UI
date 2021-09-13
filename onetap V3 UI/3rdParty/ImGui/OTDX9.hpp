#pragma once

namespace UI
{
	WNDCLASS wClass;
	HWND hWindow;
	IDirect3D9* pD3D;
	IDirect3DDevice9* pDevice;
	D3DPRESENT_PARAMETERS D3DPP;

    bool CreateD3D()
    {
        if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == 0)
            return false;

        ZeroMemory(&D3DPP, sizeof(D3DPP));
        D3DPP.Windowed = TRUE;
        D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
        D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
        D3DPP.EnableAutoDepthStencil = TRUE;
        D3DPP.AutoDepthStencilFormat = D3DFMT_D16;
        D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPP, &pDevice) < 0)
            return false;

        return true;
    }

    void CleanD3D()
    {
        if (pDevice)
        {
            pDevice->Release();
            pDevice = nullptr;
        }
        if (pD3D)
        {
            pD3D->Release();
            pD3D = nullptr;
        }
    }

    void ResetDevice()
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        if (pDevice->Reset(&D3DPP) == D3DERR_INVALIDCALL) IM_ASSERT(0);
        ImGui_ImplDX9_CreateDeviceObjects();
    }

    void DXInit()
    {
        ImGui_ImplDX9_Init(pDevice);
    }

    void DXNewFrame()
    {
        ImGui_ImplDX9_NewFrame();
    }

    void DXRenderData()
    {
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

    void DXShutdown()
    {
        ImGui_ImplDX9_Shutdown();
    }
}