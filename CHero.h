#pragma once
#include "CObj.h"

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
    EPLAYER_STATE m_eCurState;
    float   m_fSpeed;
   
public:
    void SetState(EPLAYER_STATE _eState) { m_eCurState = _eState; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }


public:
    void Update();
    void Render(HDC _dc);

    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

    void TryMove(EDIRECTION _eDir);

public:
    CHero();
    virtual ~CHero();
};

