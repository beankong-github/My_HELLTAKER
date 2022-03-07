#pragma once
#include "CObstacle.h"

class CTile;
class CStage_Puzzle;

class CKey :
    public CObstacle
{
private:
    CStage_Puzzle*  m_pCurStage;

public:
    void Update();
    void Render(HDC _dc);

public:
    CKey(CTile* _pTile);
    virtual ~CKey();
};

