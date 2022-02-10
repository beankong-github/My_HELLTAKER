#pragma once
#include "Cstage.h"

class CStage_Puzzle :
    public CStage
{
private:
    ECHAPTER    m_eChapter;
   
    Vec         m_vTileCount;
    UINT        m_iInitMoveCount;
    UINT        m_iCurMoveCount;

public:
    void    SetvTileCount(Vec _vTileCount)     { m_vTileCount = _vTileCount; }
    void    SetInitMoveCount(UINT _iMove)      { m_iInitMoveCount = _iMove; }
    
    ECHAPTER    GetChapter()                   { return m_eChapter; }
    Vec         GetTileCount()                 { return m_vTileCount; }
    UINT        GetInitMoveCount()             { return m_iInitMoveCount; }
    UINT        GetCurMoveCount()              { return m_iCurMoveCount; }

public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;

    void Enter() override;
    void Exit() override;

public:
    CStage_Puzzle(ECHAPTER _eChap);
    ~CStage_Puzzle();
};

