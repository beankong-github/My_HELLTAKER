#pragma once
#include "Cstage.h"

class CUI_Dialog;

class CStage_Start :
    public CStage
{
private:
    CUI_Dialog* m_pDailog;

public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;
    
    void Enter() override;
    void Exit() override;

public:
    void FirstOptionSelected() override;
    void SecondOptionSelected() override;
    void DialogTermination() override;


public:
    CStage_Start();
    ~CStage_Start();

};

