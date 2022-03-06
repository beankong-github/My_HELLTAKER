#include "pch.h"
#include "CStage_Start.h"

#include "CCore.h"
#include "CStageMgr.h"
#include "CKeyMgr.h"
#include "CEventMgr.h"

#include "CTexture.h"
#include "CUI_Dialog.h"

CStage_Start::CStage_Start()
{
	SetStageName(L"Start");

	m_pDailog = new CUI_Dialog(L"intro");
	m_pDailog->SetCurStage(this);
	AddObject(m_pDailog, EOBJ_TYPE::DIALOG);
}

CStage_Start::~CStage_Start()
{
}

void CStage_Start::Init()
{
}

void CStage_Start::Update()
{
	CStage::Update();
}

void CStage_Start::Render(HDC _dc)
{
	CStage::Render(_dc);
}

void CStage_Start::Enter()
{
}

void CStage_Start::Exit()
{
	CStage::Clear();
}

void CStage_Start::FirstOptionSelected()
{
	m_pDailog->SetCurPage(m_pDailog->GetCurPage()+1);
}

void CStage_Start::SecondOptionSelected()
{
	if (L"intro" == m_pDailog->GetID())
	{
		HWND hWnd = CCore::GetInst()->GetMainWndHWND();
		if (hWnd) SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
}

void CStage_Start::DialogTermination()
{
	tEventInfo eventInfo;
	eventInfo.eType = EEVENT_TYPE::STAGE_CHANGE;
	eventInfo.lParam = (DWORD)ESTAGE_TYPE::PUZZLE;
	eventInfo.wParam = (DWORD)ECHAPTER::CHAP_1;
	CEventMgr::GetInst()->AddEvent(eventInfo);
}

