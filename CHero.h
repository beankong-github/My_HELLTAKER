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
    float   m_fSpeed;
    UINT    m_iMoveCount;
    
public:
    void Update();
    void Render(HDC _dc);

    void OnCollisionEnter(CObj* _pOther) override;
    void OnCollision(CObj* _pOther) override;
    void OnCollisionExit(CObj* _pOther) override;

public:
    CHero();
    virtual ~CHero();
};

