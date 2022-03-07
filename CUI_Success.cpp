#include "pch.h"
#include "CUI_Success.h"

#include "CCore.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"
#include "CSound.h"

CUI_Success::CUI_Success()
{
	// 위치 결정
	Vec resolution = CCore::GetInst()->GetResolution();
	SetPos(Vec{ resolution.x / 2, resolution.x*2/3 });

	// 사운드 로드
	m_pSound = CResMgr::GetInst()->LoadSound(L"dialogue_success_01", L"sound\\dialogue_success_01.wav");

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	pAnimator->CreateAnimation(L"ui_success", L"texture\\ui\\dialog\\success\\", 0.05f, 8);

	CAnimation* pSaveAnim = pAnimator->FindAnimation(L"ui_success");
	pSaveAnim->Save(L"animation\\etc\\");

	//pAnimator->LoadAnimation(L"animation\\etc\\ui_success.anim");

	AddComponent(pAnimator);
}

CUI_Success::~CUI_Success()
{
}

void CUI_Success::PlayAnimation()
{
	m_pSound->Play();
	GetAnimator()->PlayAnimation(L"ui_success");
}

void CUI_Success::Update()
{
	CUI::Update();
}

void CUI_Success::Render(HDC _dc)
{
	CUI::Render(_dc);
}

