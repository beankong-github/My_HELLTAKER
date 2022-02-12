#pragma once
#include "CObj.h"

enum class ETILE_TYPE
{
    WALL,               // 벽: 흰색
    ROCK,               // 바위: 흰색
    SPIKE_ACTIVE,       // 활성 가시: 빨간색
    SPIKE_DEACTIVE,     // 비활성 가시
    ITEM,               // 아이템 - 키: 파란색
    LOCKBOX,            // 상자: 파란색
    UNDEAD,             // 언데드 노예: 초록색
    NONE,               // 길
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

