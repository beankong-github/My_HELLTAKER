#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CObj.h"

CAnimator::CAnimator()
	: CComponent(ECOM_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
	, m_bRepeat(true)
{
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		delete iter->second;
	}
	m_mapAnim.clear();
}

void CAnimator::Update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();
		if (m_bRepeat && m_pCurAnim->IsFinished())
		{
			m_pCurAnim->Reset();
		}
	}
}

void CAnimator::Render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Render(_dc);
	}
}

void CAnimator::CreateAnimation(const wstring& _strAnimName, const wstring& _strRelativePath, float _fDuration, UINT _iFrmCount)
{	
	// 이미 생성된 애니메이션이면 오류발생
	CAnimation* pAnim = FindAnimation(_strAnimName);
	assert(!pAnim);

	pAnim = new CAnimation;
	pAnim->Create(_strAnimName, _strRelativePath, _fDuration, _iFrmCount);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(_strAnimName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if(iter==m_mapAnim.end())
		return nullptr;
	
	return iter->second;
}

void CAnimator::PlayAnimation(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim =  FindAnimation(_strName);
	assert(m_pCurAnim);
	m_bRepeat = _bRepeat;
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_strRelativePath);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

