#include "pch.h"
#include "CStage_Transition.h"

#include "CCore.h"
#include "CEventMgr.h"

#include "CTransition.h"
#include "CAnimation.h"
#include "CAnimator.h"

void CStage_Transition::Enter()
{
	Init();
}

void CStage_Transition::Init()
{
	m_pTransition = new CTransition;
	m_pTransition->SetPos(Vec{ CCore::GetInst()->GetResolution().x / 2.f, CCore::GetInst()->GetResolution().y / 2.f });
	AddObject(m_pTransition, EOBJ_TYPE::DEFAULT);
}

void CStage_Transition::Update()
{
	CStage::Update();
	CAnimation* pAnimation = m_pTransition->GetAnimator()->GetCurAnimation();
	if (pAnimation->IsFinished())
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)m_eNextChap;

		CEventMgr::GetInst()->AddEvent(event);
	}
}

void CStage_Transition::Render(HDC _dc)
{
	CStage::Render(_dc);
}


void CStage_Transition::Exit()
{
}

CStage_Transition::CStage_Transition()
	:m_eNextChap (ECHAPTER::CHAP_1)
{
}

CStage_Transition::~CStage_Transition()
{
	CStage::Clear();
}
