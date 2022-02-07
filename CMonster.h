#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
private:
    UINT m_iHitCount;

public:
    void Update() override;
    void Render(HDC _dc) override;

    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

public:
    CMonster();
    virtual ~CMonster();
};

