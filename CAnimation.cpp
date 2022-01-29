#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CObj.h"
#include "CTexture.h"
#include "CCamera.h"

CAnimation::CAnimation()
	: m_strName()
	, m_pAnimator(nullptr)
	, m_pAtlas(nullptr)
	, m_vecFrm(0)
	, m_iCuridx(0)
	, m_fAddTime(0)
	, m_bFinish(0)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(const wstring& _strAnimName, CTexture* _pAtlasTex, Vec _vLeftTop, Vec _vSize, float _fxDistance, float _fDuration, UINT _iFrmCount)
{
	m_strName = _strAnimName;
	m_pAtlas = _pAtlasTex;
	
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrmCount; i++)
	{
		frm.vLeftTop = Vec(_vLeftTop.x + (float)i * _fxDistance, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.fDuration = _fDuration;
	
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Reset()
{
	m_iCuridx = 0;
	m_fAddTime = 0.f;
	m_bFinish = false;
}



void CAnimation::Update()
{
	if (m_bFinish)
		true;

	m_fAddTime += DS;

	if (m_fAddTime >= m_vecFrm[m_iCuridx].fDuration)
	{
		++m_iCuridx;
		if (m_iCuridx >= m_vecFrm.size())
		{
			m_iCuridx -= 1;		// 마지막 프레임
			m_bFinish = true;
			return;
		}
		 m_fAddTime = m_fAddTime - m_vecFrm[m_iCuridx].fDuration;
	}
}

void CAnimation::Render(HDC _dc)
{
	Vec vPos = CCamera::GetInst()->GetRenderPos(GetOwner()->GetPos());

	TransparentBlt(_dc
		, int(vPos.x - m_vecFrm[m_iCuridx].vSize.x / 2.f)
		, int(vPos.y - m_vecFrm[m_iCuridx].vSize.y / 2.f)
		, int(m_vecFrm[m_iCuridx].vSize.x)
		, int(m_vecFrm[m_iCuridx].vSize.y)
		, m_pAtlas->GetDC()
		, int(m_vecFrm[m_iCuridx].vLeftTop.x)
		, int(m_vecFrm[m_iCuridx].vLeftTop.y)
		, int(m_vecFrm[m_iCuridx].vSize.x)
		, int(m_vecFrm[m_iCuridx].vSize.y)
		, RGB(255, 0, 255));
}

CObj* CAnimation::GetOwner()
{ 
	return m_pAnimator->GetOwner();
}
