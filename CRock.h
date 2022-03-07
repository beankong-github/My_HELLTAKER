#pragma once
#include "CObstacle.h"

class CTexture;
class CSound;
class CStage_Puzzle;

class CRock :
    public CObstacle
{
private:
    CStage_Puzzle*      m_pCurStage;
    CTexture*           m_pCurTex;
    CSound*             m_pMoveSound;
    CSound*             m_pKickSound;

    Vec                 m_vOriginalPos;
    float               m_fEffectTime;
    float               m_fAddTime;

public:
    void Update();
    void Render(HDC _dc);

    void TryMove(EDIRECTION _eDir);
    void Move();

private:
    void Shake();

public:
    CRock(CTile* _pTile);
    virtual ~CRock();
};

 