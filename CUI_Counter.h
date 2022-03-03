#pragma once
#include "CObj.h"
class CUI_Counter :
    public CObj
{
private:
    CTexture*   m_pFrontUITex;
    CTexture*   m_pBackUITex;
    HFONT      m_hFont;

    wstring  m_StageName[9] = {L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��"};

public:
    void Update();
    void Render(HDC _dc);

    void CreateFont();

public:
    CUI_Counter();
    virtual  ~CUI_Counter();

};

