#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
private:
    float m_fSpeed;

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CBullet();
    ~CBullet();
};

