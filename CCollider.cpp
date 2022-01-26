#include "pch.h"
#include "CCollider.h"

#include "CCore.h"
#include "CObj.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: CComponent(ECOM_TYPE::COLLIDER)
	, m_vOffsetPos{}
	, m_vScale{}
	, m_vFinalPos{}
	, m_iColID(g_iNextID++)
	, m_iCollisionCount(0)
{ 
}

CCollider::CCollider(const CCollider& _orign)
	: CComponent(_orign)
	, m_vScale(_orign.m_vScale)
	, m_vFinalPos(_orign.m_vFinalPos)
	, m_vOffsetPos(_orign.m_vOffsetPos)
	, m_iColID(g_iNextID++)
	, m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

// 충돌 시작 알림
void CCollider::OnCollisionEnter(CCollider* _pCollider)
{
	m_iCollisionCount += 1;
	GetOwner()->OnCollisionEnter(_pCollider->GetOwner());
}

// 충돌 알림
void CCollider::OnCollision(CCollider* _pCollider)
{
	GetOwner()->OnCollision(_pCollider->GetOwner());
}

// 충돌 종료 알림
void CCollider::OnCollisionExit(CCollider* _pCollider)
{
	m_iCollisionCount -= 1;
	GetOwner()->OnCollisionExit(_pCollider->GetOwner());
}


void CCollider::Update()
{
	// 충돌체의 이번 프레임의 최종 위치
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::Render(HDC _dc)
{
	HPEN hPen = nullptr;
	if (m_iCollisionCount > 0)
	{
		hPen = CCore::GetInst()->GetRedPen();
	}
	else if (m_iCollisionCount == 0)
	{
		hPen = CCore::GetInst()->GetGreenPen();
	}
	else
	{
		assert(nullptr);
	}

	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc
		, int(vRenderPos.x - m_vScale.x / 2.f)
		, int(vRenderPos.y - m_vScale.y / 2.f)
		, int(vRenderPos.x + m_vScale.x / 2.f)
		, int(vRenderPos.y + m_vScale.y / 2.f));

	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);
}
