#include "pch.h"
#include "CCollider.h"
#include "CObj.h"

// 충돌 알림
void CCollider::OnCollision(CCollider* _pCollider)
{
	GetOwner()->OnCollision(_pCollider->GetOwner());
}

CCollider::CCollider()
	: CComponent(ECOM_TYPE::COLLIDER)
	, m_vOffsetPos{}
	, m_vScale{}
	, m_vFinalPos{}
{
}

CCollider::~CCollider()
{
}

void CCollider::Update()
{
	// 충돌체의 이번 프레임의 최종 위치
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::Render(HDC _dc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(120, 250, 50));
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Rectangle(_dc
		, int(m_vFinalPos.x - m_vScale.x / 2.f)
		, int(m_vFinalPos.y - m_vScale.y / 2.f)
		, int(m_vFinalPos.x + m_vScale.x / 2.f)
		, int(m_vFinalPos.y + m_vScale.y / 2.f));

	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);

	DeleteObject(hPen);
}
