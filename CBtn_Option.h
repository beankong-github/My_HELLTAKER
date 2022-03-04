#pragma once
#include "CBtnUI.h"
class CBtn_Option :
    public CBtnUI
{
private:
    CTexture*   m_pUnSelectImg;
    CTexture*   m_pSelectImg;

    wstring     m_wstring;
    bool        m_bAnswer;

public:
    void MouseLbtnClicked(Vec _vMousePos) override;
    void Update() override;
    void Render(HDC _dc) override;

public:
    CBtn_Option();
    ~CBtn_Option();
};

