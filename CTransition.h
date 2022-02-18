#pragma once
#include "CObj.h"
class CTransition :
    public CObj
{
private:
    CStage* m_pNextStage;

public:
    void Update();
    void Render(HDC _dc);

public:
    CTransition();
    virtual ~CTransition();
};

