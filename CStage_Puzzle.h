#pragma once
#include "Cstage.h"

class CTileMap;
class CTransition;

class CStage_Puzzle :
    public CStage
{
private:
    ECHAPTER    m_eChapter;

    CTransition* m_pTransition;

    CTileMap*   m_pTileMap;
    Vec         m_vTileStartPos;
    Vec         m_vTileCount;

    UINT        m_iInitMoveCount;
    UINT        m_iCurMoveCount;

    wstring     m_strNPCName;

public:
    void    SetvTileCount(Vec _vCount)      { m_vTileCount = _vCount; }
    void    SetvTileStartPos(Vec _vPos)     { m_vTileStartPos = _vPos; }
    void    SetInitMoveCount(UINT _iMove)   { m_iInitMoveCount = _iMove; }
    void    SetCurMoveCount(UINT _iMove)     { m_iCurMoveCount = _iMove; }
    void    SetNPCName(ECHAPTER _eChap);

    ECHAPTER        GetChapter()                { return m_eChapter; }
    Vec             GetTileCount()              { return m_vTileCount; }
    UINT            GetInitMoveCount()          { return m_iInitMoveCount; }
    UINT            GetCurMoveCount()           { return m_iCurMoveCount; }
    CTileMap*       GetTileMap()                { return m_pTileMap; }
    const wstring&  GetNPCName()                { return m_strNPCName; }

public:
    void PlayerMove(EDIRECTION _eDir);
    void PlayerDead();
    void StageClear();

    //void SaveCurrentStage();
public:
    void Init() override;
    void Update() override;
    void Render(HDC _dc) override;

    void Enter() override;
    void Exit() override;
    
    void Save(const wstring& _strRelativeFolderPath);
    void Load(const wstring& _strRelativeFilePath);

public:
    CStage_Puzzle(ECHAPTER _eChap);
    ~CStage_Puzzle();
};

