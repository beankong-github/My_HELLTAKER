#pragma once
#include "CObj.h"

enum class ETILE_TYPE
{
    NONE,               // ��
    WALL,               // ��: ���
    NPC,                // NPC ĳ���� ��ġ : �ʷϻ�
    START,              // ���� ��ġ : �Ķ���
    GOAL,              // ���� ��ġ : ������
    END
};

class CTile :
    public CObj
{
private:
    ETILE_TYPE  m_eType;
    Vec         m_vIndex;
public:
    void        SetTileType(ETILE_TYPE _eType)      { m_eType = _eType; }
    void        SetIndex(UINT _iCol, UINT _iRow)    { m_vIndex = Vec{_iCol, _iRow}; }

    ETILE_TYPE  GetType()               { return m_eType; }
    Vec         GetIndex()                   { return m_vIndex; }

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

