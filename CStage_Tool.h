#pragma once
#include "Cstage.h"

enum class ETOOL_MODE
{
    TILE,
    OBJECT,
    ANIMATION,
    NONE
};


class CStage_Tool :
    public CStage
{
private:
    ETOOL_MODE    m_eMode;
    HMENU        m_hMenu;

public:    
      void Init() override;
      void Update() override;
      void Render(HDC _dc) override;

      void Enter() override;
      void Exit() override;

public:
    void PopupCreateTile();

private:
    void Update_Tile();
    void Update_Object();
    void Update_Animation();

public:
    CStage_Tool();
    ~CStage_Tool() override;

};

