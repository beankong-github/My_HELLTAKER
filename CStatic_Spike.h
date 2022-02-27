#pragma once
#include "CObstacle.h"

class CStage_Puzzle;
class CTexture;

class CStatic_Spike :
    public CObstacle
{
private:
    CStage_Puzzle*      m_pCurStage;
    CTexture*           m_pTexture;

public:
    void Update();
    void Render(HDC _dc);

public:
    CStatic_Spike(CTile* _pTile);
    virtual ~CStatic_Spike();
};

