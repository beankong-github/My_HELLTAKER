#pragma once
#include "CObj.h"
class CTransition :
    public CObj
{
private:
    CStage* m_pNextStage;

    CSound* m_pTransitionSound_1;
    CSound* m_pTransitionSound_2;

    float   m_fSoundInterval;
    float   m_fAddTime;

public:
    void Update();
    void Render(HDC _dc);

public:
    CTransition();
    virtual ~CTransition();
};

