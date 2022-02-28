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
	// 현재 스테이지 설정
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	m_iPrevMoveCount = m_pCurStage->GetInitMoveCount();

	// 타입 저장
	SetType(EOBSTACLE_TYPE::DYNAMC_SPIKE);

	// 상태
	m_bActive = _bActive;

	// 현재 위치 설정
	SetPos(_pTile->GetCenterPos());

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"spike_up", L"texture\\object\\spike\\up\\", 0.04f, 4);	
	//pAnimator->CreateAnimation(L"spike_down", L"texture\\object\\spike\\down\\", 0.04f, 4);
	//pAnimator->CreateAnimation(L"spike_on", L"texture\\object\\spike\\", 0.05f, 1);
	//pAnimator->CreateAnimation(L"spike_off", L"texture\\object\\spike\\", 0.05f, 1);

	// 애니메이션 저장
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

	// 애니메이션 로드
	pAnimator->LoadAnimation(L"animation\\spike\\spike_up.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_down.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_on.anim");
	pAnimator->LoadAnimation(L"animation\\spike\\spike_off.anim");

	AddComponent(pAnimator);

	// 시작 애니메이션 설정
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

		// Active 된 타일에 언데드 있으면 삭제
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
	// 이전에 저장해둔 이동 카운트와 현재 이동 카운트가 같지 않으면 가시를 on/off 한다.
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

