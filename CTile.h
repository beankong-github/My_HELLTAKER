#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
private:
    CTexture*   m_pAtlas;
    UINT         m_iImgIdx;

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void SetImgIdx(int _iIdx)
    {
        m_iImgIdx = _iIdx;
    }

public:
    CTile();
    virtual ~CTile();
};

