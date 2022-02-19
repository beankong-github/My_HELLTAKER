#include "pch.h"
#include "CTransition.h"

#include "CCore.h"
#include "CStage.h"
#include "CCamera.h"

#include "CAnimator.h"
#include "CAnimation.h"

CTransition::CTransition()
{
	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	pAnimator->CreateAnimation(L"transition", L"texture\\animation\\transition\\", 0.05f, 29);
	
	// �ִϸ��̼� ����
	CAnimation* pSaveAnim = nullptr;
	pSaveAnim = pAnimator->FindAnimation(L"transition");
	pSaveAnim->Save(L"animation\\etc\\");

	// �ִϸ��̼� �ε�
	//pAnimator->LoadAnimation(L"animation\\etc\\transition.anim");

	AddComponent(pAnimator);

	// ���� �ִϸ��̼� ����
	pAnimator->PlayAnimation(L"transition", false);
}

void CTransition::Update()
{
}

void CTransition::Render(HDC _dc)
{
	// ī�޶� ��ġ�� ���� x
	Vec prevPos = GetPos();
	SetPos(CCamera::GetInst()->GetOriginalPos(GetPos()));
	Render_Component(_dc);
	SetPos(prevPos);
}

CTransition::~CTransition()
{
}
