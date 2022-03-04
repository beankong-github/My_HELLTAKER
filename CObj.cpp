#include "pch.h"
#include "CObj.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CComponent.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CFSM.h"

CObj* CObj::Clone()
{
	return nullptr;
}

CObj::CObj()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
	, m_arrCom{}
	, m_bFlip(false)
{
}

CObj::~CObj()
{
	// 컴포넌트 삭제
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			delete m_arrCom[i];
		}
	}
}

void CObj::AddComponent(CComponent* _pCom)
{
	// 컴포넌트 추가
	ECOM_TYPE eType = _pCom->GetType();
	m_arrCom[(UINT)eType] = _pCom;
	_pCom->m_pOwer = this;
}

void CObj::LateUpdate()
{
	// 컴포넌트 업데이트
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Update();
	}
}

void CObj::Render(HDC _dc)
{
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc, (int)(vRenderPos.x - (m_vScale.x / 2.f)),
		(int)(vRenderPos.y - (m_vScale.y / 2.f)),
		(int)(vRenderPos.x + (m_vScale.x / 2.f)),
		(int)(vRenderPos.y + (m_vScale.y / 2.f)));
}

void CObj::OnCollisionEnter(CObj* _pOther)
{
}

void CObj::OnCollision(CObj* _pOther)
{
}

void CObj::OnCollisionExit(CObj* _pOther)
{
}

void CObj::Render_Component(HDC _dc)
{
	// 컴포넌트 랜더
	for (UINT i = 0; i < (UINT)ECOM_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Render(_dc);
	}
}
