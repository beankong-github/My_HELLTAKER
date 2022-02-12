#include "pch.h"
#include "CHero.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTile.h"


CHero::CHero()
	: m_fSpeed(300.f)
	, m_iMoveCount(100)
{
	// 이름 설정
	SetName(L"Hero");

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	pAnimator->CreateAnimation(L"idle", L"texture\\animation\\hero\\idle\\", 0.05f, 12);

	CAnimation* pSaveAnim = nullptr;
	pSaveAnim = pAnimator->FindAnimation(L"idle");
	pSaveAnim->Save(L"animation\\hero\\");


	AddComponent(pAnimator);
	pAnimator->PlayAnimation(L"idle");
}

CHero::~CHero()
{ 
}

void CHero::Update()
{
}

void CHero::Render(HDC _dc)
{
	Render_Component(_dc);
}

void CHero::OnCollisionEnter(CObj* _pOther)
{
}

void CHero::OnCollision(CObj* _pOther)
{
}

void CHero::OnCollisionExit(CObj* _pOther)
{
}

