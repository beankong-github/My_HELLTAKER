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
	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	
	// Ÿ�� ����
	SetType(EOBSTACLE_TYPE::KEY);
	
	// ���� ��ġ ����
	SetPos(_pTile->GetCenterPos());

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"key", L"texture\\object\\key\\", 0.07f, 11);

	// �ִϸ��̼� ����
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
