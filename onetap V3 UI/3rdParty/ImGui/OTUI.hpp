#pragma once
#if defined(OTDX11)
#include "OTDX11.hpp"
#else
#include "OTDX9.hpp"
#endif
#include "OTFonts.hpp"
#include <iomanip>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace UI
{
    char* pWindowName;

    ULONGLONG uCurTickCount;
    ImGuiWindow* pWindow;
    ImDrawList* pDraw, *pForegroundDraw;

    ImVec2 iWindowPos;
    ImVec2 iWindowSize;
    ImRect iWindowBB;

    ImVec2 iDrawPos;

    unsigned int iItemID;
    std::string sItemID;
    std::string GetID()
    {
        sItemID = "##" + std::to_string(iItemID);
        iItemID++;
        return sItemID;
    }

    namespace Tabs
    {
        int iSelected;
        struct Tab
        {
            std::string sName;
            ULONGLONG uLastFadeUpdate = 0;
            unsigned char cAlpha = 0;
        };
        std::vector<Tab> vData;
        size_t sSize;

        void Add(std::string sName)
        {
            vData.emplace_back(Tab());
            vData[sSize].sName = sName;
            if (sSize == 0) vData[sSize].cAlpha = 255; // Because first tab
            sSize++;
        }
    }

    namespace KeyBind
    {
        const char* const cKeyNames[] = { "OFF", "M1", "M2", "Cancel", "M3", "M4", "M5", "UNK",
        "Back", "Tab", "UNK", "UNK", "Clear", "Return", "UNK", "UNK", "Shift", "CTRL", "ALT", "Pause",
        "Capital", "Kana", "UNK", "Junja", "Final", "Kanji", "UNK", "ESC", "Convert", "Nonconvert", "Accept",
        "Modechange", "Space","Prior", "Next", "End", "Home", "Left", "Up", "Right", "Down", "Select", "Print", "Execute",
        "Snapshot", "Insert", "Delete", "Help", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "UNK", "UNK",
        "UNK", "UNK", "UNK", "UNK", "UNK", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Win", "Rigth Win", "Apps",
        "UNK", "Sleep", "N0", "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8", "N9",
        "Mutiply", "Add", "Separator", "Subtract", "Decimal", "Divide", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
        "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
        "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "Num Lock", "Scrool",
        "Equal", "Masshou", "Touroku", "Loya", "Roya", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK",
        "UNK", "UNK", "UNK", " LShift", "RShift", "LCTRL", "RCTRL", "LALT", "RALT"
        };

        int* pKey = nullptr;
        int* pKeyType = nullptr;
        bool bKeyTypeHovered[3] = { false, false, false };
        ImRect iKeyTypeBB;
    }

    namespace Sliders
    {
        std::string sInfo;
        ImRect iBB;
        ImVec2 iPos;
        float fTextWidth;
        ULONGLONG uLastFadeUpdate;
        void* pWindow;
        unsigned char cAlpha;
    }

    namespace Combos
    {
        void* pWindow;
        int iCount;
        ImRect iBB;
    }

    namespace GroupBox
    {
        float fWidth;
        ImVec2 iPos[2];
        float fLongestY;
        float* pDynamic = nullptr;

        bool Add(const char* cName, float fHeight, bool bRightSide)
        {
            pDynamic = nullptr;

            fWidth = ((iWindowBB.Max.x - 15.f) - (iWindowBB.Min.x + 15.f)) * 0.5f - 15.f;
            if (bRightSide)
            {
                iPos[1].x = iPos[0].x + fWidth + 20.f;
            }
            pDraw->AddRect(iPos[bRightSide], ImVec2(iPos[bRightSide].x + fWidth, iPos[bRightSide].y + fHeight), IM_COL32(55, 60, 65, 255), 5.f, ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight);
            pDraw->AddLine(iPos[bRightSide], ImVec2(iPos[bRightSide].x + fWidth, iPos[bRightSide].y), IM_COL32(44, 49, 55, 255)); // Remove Upper Line (Bruh)
            const float fTextWidth = ImGui::CalcTextSize(cName).x;
            const float fTextCenter = iPos[bRightSide].x + (fWidth * 0.5f) - (fTextWidth * 0.5f);
            ImGui::SetCursorPos(ImVec2(fTextCenter - iWindowPos.x, iPos[bRightSide].y - 10.f + pWindow->Scroll.y - iWindowPos.y));
            ImGui::Text(cName);

            ImVec4 iTop = ImGui::GetStyleColorVec4(ImGuiCol_TitleBg);
            iTop.x *= 1.5f;
            if (iTop.x > 1.f) iTop.x = 1.f;
            iTop.y *= 1.5f;
            if (iTop.y > 1.f) iTop.y = 1.f;
            iTop.z *= 1.5f;
            if (iTop.z > 1.f) iTop.z = 1.f;
            ImU32 iTop32 = ImGui::ColorConvertFloat4ToU32(iTop);
            pDraw->AddRectFilledMultiColor(ImVec2(iPos[bRightSide].x, iPos[bRightSide].y), ImVec2(fTextCenter - 5.f, iPos[bRightSide].y + 1.f), ImGui::GetColorU32(ImGuiCol_TitleBg), iTop32, iTop32, ImGui::GetColorU32(ImGuiCol_TitleBg));
            pDraw->AddRectFilledMultiColor(ImVec2(fTextCenter + fTextWidth + 5.f, iPos[bRightSide].y), ImVec2(iPos[bRightSide].x + fWidth, iPos[bRightSide].y + 1.f), iTop32, ImGui::GetColorU32(ImGuiCol_TitleBg), ImGui::GetColorU32(ImGuiCol_TitleBg), iTop32);
            iDrawPos = iPos[bRightSide];
            iDrawPos.x += 8.f;
            iDrawPos.y += 12.f;
            iPos[bRightSide].y += fHeight + 15.f;
            if (iPos[bRightSide].y > fLongestY) fLongestY = iPos[bRightSide].y + 15.f;

            return true;
        }

        bool AddDynamic(const char* cName, float* pValue, bool bRightSide)
        {
            Add(cName, *pValue, bRightSide);
            *pValue = 8.f;
            pDynamic = pValue;

            return true;
        }

        void AddHeight(float fHeight, bool bCheck = true)
        {
            if (!bCheck || !pDynamic) return;

            *pDynamic += fHeight;
        }
    }

    namespace ButtonBehavior
    {
        bool Add(ImRect bb, ImGuiID id, bool* out_hovered, bool* out_held, ImGuiButtonFlags flags = 0)
        {
            const float fMinimumY = iWindowPos.y + 66.f;
            const float fMaximumY = iWindowBB.Max.y - 28.f;

            if (fMinimumY > bb.Min.y) bb.Min.y = fMinimumY;
            if (bb.Min.y > fMaximumY) bb.Min.y = fMaximumY;

            if (fMinimumY > bb.Max.y) bb.Max.y = fMinimumY;
            if (bb.Max.y > fMaximumY) bb.Max.y = fMaximumY;

            return ImGui::ButtonBehavior(bb, id, out_hovered, out_held, 0);
        }
    }

    namespace Categories
    {
        struct sCategories
        {
            std::string sName;
            std::string sIcon;
            ImVec2 iSize;
            float fTextSize = 0.f;
            float fTotalWidth = 0.f;
        };
        size_t sData = 0;
        std::vector<sCategories> vData;

        void* pIconsData = nullptr;
        int iIconsData = 0;
        ImFont* pIcons;
        void Add(std::string sName, std::string sIcon)
        {
            vData.emplace_back(sCategories());
            vData[sData].sName = sName;
            vData[sData].sIcon = sIcon;
            if (!sIcon.empty() && pIcons)
            {
                ImGui::PushFont(pIcons);
                vData[sData].iSize = ImGui::CalcTextSize(sIcon.c_str());
                ImGui::PopFont();
            }

            sData++;
        }

        ImFont* pFont;
        ImVec4 iColor[] = { ImVec4(0.31f, 0.31f, 0.31f, 1.f), ImVec4(1.f, 1.f, 1.f, 1.f) };
        int Draw(int *pInt)
        {
            GroupBox::iPos[0].y += 53.f;
            GroupBox::iPos[1].y += 53.f;

            iDrawPos.y -= 10.f;
            const ImRect iCategories(iDrawPos, ImVec2(iDrawPos.x + iWindowSize.x - 40.f, iDrawPos.y + 50.f));
            pDraw->AddRectFilled(iCategories.Min, iCategories.Max, IM_COL32(30, 33, 36, 255), 3.f);
            pDraw->AddRect(ImVec2(iCategories.Min.x + 1.f, iCategories.Min.y + 1.f), ImVec2(iCategories.Max.x - 1.f, iCategories.Max.y - 1.f), IM_COL32(36, 39, 42, 255), 3.f);

            if (static_cast<size_t>(*pInt) > sData) *pInt = 0;
            if (sData > 0)
            {
                ImGui::PushFont(pFont);

                const float fAvailableSpace = iCategories.Max.x - iCategories.Min.x;
                float fTotalUsedSpace = 0.f;
                for (size_t i = 0; sData > i; ++i)
                {
                    vData[i].fTextSize = ImGui::CalcTextSize(vData[i].sName.c_str()).x;
                    vData[i].fTotalWidth = vData[i].fTextSize > vData[i].iSize.x ? vData[i].fTextSize : vData[i].iSize.x;
                    fTotalUsedSpace += vData[i].fTotalWidth;
                }

                ImGui::PopFont();

                float fItemSpacing = (fAvailableSpace - fTotalUsedSpace) / static_cast<float>(sData + 1);
                float fItemStart = iCategories.Min.x + fItemSpacing;
                for (size_t i = 0; sData > i; ++i)
                {
                    const ImRect iCategoryBB(ImVec2(fItemStart - 5.f, iCategories.Min.y + 3.f), ImVec2(fItemStart + vData[i].fTotalWidth + 5.f, iCategories.Max.y - 3.f));

                    const ImGuiID iCategoryID = pWindow->GetID(&vData[i].sName);
                    if (ImGui::ItemAdd(iCategoryBB, iCategoryID))
                    {
                        static bool bHovered = false, bHeld = false;
                        const ImRect iCategoryButton(ImVec2(iCategoryBB.Min.x, iCategoryBB.Min.y), ImVec2(iCategoryBB.Max.x, iCategoryBB.Max.y));
                        if (ButtonBehavior::Add(iCategoryButton, iCategoryID, &bHovered, &bHeld, 0))
                        {
                            *pInt = static_cast<int>(i);
                            ImGui::SetScrollY(0.f);
                        }
                        const bool bHighlight = *pInt == static_cast<int>(i) || bHovered;

                        ImGui::PushStyleColor(ImGuiCol_Text, iColor[bHighlight]);

                        if (vData[i].iSize.x > 0.f)
                        {
                            const ImVec2 iImageStart = ImVec2(iCategoryBB.Min.x + ((iCategoryBB.Max.x - iCategoryBB.Min.x) * 0.5f) - (vData[i].iSize.x * 0.5f), iCategories.Max.y - 20.f - vData[i].iSize.y);
                            ImGui::SetCursorPos(ImVec2(iImageStart.x - iWindowPos.x, iImageStart.y + pWindow->Scroll.y - iWindowPos.y));
                            ImGui::PushFont(pIcons);
                            ImGui::Text(vData[i].sIcon.c_str());
                            ImGui::PopFont();
                        }

                        const ImVec2 iTextStart = ImVec2(iCategoryBB.Min.x + ((iCategoryBB.Max.x - iCategoryBB.Min.x) * 0.5f) - (vData[i].fTextSize * 0.5f), iCategories.Max.y - 20.f);
                        ImGui::SetCursorPos(ImVec2(iTextStart.x - iWindowPos.x, iTextStart.y + pWindow->Scroll.y - iWindowPos.y));
                        ImGui::PushFont(pFont);
                        ImGui::Text(vData[i].sName.c_str());
                        ImGui::PopFont();

                        ImGui::PopStyleColor();
                    }

                    fItemStart += vData[i].fTotalWidth + fItemSpacing;
                }

                sData = 0;
                vData.clear();
            }

            return *pInt;
        }
    }

    namespace ColorPicker
    {
        int Inline;
        unsigned int uLastIDWithText = 0U;
    }

    namespace Item
    {
        static bool bHovered, bHeld, bPressed;
        void Text(const char* cName)
        {
            ImGui::SetCursorPos(ImVec2(iDrawPos.x - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));
            ImGui::Text(cName);
            iDrawPos.y += 16.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 16.f;
        }

        void Checkbox(const char* cName, bool* pBool)
        {
            ColorPicker::Inline = 0;
            const ImRect iCheckbox(iDrawPos, ImVec2(iDrawPos.x + 24.f + ImGui::CalcTextSize(cName).x, iDrawPos.y + 12.f));
            const ImGuiID iCheckboxID = pWindow->GetID(GetID().c_str());
            if (ImGui::ItemAdd(iCheckbox, iCheckboxID))
            {
                bPressed = ButtonBehavior::Add(iCheckbox, iCheckboxID, &bHovered, &bHeld);
                if (bPressed)
                {
                    *pBool = !(*pBool);
                    ImGui::MarkItemEdited(iCheckboxID);
                }
            }
            pDraw->AddRectFilled(iDrawPos, ImVec2(iDrawPos.x + 12.f, iDrawPos.y + 12.f), *pBool || bHovered ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iDrawPos.x + 1.f, iDrawPos.y + 1.f), ImVec2(iDrawPos.x + 11.f, iDrawPos.y + 11.f), *pBool ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(32, 33, 36, 255), 3.f);
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y - 4.f + pWindow->Scroll.y - iWindowPos.y));
            ImGui::Text(cName);
            iDrawPos.y += 20.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 20.f;
        }

        /* Sliders & Fuck ImGui */

        void DrawSliderName(const char* cName)
        {
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));
            ImGui::Text(cName);
        }

        void DrawSlider(ImRect iSlider)
        {
            pDraw->AddRectFilled(iSlider.Min, iSlider.Max, IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iSlider.Min.x + 1.f, iSlider.Min.y + 1.f), ImVec2(iSlider.Max.x - 1.f, iSlider.Max.y - 1.f), IM_COL32(32, 33, 36, 255), 3.f);
        }

        void DrawSliderFill(ImRect iSlider, float fValue, float fMin, float fMax)
        {
            iSlider.Min.x++;
            iSlider.Min.y++;
            iSlider.Max.x--;
            iSlider.Max.y--;
            if (0.f > fMin)
            {
                fMin = std::fabsf(fMin);
                fValue += fMin;
                fMax += fMin;
            }
            else if (fMin > 0.f)
            {
                fMin = std::fabsf(fMin);
                fValue -= fMin;
                fMax -= fMin;
            }
            pDraw->AddRectFilled(iSlider.Min, ImVec2(iSlider.Min.x + ((iSlider.Max.x - iSlider.Min.x) * (fValue / fMax)), iSlider.Max.y), ImGui::GetColorU32(ImGuiCol_TitleBg), 3.f);
        }

        float GetSliderValue(ImRect iSlider, float fMin, float fMax)
        {
            float fPercentage = (ImGui::GetMousePos().x - iSlider.Min.x) / (iSlider.Max.x - iSlider.Min.x);
            float fRet = ((fMax - fMin) * fPercentage) + fMin;
            if (fRet > fMax) fRet = fMax;
            else if (fMin > fRet) fRet = fMin;
            return fRet;
        }

        void UpdateSliderFloat(float fValue)
        {
            std::stringstream sTemp; sTemp << std::fixed << std::setprecision(2) << fValue;
            Sliders::sInfo = sTemp.str();
        }

        void UpdateSliderDrawing(ImRect iSlider)
        {
            Sliders::iBB = iSlider;
            Sliders::iPos.x = ImGui::GetMousePos().x + 8.f;
            Sliders::iPos.y = iSlider.Max.y + 3.f;
            Sliders::fTextWidth = ImGui::CalcTextSize(Sliders::sInfo.c_str()).x;
        }

        void UpdateSliderInfo(ImRect iSlider, float fValue, std::string sType = "")
        {
            UpdateSliderFloat(fValue);
            Sliders::sInfo += sType;
            UpdateSliderDrawing(iSlider);
        }

        void UpdateSliderInfo(ImRect iSlider, int iValue, std::string sType = "")
        {
            Sliders::sInfo = std::to_string(iValue) + sType;
            UpdateSliderDrawing(iSlider);
        }

        void Slider(const char* cName, int* pInt, int iMin, int iMax, std::string sType = "")
        {
            iDrawPos.y -= 4.f;

            if (iMin > * pInt) *pInt = iMin;
            else if (*pInt > iMax) *pInt = iMax;

            const bool bHasName = cName[0] != '#';
            if (!bHasName) iDrawPos.y -= 21.f;

            const ImRect iSlider(ImVec2(iDrawPos.x + 14.f, iDrawPos.y + 22.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + 30.f));
            const ImGuiID iSliderID = pWindow->GetID(GetID().c_str());

            if (bHasName) DrawSliderName(cName);
            DrawSlider(iSlider);
            static float fFloat, fMin, fMax;
            fFloat = static_cast<float>(*pInt);
            fMin = static_cast<float>(iMin);
            fMax = static_cast<float>(iMax);
            DrawSliderFill(iSlider, fFloat, fMin, fMax);
            if (ImGui::ItemAdd(iSlider, iSliderID))
            {
                ButtonBehavior::Add(iSlider, iSliderID, &bHovered, &bHeld);
                if (bHeld) *pInt = static_cast<int>(GetSliderValue(iSlider, fMin, fMax));
                if (bHovered || bHeld)
                {
                    UpdateSliderInfo(iSlider, *pInt, sType);
                    Sliders::uLastFadeUpdate = uCurTickCount + 15;
                    Sliders::pWindow = pWindow;
                    Sliders::cAlpha = 255;
                }
            }
            iDrawPos.y += 38.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += bHasName ? 34.f : 13.f;
        }

        void Slider(const char* cName, float* pFloat, float fMin, float fMax, std::string sType = "")
        {
            iDrawPos.y -= 4.f;

            if (fMin > * pFloat) *pFloat = fMin;
            else if (*pFloat > fMax) *pFloat = fMax;

            const bool bHasName = cName[0] != '#';
            if (!bHasName) iDrawPos.y -= 21.f;

            const ImRect iSlider(ImVec2(iDrawPos.x + 14.f, iDrawPos.y + 22.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + 30.f));
            const ImGuiID iSliderID = pWindow->GetID(GetID().c_str());

            if (bHasName) DrawSliderName(cName);
            DrawSlider(iSlider);
            DrawSliderFill(iSlider, *pFloat, fMin, fMax);
            if (ImGui::ItemAdd(iSlider, iSliderID))
            {
                ButtonBehavior::Add(iSlider, iSliderID, &bHovered, &bHeld);
                if (bHeld) *pFloat = GetSliderValue(iSlider, fMin, fMax);
                if (bHovered || bHeld)
                {
                    UpdateSliderInfo(iSlider, *pFloat, sType);
                    Sliders::uLastFadeUpdate = uCurTickCount + 15;
                    Sliders::pWindow = pWindow;
                    Sliders::cAlpha = 255;
                }
            }
            iDrawPos.y += 38.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += bHasName ? 34.f : 13.f;
        }

        void DrawCombo(const char* cName, const char* cPreviewName)
        {
            ColorPicker::Inline = 0;

            iDrawPos.y -= 4.f;
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));
            ImGui::Text(cName);
            pDraw->AddRectFilled(ImVec2(iDrawPos.x + 12.f, iDrawPos.y + 20.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + 43.f), IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iDrawPos.x + 13.f, iDrawPos.y + 21.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 32.f, iDrawPos.y + 42.f), IM_COL32(32, 33, 36, 255), 3.f);
            pDraw->AddTriangleFilled(ImVec2(iDrawPos.x + GroupBox::fWidth - 44.f, iDrawPos.y + 27.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 36.f, iDrawPos.y + 27.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 40.f, iDrawPos.y + 35.f), IM_COL32_WHITE);
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 22.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y + 21.f));
            ImGui::Text(cPreviewName);
            ImGui::SetNextItemWidth(GroupBox::fWidth - 50.f);
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y + 18.f));
        }

        void DrawComboBG(int iCount)
        {
            Combos::pWindow = pWindow;
            Combos::iCount = iCount;
            Combos::iBB.Min = ImVec2(iDrawPos.x + 13.f, iDrawPos.y + 21.f);
            Combos::iBB.Max = ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + 43.f);
            float fHeight = 3.f + static_cast<float>(22.f * Combos::iCount);
            pForegroundDraw->AddRect(ImVec2(Combos::iBB.Min.x - 1.f, Combos::iBB.Max.y + 1.f), ImVec2(Combos::iBB.Max.x + 1.f, Combos::iBB.Max.y + fHeight + 1.f), IM_COL32(55, 60, 65, 255));
            pForegroundDraw->AddRectFilled(ImVec2(Combos::iBB.Min.x, Combos::iBB.Max.y + 2.f), ImVec2(Combos::iBB.Max.x, Combos::iBB.Max.y + fHeight), IM_COL32(32, 33, 36, 255));
        }

        void DrawComboHover()
        {
            pDraw->AddRect(ImVec2(iDrawPos.x + 12.f, iDrawPos.y + 20.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + 43.f), ImGui::GetColorU32(ImGuiCol_TitleBg), 3.f);
        }

        void Combo(const char* cName, int* pInt, const char* const cItems[], int iCount)
        {
            DrawCombo(cName, cItems[*pInt]);
            int iMaxCount = iCount > 8 ? 8 : iCount;

            static unsigned int uLastID = 0U;
            static bool bWasScrollSet = false;
            unsigned int uCurrentID = iItemID;
            if (ImGui::BeginCombo(GetID().c_str(), cName))
            {
                DrawComboHover();
                if (20.f >= ImGui::GetWindowPos().x - UI::iDrawPos.x)
                {
                    DrawComboBG(iMaxCount);
                    if (ImGui::GetCurrentWindow()->ScrollbarY) ImGui::Scrollbar(ImGuiAxis_Y);
                    for (int i = 0; iCount > i; ++i)
                    {
                        if (ImGui::Selectable(cItems[i], *pInt == i)) *pInt = i;
                        if (*pInt == i && !bWasScrollSet)
                        {
                            ImGui::SetScrollHereY(0.025f);
                            bWasScrollSet = true;
                        }
                    }
                }
                ImGui::EndCombo();

                uLastID = uCurrentID;
            }
            else
            {
                if (ImGui::IsItemHovered()) DrawComboHover();
                if (uLastID == uCurrentID) bWasScrollSet = false;
            }
            iDrawPos.y += 48.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 45.f;
        }

        float CalcMaxPopupHeightFromItemCount(int items_count)
        {
            ImGuiContext& g = *GImGui;
            return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2) - 5.f;
        }

        void ComboMulti(const char* cName, const char* cDefaultPreviewName, int* pInt, const char* const cItems[], int iCount)
        {
            static std::string sSelected; sSelected.clear();
            static const float fComboMaxTextWidth = (iDrawPos.x + GroupBox::fWidth - 51.f) - iDrawPos.x - 60.f;
            for (int i = 0; iCount > i; ++i)
            {
                if (!(*pInt & 1 << i)) continue;

                if (!sSelected.empty()) sSelected += ", ";
                if (ImGui::CalcTextSize(std::string(sSelected + cItems[i]).c_str()).x > fComboMaxTextWidth)
                {
                    sSelected += "...";
                    break;
                }
                else sSelected += cItems[i];
            }
            DrawCombo(cName, sSelected.empty() ? cDefaultPreviewName : sSelected.c_str());
            int iMaxCount = iCount > 8 ? 8 : iCount;
            ImGui::SetNextWindowSizeConstraints(ImVec2(), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(iMaxCount + 1)));
            if (ImGui::BeginCombo(GetID().c_str(), cName))
            {
                DrawComboHover();
                if (20.f >= ImGui::GetWindowPos().x - UI::iDrawPos.x)
                {
                    DrawComboBG(iMaxCount);
                    if (ImGui::GetCurrentWindow()->ScrollbarY) ImGui::Scrollbar(ImGuiAxis_Y);
                    for (int i = 0; iCount > i; ++i)
                    {
                        if (ImGui::Selectable(cItems[i], *pInt & 1 << i, ImGuiSelectableFlags_DontClosePopups))
                        {
                            if (*pInt & 1 << i) *pInt &= ~(1 << i);
                            else *pInt |= 1 << i;
                        }
                    }
                }
                ImGui::EndCombo();
            }
            else if (ImGui::IsItemHovered()) DrawComboHover();
            iDrawPos.y += 48.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 45.f;
        }

        void Listbox(const char* cName, int* pInt, const char* const cItems[], int iCount, float fHeight)
        {
            int iMaxCount = iCount;
            while (iDrawPos.y + 3.f + static_cast<float>(22.f * iMaxCount) > iDrawPos.y + fHeight) --iMaxCount;
            pDraw->AddRectFilled(ImVec2(iDrawPos.x + 12.f, iDrawPos.y + 5.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 31.f, iDrawPos.y + fHeight), IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iDrawPos.x + 13.f, iDrawPos.y + 6.f), ImVec2(iDrawPos.x + GroupBox::fWidth - 32.f, iDrawPos.y + fHeight - 1.f), IM_COL32(50, 55, 60, 255), 3.f);
            ImGui::SetNextItemWidth(GroupBox::fWidth - 50.f);
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y + 5.f));
            ImGui::ListBox(cName, pInt, cItems, iCount, iMaxCount);
            iDrawPos.y += 10.f + fHeight;
        }

        int iInputTextInLine = 0;
        int iInputTextInLineCounter = 0;
        void InputTextsInline(int iCount)
        {
            iInputTextInLine = iCount;
            iInputTextInLineCounter = 0;
        }

        void InputText(const char* cName, char* pInput, size_t sInput, ImGuiInputTextFlags iFlags = 0)
        {
            float fDrawX = iDrawPos.x;
            float fInputTextWidth = GroupBox::fWidth - 32.f;
            if (iInputTextInLine > iInputTextInLineCounter)
            {
                fInputTextWidth = (fInputTextWidth / iInputTextInLine) - (static_cast<float>(iInputTextInLine - 1));
                if (iInputTextInLineCounter > 0) iDrawPos.y -= 48.f;
                fDrawX += (fInputTextWidth * iInputTextInLineCounter) + (iInputTextInLineCounter);
                iInputTextInLineCounter++;
            }
            if (cName[0] != '\0')
            {
                ImGui::SetCursorPos(ImVec2(fDrawX + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));
                ImGui::Text(cName);
                iDrawPos.y += 20.f;
            }
            pDraw->AddRectFilled(ImVec2(fDrawX + 13.f, iDrawPos.y + 1.f), ImVec2(fDrawX + fInputTextWidth, iDrawPos.y + 22.f), IM_COL32(32, 33, 36, 255), 3.f);
            ImGui::SetCursorPos(ImVec2(fDrawX + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y - 1.f));
            ImGui::SetNextItemWidth(fInputTextWidth - 23.f);
            ImGui::InputText(cName, pInput, sInput, iFlags);
            pDraw->AddRect(ImVec2(fDrawX + 12.f, iDrawPos.y), ImVec2(fDrawX + fInputTextWidth + 1.f, iDrawPos.y + 23.f), ImGui::IsItemHovered() || ImGui::IsItemActive() ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(55, 60, 65, 255), 3.f);
            iDrawPos.y += 28.f;

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 48.f;
        }

        int iButtonsInLine;
        int iButtonsInLineCounter;
        void ButtonsInline(int iCount)
        {
            iButtonsInLine = iCount;
            iButtonsInLineCounter = 0;
        }

        bool Button(const char* cName)
        {
            float fDrawX = iDrawPos.x;
            float fButtonWidth = GroupBox::fWidth - 32.f;

            const bool bButtonsInLine = iButtonsInLine > iButtonsInLineCounter;
            if (bButtonsInLine)
            {
                fButtonWidth = (fButtonWidth / iButtonsInLine) - (static_cast<float>(iButtonsInLine - 1));
                if (iButtonsInLineCounter > 0) iDrawPos.y -= 28.f;
                fDrawX += (fButtonWidth * iButtonsInLineCounter) + (iInputTextInLineCounter);
                iButtonsInLineCounter++;
            }

            const ImRect iButton(ImVec2(bButtonsInLine && iButtonsInLineCounter > 1 ? fDrawX + 5.f : fDrawX + 12.f, iDrawPos.y), ImVec2(fDrawX + fButtonWidth + 1.f, iDrawPos.y + 23.f));
            const ImGuiID iButtonID = pWindow->GetID(GetID().c_str());
            if (ImGui::ItemAdd(iButton, iButtonID))
            {
                bPressed = ButtonBehavior::Add(iButton, iButtonID, &bHovered, &bHeld);
                if (bPressed) ImGui::MarkItemEdited(iButtonID);
            }
            pDraw->AddRectFilled(iButton.Min, iButton.Max, bHovered ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iButton.Min.x + 1.f, iButton.Min.y + 1.f), ImVec2(iButton.Max.x - 1.f, iButton.Max.y - 1.f), IM_COL32(32, 33, 36, 255), 3.f);
            float fTextCenter = iButton.Min.x + ((iButton.Max.x - iButton.Min.x) * 0.5f) - (ImGui::CalcTextSize(cName).x * 0.5f);
            ImGui::SetCursorPos(ImVec2(fTextCenter - iWindowPos.x, iButton.Min.y + pWindow->Scroll.y + 1.f - iWindowPos.y));
            ImGui::Text(cName);
            iDrawPos.y += 28.f;
            return bPressed;
        }

        // Should be used only after Checkbox!
        void KeyBind(const char* cName, int* pKey, int* pKeyType = nullptr)
        {
            static const char* cWaitForInput = "...";

            iDrawPos.y -= 22.f;
            const float fDrawPosKey = iDrawPos.x + GroupBox::fWidth - 60.f;
            const ImRect iKeyBind(ImVec2(fDrawPosKey, iDrawPos.y), ImVec2(fDrawPosKey + 44.f, iDrawPos.y + 16.f));
            const ImGuiID iKeyBindID = pWindow->GetID(GetID().c_str());
            if (ImGui::ItemAdd(iKeyBind, iKeyBindID))
            {
                bPressed = ButtonBehavior::Add(iKeyBind, iKeyBindID, &bHovered, &bHeld);
                if (bPressed)
                {
                    KeyBind::pKey = pKey;
                    ImGui::MarkItemEdited(iKeyBindID);
                }
                else if (bHovered && pKeyType && ImGui::GetIO().MouseClicked[1])
                {
                    KeyBind::pKeyType = pKeyType;
                    KeyBind::iKeyTypeBB = ImRect(ImVec2(iKeyBind.Min.x, iKeyBind.Min.y), ImVec2(iKeyBind.Min.x + 64.f, iKeyBind.Min.y + 68.f));
                    if (KeyBind::iKeyTypeBB.Max.y > iWindowBB.Max.y - 40.f)
                    {
                        KeyBind::iKeyTypeBB.Min.y -= 52.f;
                        KeyBind::iKeyTypeBB.Max.y -= 52.f;
                    }
                    ImGui::MarkItemEdited(iKeyBindID);
                }
            }
            const bool bIsAlwaysOn = KeyBind::pKey != pKey && pKeyType && *pKeyType == 2;
            const char* pKeyBindText = KeyBind::pKey == pKey ? cWaitForInput : bIsAlwaysOn ? "ON" : KeyBind::cKeyNames[*pKey];

            pDraw->AddRectFilled(iKeyBind.Min, iKeyBind.Max, bHovered ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(55, 60, 65, 255), 3.f);
            pDraw->AddRectFilled(ImVec2(iKeyBind.Min.x + 1.f, iKeyBind.Min.y + 1.f), ImVec2(iKeyBind.Max.x - 1.f, iKeyBind.Max.y - 1.f), IM_COL32(32, 33, 36, 255), 3.f);
            const float fTextCenter = ((iKeyBind.Max.x - iKeyBind.Min.x) * 0.5f) - ImGui::CalcTextSize(pKeyBindText).x * 0.5f;
            ImGui::SetCursorPos(ImVec2(iKeyBind.Min.x + fTextCenter - iWindowPos.x, iKeyBind.Min.y - 2.f + pWindow->Scroll.y - iWindowPos.y));
            ImGui::TextColored(bIsAlwaysOn ? ImGui::GetStyleColorVec4(ImGuiCol_TitleBg) : ImGui::GetStyleColorVec4(ImGuiCol_Text),  pKeyBindText);
            iDrawPos.y += 22.f;
        }

        void KeyBindWithText(const char* cName, int* pKey, int* pKeyType = nullptr)
        {
            iDrawPos.y -= 4.f;
            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));

            size_t sHashTag = std::string(cName).find_first_of('#');
            if (sHashTag == std::string::npos) ImGui::Text(cName);
            else ImGui::Text(std::string(cName).substr(0, sHashTag).c_str());
            iDrawPos.y += 24.f;
            KeyBind(cName, pKey, pKeyType);

            if (GroupBox::pDynamic) *GroupBox::pDynamic += 24.f;
        }

        // Should be used only after Checkbox!
        void ColorPicker(float* pColor, bool bAlpha = false)
        {
            iDrawPos.y -= 27.f;
            ImVec2 iButton = ImVec2(iDrawPos.x + GroupBox::fWidth - 46.f - iWindowPos.x, iDrawPos.y - iWindowPos.y + 4.f);
            if (ColorPicker::Inline > 0) iButton.x -= ColorPicker::Inline * 32.f;
            ImGui::SetCursorPos(ImVec2(iButton.x, iButton.y + pWindow->Scroll.y)); // Fix ColorPicker button
            iButton.x += iWindowPos.x;
            iButton.y += iWindowPos.y;
            ImGuiColorEditFlags iFlags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip;
            if (bAlpha) iFlags |= ImGuiColorEditFlags_AlphaBar;
            bool bOpened = ImGui::ColorEdit4(GetID().c_str(), pColor, iFlags);
            if (bAlpha)
            {
                pDraw->AddRectFilled(ImVec2(iButton.x + 1.f, iButton.y + 1.f), ImVec2(iButton.x + 29.f, iButton.y + 17.f), IM_COL32(255, 255, 255, 255), 3.f);
                pDraw->AddRectFilled(ImVec2(iButton.x + 1.f, iButton.y + 1.f), ImVec2(iButton.x + 15.f, iButton.y + 9.f), IM_COL32(204, 204, 204, 255));
                pDraw->AddRectFilled(ImVec2(iButton.x + 15.f, iButton.y + 9.f), ImVec2(iButton.x + 29.f, iButton.y + 17.f), IM_COL32(204, 204, 204, 255));
            }
            pDraw->AddRectFilled(ImVec2(iButton.x + 1.f, iButton.y + 1.f), ImVec2(iButton.x + 29.f, iButton.y + 17.f), ImGui::ColorConvertFloat4ToU32(ImVec4(pColor[0], pColor[1], pColor[2], bAlpha ? pColor[3] : 1.f)), 3.f);
            pDraw->AddRect(iButton, ImVec2(iButton.x + 30.f, iButton.y + 18.f), ImGui::IsItemHovered() || bOpened ? ImGui::GetColorU32(ImGuiCol_TitleBg) : IM_COL32(55, 60, 65, 255), 3.f);
            iDrawPos.y += 27.f;
            ColorPicker::Inline++;
        }

        void ColorPickerAfterCombo(float* pColor, bool bAlpha = false)
        {
            iDrawPos.y -= 24.f; 
            ColorPicker(pColor, bAlpha);
            iDrawPos.y += 24.f;
        }

        void ColorPickerWithText(const char* cName, float* pColor, bool bAlpha = false)
        {
            iItemID++;
            if (iItemID > ColorPicker::uLastIDWithText && 2U >= iItemID - ColorPicker::uLastIDWithText) iDrawPos.y -= 4.f;
            ColorPicker::uLastIDWithText = iItemID;

            ImGui::SetCursorPos(ImVec2(iDrawPos.x + 18.f - iWindowPos.x, iDrawPos.y + pWindow->Scroll.y - iWindowPos.y));
            
            size_t sHashTag = std::string(cName).find_first_of('#');
            if (sHashTag == std::string::npos) ImGui::Text(cName);
            else ImGui::Text(std::string(cName).substr(0, sHashTag).c_str());
            iDrawPos.y += 24.f;
            ColorPicker::Inline = 0;
            ColorPicker(pColor, bAlpha);
        }
    }

    bool bUseWinWndProc = true;
    LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (KeyBind::pKey) // Handle KeyBind and disable ImGui Handler
        {
            int iKey = -1;
            if (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN)
            {
                int iExtended = (lParam & 0x1000000) != 0;
                switch (wParam)
                {
                case VK_SHIFT:
                    iKey = MapVirtualKeyA((lParam & 0xFF0000) >> 16, MAPVK_VSC_TO_VK_EX);
                    break;
                case VK_CONTROL:
                    iKey = iExtended ? VK_RCONTROL : VK_LCONTROL;
                    break;
                case VK_MENU:
                    iKey = iExtended ? VK_RMENU : VK_LMENU;
                    break;
                default:
                    iKey = wParam;
                    break;
                }
            }
            else if (uMsg == WM_LBUTTONDOWN) iKey = VK_LBUTTON;
            else if (uMsg == WM_RBUTTONDOWN) iKey = VK_RBUTTON;
            else if (uMsg == WM_MBUTTONDOWN) iKey = VK_MBUTTON;
            else if (uMsg == WM_XBUTTONDOWN) iKey = GET_XBUTTON_WPARAM(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
            if (iKey > -1)
            {
                if (iKey == VK_ESCAPE || iKey > sizeof(KeyBind::cKeyNames) / sizeof(*KeyBind::cKeyNames)) iKey = 0;
                *KeyBind::pKey = iKey;
                KeyBind::pKey = nullptr;
            }
        }
        else if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
        if (!bUseWinWndProc) return false;

        switch (uMsg)
        {
        case WM_SIZE:
            if (pDevice && wParam != SIZE_MINIMIZED)
            {
#if defined(OTDX11)

                CleanRender();
                pSwap->ResizeBuffers(0, UINT(LOWORD(lParam)), UINT(HIWORD(lParam)), DXGI_FORMAT_UNKNOWN, 0);
                CreateRender();
#else
                D3DPP.BackBufferWidth = LOWORD(lParam);
                D3DPP.BackBufferHeight = HIWORD(lParam);
                ResetDevice();
#endif
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_KEYMENU) return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProcA(hWnd, uMsg, wParam, lParam);
    }

    ImFont* pFont;
    ImFont* pFontTitle;
    ImFont* pFontTabs;
    bool InitFonts(ImGuiIO& io)
    {
        pFont = io.Fonts->AddFontFromMemoryCompressedTTF(uSegoui, uSegouiSize, 18.f); // Menu Items
        if (!pFont) return false;

        pFontTitle = io.Fonts->AddFontFromMemoryCompressedTTF(uTahomaBold, uTahomaBoldSize, 28.f); // Title
        if (!pFontTitle) return false;

        pFontTabs = io.Fonts->AddFontFromMemoryCompressedTTF(uSegouiBold, uSegouiBoldSize, 18.f); // Tabs
        if (!pFontTabs) return false;

        if (Categories::pIconsData && Categories::iIconsData > 0)
        {
            Categories::pIcons = io.Fonts->AddFontFromMemoryCompressedTTF(Categories::pIconsData, Categories::iIconsData, 24.f);
            if (!Categories::pIcons) return false;
        }

        Categories::pFont = io.Fonts->AddFontFromMemoryCompressedTTF(uSegoui, uSegouiSize, 13.f);
        if (!Categories::pFont) return false;

        return true;
    }

    bool ImGuiSetup(HINSTANCE hInstance, const char* cClass, std::string sWindowName, DWORD dStyle = WS_POPUP)
    {
        const size_t sSize = sWindowName.size();
        pWindowName = new char[sSize + 1];
        memcpy(pWindowName, &sWindowName[0], sSize);
        pWindowName[sSize] = '\0';

        if (hInstance)
        {
            wClass.lpfnWndProc = WNDPROC(WndProc);
            wClass.style = CS_HREDRAW | CS_VREDRAW;
            wClass.hInstance = hInstance;
            wClass.lpszClassName = cClass;
            wClass.hCursor = LoadCursor(0, IDC_ARROW);
            wClass.hbrBackground = HBRUSH(COLOR_APPWORKSPACE);
            RegisterClassA(&wClass);

            hWindow = CreateWindowA(wClass.lpszClassName, pWindowName, dStyle, 0, 0, 574, 461, 0, 0, wClass.hInstance, 0);
            if (!CreateD3D())
            {
                MessageBoxA(0, "Couldn't create D3D!", "", MB_OK | MB_ICONERROR);
                CleanD3D();
                UnregisterClassA(wClass.lpszClassName, wClass.hInstance);
                return false;
            }

            ShowWindow(hWindow, SW_SHOWDEFAULT);
            UpdateWindow(hWindow);
        }

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = 0; // Disable ImGui.ini

        if (!InitFonts(io))
        {
            MessageBoxA(0, "Couldn't init fonts!", "", MB_OK | MB_ICONERROR);
            ImGui::DestroyContext();
            if (wClass.hInstance)
            {
                CleanD3D();
                UnregisterClassA(wClass.lpszClassName, wClass.hInstance);
            }
        }

        ImGuiStyle* pStyle = &ImGui::GetStyle();
        pStyle->WindowRounding = 0.f;
        pStyle->ScrollbarRounding = 0.f;
        pStyle->ScrollbarSize = 0.1f;
        pStyle->Colors[ImGuiCol_Text] = ImGui::ColorConvertU32ToFloat4(IM_COL32(215, 215, 220, 255));
        pStyle->Colors[ImGuiCol_PopupBg] = ImVec4(0.f, 0.f, 0.f, 1.f);
        pStyle->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
        pStyle->Colors[ImGuiCol_FrameBg] = ImVec4(0.f, 0.f, 0.f, 0.f);

        ImGui_ImplWin32_Init(hWindow);
        DXInit();
        return true;
    }

    ImU32 uGeneralColor;
    void SetGeneralColor(ImU32 iCol)
    {
        uGeneralColor = iCol;

        ImGuiStyle* pStyle = &ImGui::GetStyle();
        pStyle->Colors[ImGuiCol_TitleBg] = ImGui::ColorConvertU32ToFloat4(iCol);
        pStyle->Colors[ImGuiCol_TextSelectedBg] = pStyle->Colors[ImGuiCol_TitleBg];
        pStyle->Colors[ImGuiCol_ScrollbarGrabHovered] = pStyle->Colors[ImGuiCol_ScrollbarGrabActive] = pStyle->Colors[ImGuiCol_ScrollbarGrab] = pStyle->Colors[ImGuiCol_TitleBg];
    }

    std::string sBottomInfo;
    void SetBottomInfo(std::string sInfo)
    {
        sBottomInfo = sInfo;
    }

    std::string sWatermark;
    void AddToWatermark(std::string sText)
    {
        sWatermark += " | ";
        sWatermark += sText;
    }

    bool bDrawBegin = true;
    bool bDrawShouldEnd;
    void DrawPreBegin()
    {
        DXNewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        uCurTickCount = GetTickCount64();

        sWatermark = pWindowName;
    }

    bool DrawBeginTopBar(std::string sName, ImVec2 iSze, bool bEnableInput = true)
    {
        ImGuiWindowFlags iFlags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        if (!bEnableInput) iFlags |= ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoMove;
        ImGui::SetNextWindowSize(iSze, ImGuiCond_Always);
        return ImGui::Begin(sName.c_str(), &bDrawBegin, iFlags);
    }

    void DrawEndTopBar()
    {
        ImGui::End();
    }

    void DrawWatermark()
    {
        cNavBar = sWatermark.c_str();
        float fTextSize = ImGui::CalcTextSize(cNavBar).x;
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - fTextSize - 20.f, 10.f), ImGuiCond_Always);
        if (DrawBeginTopBar("##WM", ImVec2(ImGui::CalcTextSize(cNavBar).x + 10.f, 20.f), false)) DrawEndTopBar();
    }

    void DrawSliderInfoIfVisible()
    {
        if (Sliders::cAlpha > 0 && Sliders::pWindow == pWindow) // We draw slider info here so its above everything
        {
            if (Sliders::iBB.Min.x > Sliders::iPos.x) Sliders::iPos.x = Sliders::iBB.Min.x;
            float fSliderMax = Sliders::iPos.x + Sliders::fTextWidth + 8.f;
            if (fSliderMax > Sliders::iBB.Max.x)
            {
                Sliders::iPos.x = Sliders::iBB.Max.x - Sliders::fTextWidth - 8.f;
                fSliderMax = Sliders::iBB.Max.x;
            }
            pForegroundDraw->AddRectFilled(Sliders::iPos, ImVec2(fSliderMax, Sliders::iPos.y + 23.f), IM_COL32(30, 35, 40, Sliders::cAlpha), 3.f);
            pForegroundDraw->AddText(pFont, pFont->FontSize, ImVec2(Sliders::iPos.x + 4.f, Sliders::iPos.y + 1.f), ImGui::GetColorU32(ImGuiCol_Text), Sliders::sInfo.c_str());
            if (uCurTickCount > Sliders::uLastFadeUpdate)
            {
                Sliders::uLastFadeUpdate = uCurTickCount + 15;
                Sliders::cAlpha -= 15;
            }
        }
    }

    void DrawKeyBindTypeIfOpen()
    {
        if (KeyBind::pKeyType)
        {
            if (ImGui::GetIO().MouseClicked[0])
            {
                ImVec2 iMousePos = ImGui::GetMousePos();
                if (iMousePos.x > KeyBind::iKeyTypeBB.Max.x || KeyBind::iKeyTypeBB.Min.x > iMousePos.x ||
                    iMousePos.y > KeyBind::iKeyTypeBB.Max.y || KeyBind::iKeyTypeBB.Min.y > iMousePos.y)
                {
                    KeyBind::pKeyType = nullptr;
                    return;
                }
            }

            pDraw->AddRectFilled(KeyBind::iKeyTypeBB.Min, KeyBind::iKeyTypeBB.Max, IM_COL32(44, 49, 55, 255), 3.f);
            pDraw->AddRect(KeyBind::iKeyTypeBB.Min, KeyBind::iKeyTypeBB.Max, IM_COL32(32, 33, 36, 255), 3.f);

            static const char* cTypes[] = { "Hold", "Toggle", "Always" };
            for (int i = 0; 3 > i; ++i)
            {
                const float fStartY = KeyBind::iKeyTypeBB.Min.y + (static_cast<float>(i) * 22.f);

                ImVec2 iText = ImVec2(KeyBind::iKeyTypeBB.Min.x + 8.f, fStartY);
                ImGui::SetCursorPos(ImVec2(iText.x - iWindowPos.x, iText.y - iWindowPos.y + pWindow->Scroll.y));
                ImGui::TextColored(i == *KeyBind::pKeyType || KeyBind::bKeyTypeHovered[i] ? ImGui::GetStyleColorVec4(ImGuiCol_TitleBg) : ImGui::GetStyleColorVec4(ImGuiCol_Text), cTypes[i]);
            }
        }
    }

    // This shouldn't be used in Overlay!
    bool DrawBeginChild(const char* cName, ImVec2 iSize)
    {
        ImGui::SetNextWindowSize(iSize, ImGuiCond_Once);

        bool bRet = ImGui::Begin(cName, &bDrawBegin, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        if (bRet)
        {
            pWindow = ImGui::GetCurrentWindow();
            pDraw = pWindow->DrawList;
            pForegroundDraw = ImGui::GetForegroundDrawList();
            iWindowPos = ImGui::GetWindowPos();
            iWindowSize = ImGui::GetWindowSize();
            iWindowBB.Min = iWindowPos;
            iWindowBB.Max = ImVec2(iWindowPos.x + iWindowSize.x, iWindowPos.y + iWindowSize.y + 20.f);

            iDrawPos.x = iWindowPos.x - 1.f;
            iDrawPos.y = iWindowPos.y + 32.f - pWindow->Scroll.y;

            iItemID = 0;

            Combos::pWindow = nullptr;

            GroupBox::fWidth = iWindowSize.x + 21.f;
            GroupBox::iPos[0].x = GroupBox::iPos[1].x = iDrawPos.x + 21.f;
            GroupBox::iPos[0].y = GroupBox::iPos[1].y = iDrawPos.y + 5.f;
            GroupBox::fLongestY = 0.f;
            GroupBox::pDynamic = nullptr;
        }
        return bRet;
    }

    void DrawEndChild()
    {
        DrawSliderInfoIfVisible();

        pDraw->AddRectFilled(ImVec2(iWindowBB.Min.x, iWindowPos.y + 24.f), ImVec2(iWindowBB.Max.x, iWindowPos.y + 25.f), IM_COL32(44, 49, 55, 255));
        pDraw->AddRectFilledMultiColor(ImVec2(iWindowBB.Min.x, iWindowPos.y + 24.f), ImVec2(iWindowBB.Max.x, iWindowPos.y + 32.f), IM_COL32(44, 49, 55, 255), IM_COL32(44, 49, 55, 255), IM_COL32(44, 49, 55, 0), IM_COL32(44, 49, 55, 0));
        pDraw->AddLine(ImVec2(iWindowBB.Min.x + 11.f, iWindowPos.y + 25.f), ImVec2(iWindowBB.Max.x - 11.f, iWindowPos.y + 25.f), IM_COL32(77, 80, 89, 255));
        ImGui::End();
    }

    bool DrawBegin(bool bInternal = false)
    {
        ImGui::SetNextWindowSize(ImVec2(574.f, 461.f), ImGuiCond_Once);

        bDrawShouldEnd = ImGui::Begin(pWindowName, &bDrawBegin, bInternal ? ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize : ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (bDrawShouldEnd)
        {
            pWindow = ImGui::GetCurrentWindow();
            pDraw = pWindow->DrawList;
            pForegroundDraw = ImGui::GetForegroundDrawList();
            iWindowPos = ImGui::GetWindowPos();
            iWindowSize = ImGui::GetWindowSize();
            iWindowBB.Min = iWindowPos;
            iWindowBB.Max = ImVec2(iWindowPos.x + iWindowSize.x, iWindowPos.y + iWindowSize.y);

            iDrawPos.x = iWindowPos.x + 15.f;
            iDrawPos.y = iWindowPos.y + 86.f - pWindow->Scroll.y;

            iItemID = 0;

            Combos::pWindow = nullptr;

            GroupBox::iPos[0] = GroupBox::iPos[1] = iDrawPos;
            GroupBox::fLongestY = 0.f;
            GroupBox::pDynamic = nullptr;

            if (KeyBind::pKeyType)
            {
                for (int i = 0; 3 > i; ++i)
                {
                    const float fStartY = KeyBind::iKeyTypeBB.Min.y + (static_cast<float>(i) * 22.f);
                    const ImRect iType(ImVec2(KeyBind::iKeyTypeBB.Min.x, fStartY), ImVec2(KeyBind::iKeyTypeBB.Max.x, fStartY + 22.f));
                    const ImGuiID iTypeID = pWindow->GetID(GetID().c_str());
                    if (ImGui::ItemAdd(iType, iTypeID))
                    {
                        Item::bPressed = ImGui::ButtonBehavior(iType, iTypeID, &KeyBind::bKeyTypeHovered[i], &Item::bHeld, ImGuiButtonFlags_AllowItemOverlap);
                        if (Item::bPressed)
                        {
                            *KeyBind::pKeyType = i;
                            ImGui::MarkItemEdited(iTypeID);
                            KeyBind::pKeyType = nullptr;
                            break;
                        }
                    } 
                }
            }
        }
        return bDrawShouldEnd;
    }

    void DrawEnd(bool bCloseButton = true, bool bDrawBG = true)
    {
        if (bDrawShouldEnd)
        {
            DrawSliderInfoIfVisible();
            DrawKeyBindTypeIfOpen();

            // Stop objects from "drawing" when outside area.
            pDraw->AddRectFilled(iWindowPos, ImVec2(iWindowBB.Max.x, iWindowPos.y + 65.f), IM_COL32(44, 49, 55, 255));
            pDraw->AddRectFilledMultiColor(ImVec2(iWindowBB.Min.x, iWindowPos.y + 65.f), ImVec2(iWindowBB.Max.x, iWindowPos.y + 80.f), IM_COL32(44, 49, 55, 255), IM_COL32(44, 49, 55, 255), IM_COL32(44, 49, 55, 0), IM_COL32(44, 49, 55, 0));
            pDraw->AddRectFilledMultiColor(ImVec2(iWindowPos.x, iWindowBB.Max.y - 40.f), ImVec2(iWindowBB.Max.x, iWindowBB.Max.y - 30.f), IM_COL32(44, 49, 55, 0), IM_COL32(44, 49, 55, 0), IM_COL32(44, 49, 55, 255), IM_COL32(44, 49, 55, 255));
            pDraw->AddRectFilled(ImVec2(iWindowPos.x, iWindowBB.Max.y - 30.f), ImVec2(iWindowBB.Max.x, iWindowBB.Max.y - 2.f), IM_COL32(44, 49, 55, 255));
            pDraw->AddLine(ImVec2(iWindowBB.Min.x, iWindowBB.Max.y - 2.f), ImVec2(iWindowBB.Max.x, iWindowBB.Max.y - 2.f), IM_COL32(77, 80, 89, 255));

            // Title
            ImGui::PushFont(pFontTitle);

            ImVec2 iTitle(22.f, 24.f + pWindow->Scroll.y);
            ImGui::SetCursorPos(iTitle);
            ImGui::Text(pWindowName);

            // Title Animation
            

            // Title Lines
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
            float fTitleWidth = ImGui::CalcTextSize(pWindowName).x;
            pDraw->AddLine(ImVec2(iWindowPos.x + 32.f + fTitleWidth, iWindowPos.y + 24.f), ImVec2(iWindowPos.x + 32.f + fTitleWidth, iWindowPos.y + 58.f), IM_COL32(55, 60, 65, 255));
            pDraw->AddLine(ImVec2(iWindowPos.x + 12.f, iWindowPos.y + 66.f), ImVec2(iWindowPos.x + iWindowSize.x - 12.f, iWindowPos.y + 66.f), IM_COL32(55, 60, 65, 255));
            ImGui::PopFont();

            // Tabs
            float fTabsAvailableWidth = (iWindowPos.x + iWindowSize.x) - (iWindowPos.x + 18.f + fTitleWidth);
            float fTabWidthCalc = static_cast<float>(fTabsAvailableWidth / Tabs::sSize) - (8.f * (Tabs::sSize - 1));
            float fTabWidthCalc2 = fTabsAvailableWidth - (fTabWidthCalc * Tabs::sSize) - (8.f * Tabs::sSize);
            float fTabWidth = fTabWidthCalc + (fTabWidthCalc2 / Tabs::sSize);
            ImGui::PushFont(pFontTabs);
            for (size_t sTab = 0; Tabs::sSize > sTab; ++sTab)
            {
                const ImVec2 iTabPos = ImVec2(iWindowPos.x + 43.f + fTitleWidth + (fTabWidth * sTab), iWindowPos.y + 30.f);
                const ImRect iTabBB(iTabPos, ImVec2(iTabPos.x + fTabWidth - 8.f, iTabPos.y + 22.f));
                if (Tabs::iSelected != sTab)
                {
                    const ImGuiID iTabID = pWindow->GetID(&Tabs::vData[sTab].sName);
                    if (ImGui::ItemAdd(iTabBB, iTabID))
                    {
                        static bool bHovered, bHeld;
                        bool bPressed = ImGui::ButtonBehavior(iTabBB, iTabID, &bHovered, &bHeld, 0);
                        if (bPressed)
                        {
                            ImGui::SetScrollY(0.f);
                            Tabs::iSelected = sTab;
                            Tabs::vData[sTab].cAlpha = 255;
                        }
                        else if (bHovered)
                        {
                            if (Tabs::vData[sTab].cAlpha != 255 && uCurTickCount > Tabs::vData[sTab].uLastFadeUpdate)
                            {
                                Tabs::vData[sTab].uLastFadeUpdate = uCurTickCount + 15;
                                Tabs::vData[sTab].cAlpha += 15;
                            }
                        }
                        else
                        {
                            if (Tabs::vData[sTab].cAlpha != 0 && uCurTickCount > Tabs::vData[sTab].uLastFadeUpdate)
                            {
                                Tabs::vData[sTab].uLastFadeUpdate = uCurTickCount + 15;
                                Tabs::vData[sTab].cAlpha -= 15;
                            }
                        }
                    }
                }
                if (Tabs::vData[sTab].cAlpha > 0) pDraw->AddRectFilled(iTabBB.Min, iTabBB.Max, IM_COL32(30, 35, 40, Tabs::vData[sTab].cAlpha), 3.f);
                ImGui::SetCursorPos(ImVec2((((iTabBB.Min.x + iTabBB.Max.x) * 0.5f) - (ImGui::CalcTextSize(Tabs::vData[sTab].sName.c_str()).x * 0.5f)) - iWindowPos.x, 30.f + pWindow->Scroll.y));
                ImGui::Text(Tabs::vData[sTab].sName.c_str());
            }
            ImGui::PopFont();

            // Bottom
            pDraw->AddLine(ImVec2(iWindowBB.Min.x + 12.f, iWindowBB.Max.y - 28.f), ImVec2(iWindowBB.Max.x - 12.f, iWindowBB.Max.y - 28.f), IM_COL32(55, 60, 65, 255));
            if (bCloseButton && ImGui::CloseButton(pWindow->GetID("#CLOSE"), ImVec2(iWindowBB.Max.x - 42.f, iWindowBB.Max.y - 26.f))) bDrawBegin = false;
            if (!sBottomInfo.empty())
            {
                ImGui::SetCursorPos(ImVec2(15.f, iWindowSize.y - 26.f + pWindow->Scroll.y));
                ImGui::Text(sBottomInfo.c_str());
            }
            ImGui::PopStyleColor();
            ImGui::SetCursorPosY(GroupBox::fLongestY - pWindow->Pos.y + pWindow->Scroll.y);
            ImGui::End();
            bDrawShouldEnd = false;
        }
        ImGui::EndFrame();
#if defined(OTDX11)
        static float fClear[4];
        pDeviceContext->ClearRenderTargetView(pRender, fClear);
        ImGui::Render();
        pDeviceContext->OMSetRenderTargets(1, &pRender, 0);
        DXRenderData();
        pSwap->Present(0 /* 0 => No FPS Lock */, 0);
#else
        if (bDrawBG)
        {
            pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.f, 0);
            if (pDevice->BeginScene() >= 0)
            {
                ImGui::Render();
                DXRenderData();
                pDevice->EndScene();
            }
            if (pDevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) ResetDevice();
        }
        else
        {
            ImGui::Render();
            DXRenderData();
        }

#endif
    }

    void ImGuiShutDown()
    {
        DXShutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (!wClass.hInstance) return;

        CleanD3D();
        DestroyWindow(hWindow);
        UnregisterClassA(wClass.lpszClassName, wClass.hInstance);
    }
}