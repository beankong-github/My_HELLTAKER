#pragma once
#include "Cstage.h"

class CTileMap;

class CStage_Puzzle :
    public CStage
{
private:
    ECHAPTER    m_eChapter;
   
    Vec         m_vTileStartPos;
    Vec         m_vTileCount;

    UINT        m_iInitMoveCount;
    UINT        m_iCurMoveCount;

    CTileMap*   m_pTileMap;

public:
    void    SetvTileCount(Vec _vCount)      { m_vTileCount = _vCount; }
    void    SetvTileStartPos(Vec _vPos)     { m_vTileStartPos = _vPos; }
    void    SetInitMoveCount(UINT _iMove)   { m_iInitMoveCount = _iMove; }
    
    ECHAPTER    GetChapter()                { return m_eChapter; }
    Vec         GetTileCount()              { return m_vTileCount; }
    UINT        GetInitMoveCount()          { return m_iInitMoveCount; }
    UINT        GetCurMoveCount()           { return m_iCurMoveCount; }
    CTileMap*   GetTileMap()                { return m_pTileMap; }

public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;

    void Enter() override;
    void Exit() override;

public:
    void PlayerMove(EDIRECTION _eDir);

public:
    CStage_Puzzle(ECHAPTER _eChap);
    ~CStage_Puzzle();
};

