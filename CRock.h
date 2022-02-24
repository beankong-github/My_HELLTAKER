#pragma once
#include "CObstacle.h"

class CTexture;

class CRock :
    public CObstacle
{
private:
    vector<CTexture*>   m_vecTextures;
    CTexture*           m_pCurTex;

    float               m_fEffectTime;
    float               m_fAddTime;

public:
    void Update();
    void Render(HDC _dc);

    void TryMove();
    void Move(EDIRECTION _eDir);

private:
    void Shake();

public:
    CRock(CTile* _pTile);
    virtual ~CRock();
};

 