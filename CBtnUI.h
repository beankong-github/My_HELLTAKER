#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
public:
    virtual void MouseLbtnClicked(Vec _vMousePos);   
    virtual void Update() override;
    virtual void Render(HDC _dc);

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

