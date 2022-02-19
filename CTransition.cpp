#include "pch.h"
#include "CTransition.h"

#include "CCore.h"
#include "CStage.h"
#include "CCamera.h"

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
	// 카메라 위치에 영향 x
	Vec prevPos = GetPos();
	SetPos(CCamera::GetInst()->GetOriginalPos(GetPos()));
	Render_Component(_dc);
	SetPos(prevPos);
}

CTransition::~CTransition()
{
}
