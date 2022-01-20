#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
	// collider Ãß°¡
	CCollider* pCollider = new CCollider;
	AddComponent(pCollider);
	GetCollider()->SetScale(Vec(50.f, 50.f));
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

