#pragma once
#include "Cstage.h"

class CStage_Tool :
    public CStage
{
private:
    HMENU m_hMenu;

public:    
      void Init() override;
      void Update() override;
      void Render(HDC _dc) override;

      void Enter() override;
      void Exit() override;

public:
    CStage_Tool();
    ~CStage_Tool() override;

};

