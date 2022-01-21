#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
public:
    static UINT g_iNextID;

private:
    const UINT m_iColID;

    Vec m_vOffsetPos;
    Vec m_vScale;
    Vec m_vFinalPos;        // Object position + offset position

    int m_iCollisionCount;

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void SetOffsetPos(Vec _vPos)    { m_vOffsetPos = _vPos;}
    void SetScale(Vec _vScale)      { m_vScale = _vScale;}

    Vec GetOffsetPos()              { return m_vOffsetPos;}
    Vec GetScale()                  { return m_vScale;}
    Vec GetFinalPos()               { return m_vFinalPos;}
    UINT GetID()                    { return m_iColID;}


    void OnCollisionEnter(CCollider* _pCollider);
    void OnCollision(CCollider* _pCollider);
    void OnCollisionExit(CCollider* _pCollider);

public:
    CCollider& operator =(const CCollider& _orign) = delete;

public:
    CCollider();
    CCollider(const CCollider& _orign); // 복사 생성자 (깊은 복사)
    ~CCollider();
};

