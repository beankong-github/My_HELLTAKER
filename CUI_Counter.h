#pragma once
#include "CObj.h"
class CUI_Counter :
    public CObj
{
private:
    CTexture*   m_pFrontUITex;
    CTexture*   m_pBackUITex;
    HFONT      m_hFont;

public:
    void Update();
    void Render(HDC _dc);

    void CreateFont();

public:
    CUI_Counter();
    virtual  ~CUI_Counter();

};

