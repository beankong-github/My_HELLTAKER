#include "pch.h"
#include "CTransition.h"

#include "CCore.h"
#include "CStage.h"
#include "CCamera.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CSound.h"

CTransition::CTransition()
	: m_fSoundInterval(1.3f)
	, m_fAddTime(0.f)
{
	// ���� �ε�
	m_pTransitionSound_1 = CResMgr::GetInst()->LoadSound(L"screen_changer_part1", L"sound\\screen_changer_part1.wav");
	m_pTransitionSound_2 = CResMgr::GetInst()->LoadSound(L"screen_changer_part2", L"sound\\screen_changer_part2.wav");

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"transition", L"texture\\animation\\transition\\", 0.08f, 29);
	
	// �ִϸ��̼� ����
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"transition");
	//pSaveAnim->Save(L"animation\\etc\\");

	// �ִϸ��̼� �ε�
	pAnimator->LoadAnimation(L"animation\\etc\\transition.anim");

	AddComponent(pAnimator);

	// ���� �ִϸ��̼� ����
	m_pTransitionSound_1->Play();
	pAnimator->PlayAnimation(L"transition", false);
}

void CTransition::Update()
{
	// �ι�° ���� ���
	m_fAddTime += DS;
	if (m_fAddTime >= m_fSoundInterval)
	{
		if(nullptr != m_pTransitionSound_2 )
			m_pTransitionSound_2->Play();
		m_pTransitionSound_2 = nullptr;
		m_fAddTime = 0;
	}
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
