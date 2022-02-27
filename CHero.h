#pragma once
#include "CObj.h"

class CTile;

enum class EPLAYER_STATE
{
    IDLE,
    MOVE,
    KICK,
    DAMAGED,
    SUCCESS,
    DEAD
};

class CHero :
    public CObj
{
private:
    CStage_Puzzle*  m_pCurStage;
    
    EPLAYER_STATE   m_eState;

    CTile*          m_pCurTile;
    CTile*          m_pNextTile;
   
    EDIRECTION      m_eMovDir;
    float           m_fSpeed;

    bool            m_bKey;

public:
    void SetState(EPLAYER_STATE _eState)    { m_eState = _eState; }
    void SetSpeed(float _fSpeed)            { m_fSpeed = _fSpeed; }
    void SetCurTile(CTile* _pTile)          { m_pCurTile = _pTile; }

public:
    void Update();
    void Render(HDC _dc);

    void TryMove();
    void Move(EDIRECTION _eDir);

private:
    void KeyCheck();
    void CountDown();

public:
    CHero();
    virtual ~CHero();
};

