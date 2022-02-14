#pragma once
#include "CObj.h"

enum class ETILE_TYPE
{
    NONE,               // 길
    WALL,               // 벽: 흰색
    OBSTACLE,           // 방해물 : 초록색
    START,              // 시작 위치 : 파란색
    END
};

class CTile :
    public CObj
{
private:
    ETILE_TYPE m_eType;

public:
    void SetTileType(ETILE_TYPE _eType) { m_eType = _eType; }
    ETILE_TYPE GetTileType() { return m_eType; }

public:
    void Update() override;
    void Render(HDC _dc) override;

    //void OnCollisionEnter(CObj* _pOther) override;
    //void OnCollision(CObj* _pOther) override;
    //void OnCollisionExit(CObj* _pOther) override;

public:
    Vec GetCenterPos()
    {
        return GetPos() + Vec{ TILE_SIZE/2, TILE_SIZE/2 };
    };

public:
    CTile();
    virtual ~CTile();
};

