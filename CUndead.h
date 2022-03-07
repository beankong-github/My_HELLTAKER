#pragma once
#include "CObstacle.h"

class CStage_Puzzle;

class CUndead :
    public CObstacle
{
private:
    CStage_Puzzle*  m_pCurStage;
    Vec             m_vOriginalPos;

    CSound*         m_pMoveSound;
    CSound*         m_pDeadSound;
public:
    void Update();
    void Render(HDC _dc);

    void TryMove(EDIRECTION _eDir);
    void Move();
    void Dead();
   
public:
    CUndead(CTile* _pTile);
    virtual ~CUndead();
};

