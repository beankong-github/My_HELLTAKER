#include "pch.h"
#include "CMonster.h"

#include "CBullet.h"

CMonster::CMonster()
	:m_iHitCount(5)
{
	// collider 추가
	CCollider* pCollider = new CCollider;
	AddComponent(pCollider);
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
}

void CMonster::Render(HDC _dc)
{
	CObj::Render(_dc);

#ifdef _DEBUG
	Render_Component(_dc);
#endif // DEBUG

}

void CMonster::OnCollision(CObj* _pOtherObj)
{
	// 플레이어 총알과 충돌 시 
	dynamic_cast<CBullet*>(_pOtherObj);
	if (nullptr != _pOtherObj)
	{
		// HitCount 만큼 Buller과 충돌 후 삭제
		m_iHitCount -= 1;
		if(m_iHitCount <= 0 )
			DeleteObject(this);
	}

}

