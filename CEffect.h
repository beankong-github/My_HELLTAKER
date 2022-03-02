#pragma once
#include "CObj.h"

class CEffect :
    public CObj
{
private:
    wstring m_strCurEffect;

public:
    void PlayEffect(wstring _wstrName, Vec _vPos);

public:
    void Update();
    void Render(HDC _dc);

public:
    CEffect();
    virtual ~CEffect();
};
