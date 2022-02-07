#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
private:
    CTexture* m_pAtlas;

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CTile();
    virtual ~CTile();
};

