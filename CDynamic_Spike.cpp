#include "pch.h"
#include "CDynamic_Spike.h"

#include "CStageMgr.h"
#include "CStage_Puzzle.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTile.h"
#include "CTileMap.h"

#include "CUndead.h"
#include "CHero.h"

CDynamic_Spike::CDynamic_Spike(CTile* _pTile, bool _bActive)
	: CObstacle(_pTile)
{
	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	m_iPrevMoveCount = m_pCurStage->GetInitMoveCount();

	// Ÿ�� ����
	SetType(EOBSTACLE_TYPE::DYNAMC_SPIKE);

	// ����
	m_bActive = _bActive;

	// ���� ��ġ ����
	SetPos(_pTile->GetCenterPos());

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"spike_up", L"texture\\object\\spike\\up\\", 0.04f, 4);	
	//pAnimator->CreateAnimation(L"spike_down", L"texture\\object\\spike\\down\\", 0.04f, 4);
	//pAnimator->CreateAnimation(L"spike_on", L"texture\\object\\spike\\", 0.05f, 1);
	//pAnimator->CreateAnimation(L"spike_off", L"texture\\object\\spike\\", 0.05f, 1);

	// �ִϸ��̼� ����
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"spike_up");
	//pSaveAnim->Save(L"animation\\spike\\");		
	//
	//pSaveAnim = pAnimator->FindAnimation(L"spike_down");
	//pSaveAnim->Save(L"animation\\spike\\");		
	//
	//pSaveAnim = pAnimator->FindAnimation(L"spike_on");
	//pSaveAnim->Save(L"animation\\spike\\");		
	//
	//pSaveAnim = pAnimator->FindAnimation(L"spike_off");
	//pSaveAnim->Save(L"animation\\spike\\");	

	// �ִϸ��̼� �ε�
	pAnimator->LoadAnimation(L"animation\\spike\\spike_up.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_down.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_on.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_off.anim");

	AddComponent(pAnimator);

	// ���� �ִϸ��̼� ����
	if(_bActive) 
		pAnimator->PlayAnimation(L"spike_on");
	else
		pAnimator->PlayAnimation(L"spike_off");
}

CDynamic_Spike::~CDynamic_Spike()
{
}

void CDynamic_Spike::ChangeAcivation()
{ 
	m_bActive = !m_bActive;
	if (m_bActive)
	{
		GetAnimator()->PlayAnimation(L"spike_up", false);

		// Active �� Ÿ�Ͽ� �𵥵� ������ ����
		CUndead* pUndead = (CUndead*)(GetCurTile()->FindObstacle(EOBSTACLE_TYPE::UNDEAD));
		if (nullptr != pUndead)
		{
			pUndead->SetState(EOBSTACLE_STATE::DEAD);
			return;
		}
	}
	else
		GetAnimator()->PlayAnimation(L"spike_down", false);
}

void CDynamic_Spike::Update()
{
	// ������ �����ص� �̵� ī��Ʈ�� ���� �̵� ī��Ʈ�� ���� ������ ���ø� on/off �Ѵ�.
	if (m_iPrevMoveCount != m_pCurStage->GetCurMoveCount())
	{
		ChangeAcivation();
		m_iPrevMoveCount = m_pCurStage->GetCurMoveCount();
	}
}

void CDynamic_Spike::Render(HDC _dc)
{
	CAnimation* curAnim = GetAnimator()->GetCurAnimation();
	if (curAnim->IsFinished())
	{
		curAnim->Reset();
		if (L"spike_up" == curAnim->GetName())
		{
			GetAnimator()->PlayAnimation(L"spike_on");
		}
		else if (L"spike_down" == curAnim->GetName())
		{
			GetAnimator()->PlayAnimation(L"spike_off");
		}
	}

	Render_Component(_dc);
}

