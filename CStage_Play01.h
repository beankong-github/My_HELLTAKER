#pragma once
#include "Cstage.h"

class CStage_Play01 :
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
    CStage_Play01();
    ~CStage_Play01() override;
};

