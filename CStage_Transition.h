#pragma once
#include "Cstage.h"

class CTransition;
class CStage_Transition :
    public CStage
{
private:
    CTransition*    m_pTransition;
    ECHAPTER        m_eNextChap;

public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;
     
    void Enter() override;
    void Exit() override;
public:
    CStage_Transition();
    ~CStage_Transition();
};

