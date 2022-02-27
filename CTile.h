#pragma once
#include "CObj.h"

enum class ETILE_TYPE
{
    NONE,               // 길
    WALL,               // 벽: 흰색
    NPC,                // NPC 캐릭터 위치 : 초록색
    START,              // 시작 위치 : 파란색
    GOAL,              // 성공 위치 : 빨간색
    END
};

class CObstacle;

class CTile :
    public CObj
{
private:
    ETILE_TYPE          m_eType;
    Vec                 m_vIndex;
    list<CObstacle*>  m_listObstcles;

public:
    void        SetTileType(ETILE_TYPE _eType)      { m_eType = _eType; }
    void        SetIndex(UINT _iCol, UINT _iRow)    { m_vIndex = Vec{_iCol, _iRow}; }

    ETILE_TYPE          GetType()           { return m_eType; }
    Vec                 GetIndex()          { return m_vIndex; }
    list<CObstacle*>* GetObstacles()        { return &m_listObstcles; }

public:
    void        AddObstacle     (CObstacle* _pObs)  { m_listObstcles.push_back(_pObs); }
    void        DeleteObstacle  (CObstacle* _pObs)      
    { 
        list<CObstacle*>::iterator iter = m_listObstcles.begin();
        list<CObstacle*>::iterator endIter = m_listObstcles.end();
        for (; iter != endIter;)
        {
            if (_pObs == *iter)
            {
                iter = m_listObstcles.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
    void        DeleteDeadObstacle();
    CObstacle*  FindObstacle    (EOBSTACLE_TYPE _eType)   
    {
        list<CObstacle*>::iterator iter = m_listObstcles.begin();
        for (; iter != m_listObstcles.end(); ++iter)
        {
            CObstacle* pObs = *iter;
            if (_eType == pObs->GetType())
                return *iter;
        }
        return nullptr;
    }
    void        ClearObstacles  ()                  { m_listObstcles.clear(); }

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    Vec GetCenterPos()
    {
        return GetPos() + Vec{ TILE_SIZE/2, TILE_SIZE/2 };
    };

public:
    CTile();
    virtual ~CTile();
};

