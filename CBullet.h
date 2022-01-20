#pragma once
#include "CObj.h"


struct tTailInfo
{
    Vec vPos;
    float fLifeTime;
};

class CTexture;

class CBullet :
    public CObj
{
private:
    float           m_fSpeed;
    float           m_fAddTime;

    CTexture*       m_pTex;

    float           m_fTailAddTime;

    list<tTailInfo> m_listTailInfo;

public:
    virtual void Update();
    void Render(HDC _dc) override;

public:
    CBullet();
    ~CBullet();
};

