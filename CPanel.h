#pragma once
#include "CUI.h"


class CPanel :
    public CUI
{
private:

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    virtual void MouseLbtnClicked(Vec _vMousePos) override;

    CLONE(CPanel);

public:
    CPanel();
    ~CPanel();
};

