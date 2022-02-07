#pragma once
#include "Cstage.h"

class CStage_Start :
    public CStage
{
private:

public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;
    
    void Enter() override;
    void Exit() override;


public:
    CStage_Start();
    ~CStage_Start();

};

