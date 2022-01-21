#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec m_vOffsetPos;
    Vec m_vScale;
    Vec m_vFinalPos;        // Object position + offset position

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void SetOffsetPos(Vec _vPos)    { m_vOffsetPos = _vPos;}
    void SetScale(Vec _vScale)      { m_vScale = _vScale;}

    Vec GetOffsetPos()              { return m_vOffsetPos;}
    Vec GetScale()                  { return m_vScale; }
    Vec GetFinalPos()               { return m_vFinalPos;}

    void OnCollision(CCollider* _pCollider);
    
public:
    CCollider();
    ~CCollider();
};

