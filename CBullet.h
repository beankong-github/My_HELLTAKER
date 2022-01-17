#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
private:
    float m_fSpeed;
    float m_fAddTime;

public:
    virtual void Init();
    virtual void Update();
    void Render(HDC _dc) override;

public:
    CBullet();
    ~CBullet();
};

