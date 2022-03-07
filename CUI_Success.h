#pragma once
#include "CUI.h"
class CUI_Success :
    public CUI
{
private:
    CSound* m_pSound;

public:
    void PlayAnimation();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CUI_Success();
    ~CUI_Success();
};

