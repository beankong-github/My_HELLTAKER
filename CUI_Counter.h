#pragma once
#include "CObj.h"
class CUI_Counter :
    public CObj
{
private:
    CTexture* m_pFrontUITex;
    CTexture* m_pBackUITex;

public:
    void Update();
    void Render(HDC _dc);

public:
    CUI_Counter();
    virtual  ~CUI_Counter();

};

