#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include "3rdParty/ImGui/imgui.h"
#include "3rdParty/ImGui/imgui_internal.h"
#include "3rdParty/ImGui/imgui_impl_dx9.h"
#include "3rdParty/ImGui/OTUI.hpp"
#include "3rdParty/ImGui/Icons.h"

const char* m_pUser = "sneakyevil.eu";
namespace EndScene
{
    bool m_bInit = true;
    bool m_bMenuOpen = true;

    typedef long(__stdcall* tHook)(IDirect3DDevice9*); tHook oHook;
    long __stdcall Hook(IDirect3DDevice9* pDevice)
    {
        UI::pDevice = pDevice;
        if (m_bInit)
        {
            UI::Categories::pIconsData = reinterpret_cast<void*>(Icons_compressed_data);
            UI::Categories::iIconsData = Icons_compressed_size;

            UI::ImGuiSetup(nullptr, nullptr, "onetap");
            UI::Tabs::Add("Rage");
            UI::Tabs::Add("Legit");
            UI::Tabs::Add("Anti-Aim");
            UI::Tabs::Add("Visuals");
            UI::Tabs::Add("Misc");
            UI::SetBottomInfo(m_pUser);

            UI::SetGeneralColor(ImGui::ColorConvertFloat4ToU32(ImVec4(0.83f, 0.62f, 0.40f, 1.f)));
            m_bInit = false;
        }


        static IDirect3DVertexDeclaration9* pVertexDeclaration;
        static IDirect3DVertexShader9* pVertexShader;
        pDevice->GetVertexDeclaration(&pVertexDeclaration);
        pDevice->GetVertexShader(&pVertexShader);

        static DWORD dColor = 0, dSRGB = 0;
        pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dColor);
        pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &dSRGB);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
        pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

        static DWORD dSamplerU = 0, dSamplerV = 0, dSamplerW = 0, dSamplerSRGB = 0;
        pDevice->GetSamplerState(0, D3DSAMP_ADDRESSU, &dSamplerU);
        pDevice->GetSamplerState(0, D3DSAMP_ADDRESSV, &dSamplerV);
        pDevice->GetSamplerState(0, D3DSAMP_ADDRESSW, &dSamplerW);
        pDevice->GetSamplerState(0, D3DSAMP_SRGBTEXTURE, &dSamplerSRGB);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);

        if (true)
        {
            UI::DrawPreBegin();

            if (true) // Watermark
            {
                static char cTime[10];
                static struct tm tTime;
                time_t tNow = time(0);
                localtime_s(&tTime, &tNow);
                strftime(cTime, sizeof(cTime), "%H:%M:%S", &tTime);

                UI::sWatermark += " [dev]";
                UI::AddToWatermark(m_pUser);
                UI::AddToWatermark(cTime);
                UI::DrawWatermark();
            }

            if (m_bMenuOpen && UI::DrawBegin(true))
            {
                static int m_iCategory = 0;
                UI::Categories::Add("SELF", "1");
                UI::Categories::Add("ENEMIES", "3");
                UI::Categories::Add("TEAMMATES", "2");
                UI::Categories::Add("WORLD", "0");
                UI::Categories::Add("OTHER", "8");
                UI::Categories::Draw(&m_iCategory);

                if (UI::GroupBox::Add("Left", 120.f, false))
                {
                    static bool m_bCheckbox = false;
                    UI::Item::Checkbox("Checkbox", &m_bCheckbox);

                    static float m_fColorPicker[4] = { 1.f, 1.f, 1.f, 1.f };
                    UI::Item::ColorPicker(m_fColorPicker, true);

                    static int m_iSlider = 50;
                    UI::Item::Slider("Slider", &m_iSlider, 0, 100, "%");
                }

                if (UI::GroupBox::Add("Right", 120.f, true))
                {
                    static int m_iCombo = 0;
                    static const char* m_aCombo[] = { "0", "1", "2", "3" };
                    UI::Item::Combo("Combo", &m_iCombo, m_aCombo, IM_ARRAYSIZE(m_aCombo));
                }
            }

            UI::DrawEnd(false, false);
        }

        pDevice->SetVertexDeclaration(pVertexDeclaration);
        pDevice->SetVertexShader(pVertexShader);

        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dColor);
        pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, dSRGB);

        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, dSamplerU);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, dSamplerV);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, dSamplerW);
        pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, dSamplerSRGB);

        return oHook(pDevice);
    }
}