#include "pch.h"
#include "CKey.h"

#include "CStage_Puzzle.h"
#include "CStageMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTile.h"

CKey::CKey(CTile* _pTile)
	:CObstacle(_pTile)
{
	// 현재 스테이지 설정
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	
	// 타입 저장
	SetType(EOBSTACLE_TYPE::KEY);
	
	// 현재 위치 설정
	SetPos(_pTile->GetCenterPos());

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"key", L"texture\\object\\key\\", 0.07f, 11);

	// 애니메이션 저장
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"key");
	//pSaveAnim->Save(L"animation\\key\\");	

	pAnimator->LoadAnimation(L"animation\\key\\key.anim");

	AddComponent(pAnimator);

	pAnimator->PlayAnimation(L"key");
}

CKey::~CKey()
{
}

void CKey::Update()
{
}

void CKey::Render(HDC _dc)
{
	Render_Component(_dc);
}
