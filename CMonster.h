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
    void OnCollision(CObj* _pOtherObj) override ;

public:
    CMonster();
    ~CMonster();
};

