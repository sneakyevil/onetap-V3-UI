#pragma once

namespace UI
{
    WNDCLASS wClass;
    HWND hWindow;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwap;
	ID3D11RenderTargetView* pRender;
    void CreateRender()
    {
        ID3D11Texture2D* pBackBuffer;
        pSwap->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        if (pBackBuffer)
        {
            pDevice->CreateRenderTargetView(pBackBuffer, 0, &pRender);
            pBackBuffer->Release();
        }
    }

    bool CreateD3D()
    {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWindow;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwap, &pDevice, &featureLevel, &pDeviceContext) != S_OK)
            return false;

        CreateRender();
        return true;
    }

    void CleanRender()
    {
        if (pRender)
        {
            pRender->Release();
            pRender = nullptr;
        }
    }

    void CleanD3D()
    {
        CleanRender();
        if (pSwap)
        {
            pSwap->Release();
            pSwap = nullptr;
        }
        if (pDeviceContext)
        {
            pDeviceContext->Release();
            pDeviceContext = nullptr;
        }
        if (pDevice)
        {
            pDevice->Release();
            pDevice = nullptr;
        }
    }

    void DXInit()
    {
        ImGui_ImplDX11_Init(pDevice, pDeviceContext);
    }

	void DXNewFrame()
	{
		ImGui_ImplDX11_NewFrame();
	}

	void DXRenderData()
	{
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void DXShutdown()
	{
		ImGui_ImplDX11_Shutdown();
	}
}