#pragma once
#include "Cstage.h"

class CTileMap;
class CTransition;
class CEffect;

class CStage_Puzzle :
    public CStage
{
private:
    ECHAPTER    m_eChapter;

    CTransition*    m_pTransition;
    CEffect*        m_pEffects[5];

    CTileMap*   m_pTileMap;
    Vec         m_vTileStartPos;
    Vec         m_vTileCount;

    int        m_iInitMoveCount;
    int        m_iCurMoveCount;

    UINT        m_iOBRockCount;     // 오브젝트 Rock 개수
    UINT        m_iOBUndeadCount;   // 오브젝트 Undead 개수
    UINT        m_iOBSSpikeCount;   // 오브젝트 Static Spike 개수
    UINT        m_iOBDSpikeCount;   // 오브젝트 Dynamic Spike 개수

    wstring     m_strNPCName;

    CSound* m_pBGM;


public:
    void    SetvTileCount(Vec _vCount)      { m_vTileCount = _vCount; }
    void    SetvTileStartPos(Vec _vPos)     { m_vTileStartPos = _vPos; }
    void    SetInitMoveCount(int _iMove)   { m_iInitMoveCount = _iMove; }
    void    SetCurMoveCount(int _iMove)     { m_iCurMoveCount = _iMove; }
    void    SetNPCName(ECHAPTER _eChap);

    ECHAPTER        GetChapter()          { return m_eChapter; }
    Vec             GetTileCount()        { return m_vTileCount; }
    CTileMap*       GetTileMap()          { return m_pTileMap; }
    CEffect*        GetEffect();
    
    const wstring&  GetNPCName()          { return m_strNPCName; }
    int             GetCurMoveCount()     { return m_iCurMoveCount; }
    int             GetInitMoveCount()    { return m_iInitMoveCount; }
    
public:
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

