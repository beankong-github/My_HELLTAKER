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
    void Update() override;
    void Render(HDC _dc) override;

    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

public:
    CBullet();
    virtual ~CBullet();
};

