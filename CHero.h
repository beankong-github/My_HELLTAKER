#pragma once
#include "CObj.h"

class CTile;

enum class EPLAYER_STATE
{
    IDLE,
    MOVE,
    KICK,
    SUCCESS,
    DEAD
};

class CHero :
    public CObj
{
private:
    EPLAYER_STATE   m_eCurState;
    CTile*          m_pCurTile;
    CTile*          m_pNextTile;
    float           m_fSpeed;
   
public:
    void SetState(EPLAYER_STATE _eState) { m_eCurState = _eState; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetCurTile(CTile* _pTile) { m_pCurTile = _pTile; }

public:
    void Update();
    void Render(HDC _dc);

    bool TryMove(EDIRECTION _eDir);

private: 
    void Move();

public:
    CHero();
    virtual ~CHero();
};

