#pragma once
#include "CObstacle.h"

class CStage_Puzzle;

class CDynamic_Spike :
    public CObstacle
{
private:
    CStage_Puzzle*  m_pCurStage;
    bool            m_bActive;
    UINT            m_iPrevMoveCount;

public:
    void SetActive(bool _bAct)  { m_bActive = _bAct; }
    bool IsActive()             { return m_bActive; }

    void ChangeAcivation();

public:
    void Update();
    void Render(HDC _dc);

public:
    CDynamic_Spike(CTile* _pTile, bool _vActive = false);
    virtual ~CDynamic_Spike();
};

