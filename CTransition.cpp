#include "pch.h"
#include "CTransition.h"

#include "CStage.h"

#include "CAnimator.h"
#include "CAnimation.h"

CTransition::CTransition()
{
	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	pAnimator->CreateAnimation(L"transition", L"texture\\animation\\transition\\", 0.05f, 29);
	
	// 애니메이션 저장
	CAnimation* pSaveAnim = nullptr;
	pSaveAnim = pAnimator->FindAnimation(L"transition");
	pSaveAnim->Save(L"animation\\etc\\");

	// 애니메이션 로드
	//pAnimator->LoadAnimation(L"animation\\etc\\transition.anim");

	AddComponent(pAnimator);

	// 시작 애니메이션 설정
	pAnimator->PlayAnimation(L"transition", false);
}

void CTransition::Update()
{
}

void CTransition::Render(HDC _dc)
{
	Render_Component(_dc);
}

CTransition::~CTransition()
{
}
