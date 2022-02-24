#pragma once
#include "CObj.h"

enum class EOBSTACLE_TYPE
{
    NONE,
    ROCK,
    UNDEAD,
    DYNAMC_SPIKE,
    STATIC_SPIKE,
    END
};
enum class EOBSTACLE_STATE
{
    IDLE,
    MOVE,
    KICKED,
    DEAD,
    END
};

class CTile;

class CObstacle :
    public CObj
{
private:

    EOBSTACLE_STATE m_eState;
    EOBSTACLE_TYPE  m_eType;

    CTile* m_pCurTile;
    CTile* m_pNextTile;

    EDIRECTION  m_eMoveDir;
    float       m_fSpeed;

public:
    void SetCurTile(CTile* _tile);
    void SetSpeed(float _fSpeed)            { m_fSpeed = _fSpeed; }
    void SetNextTile(CTile* _tile)          { m_pNextTile = _tile;}
    void SetState(EOBSTACLE_STATE _eState)  { m_eState = _eState; }

    CTile* GetCurTile()         { return m_pCurTile; }
    CTile* GetNextTile()        { return m_pNextTile; }
    EOBSTACLE_STATE GetState()  { return m_eState; }

    virtual void TryMove() = 0; 
    virtual void Move(EDIRECTION _eDir) = 0;

public:
    virtual void Update() = 0;
    virtual void Render(HDC _dc) = 0;

public:
    CObstacle(CTile* _pTile);
    virtual ~CObstacle();
};

