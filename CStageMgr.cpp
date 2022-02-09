#include "pch.h"
#include "CStageMgr.h"

#include "CKeyMgr.h"
#include "CEventMgr.h"

#include "CStage.h"
#include "CStage_Start.h"
#include "CStage_Play01.h"
#include "CStage_Tool.h"
#include "CStage_Puzzle.h"
//#include "CStage_Transition.h"
//#include "CStage_Exit.h"

CStageMgr::CStageMgr()
	:m_arrStage{}
	,m_pCurStage(nullptr)
{}

CStageMgr::~CStageMgr()
{
	// 스테이지는 Heap 메모리 영역에 동적할당 할 것이므로 
	// 스테이지가 종료될 때 할당 해제해야 한다.
	for (UINT i = 0; i < (UINT)ESTAGE_TYPE::STAGE_END; i++)
	{
		for (UINT j = 0; j < (UINT)ECHAPTER::END; j++)
		{
			if (nullptr != m_arrStage[i][j])
			{
				delete m_arrStage[i][j];
			}
		}
	}

}

void CStageMgr::Init()
{
	// 모든 스테이지 생성
	m_arrStage[(UINT)ESTAGE_TYPE::TOOL][0] = new CStage_Tool;
	m_arrStage[(UINT)ESTAGE_TYPE::START][0] = new CStage_Start;
	m_arrStage[(UINT)ESTAGE_TYPE::PLAY_01][0] = new CStage_Play01;

	for (UINT i = 1; i < (UINT)ECHAPTER::END; i++)
	{
		CStage_Puzzle* newStage = new CStage_Puzzle((ECHAPTER)i);
		m_arrStage[(UINT)ESTAGE_TYPE::PUZZLE][i] = newStage;
	}

	//m_arrStage[(UINT)ESTAGE_TYPE::PLAY_02] = new CStage_Play02;
	//m_arrStage[(UINT)ESTAGE_TYPE::EXIT] = new CStage_Exit;
	
	// 첫 스테이지 지정
	m_pCurStage = m_arrStage[(UINT)ESTAGE_TYPE::PUZZLE][ECHAPTER::CHAP_01];
	m_pCurStage->Enter();
}

void CStageMgr::Update()
{
	m_pCurStage->Update();
	m_pCurStage->LateUpdate();
	
	// 키 입력에 따라 카메라 이동
	if (IS_KEY_PRESSED(KEY::_1))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_01;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_2))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_02;

		CEventMgr::GetInst()->AddEvent(event);
	}
	
	if (IS_KEY_PRESSED(KEY::_3))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_03;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_4))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_04;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_5))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_05;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_6))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_06;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_7))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_07;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_8))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_08;

		CEventMgr::GetInst()->AddEvent(event);
	}

	if (IS_KEY_PRESSED(KEY::_9))
	{
		tEventInfo event;
		event.eType = EEVENT_TYPE::STAGE_CHANGE;
		event.lParam = (DWORD_PTR)ESTAGE_TYPE::PUZZLE;
		event.wParam = (DWORD_PTR)ECHAPTER::CHAP_09;

		CEventMgr::GetInst()->AddEvent(event);
	}

}

void CStageMgr::Render(HDC _dc)
{
	m_pCurStage->Render(_dc);
}


void CStageMgr::ChangeStage(ESTAGE_TYPE _eNextStage, ECHAPTER _iChapter)
{
	// 같은 Stage로 change 요청이 들어오면 assert
	//assert(m_pCurStage != m_arrStage[(UINT)_eNextStage][(UINT)_iChapter]);

	m_pCurStage->Exit();
	m_pCurStage= m_arrStage[(UINT)_eNextStage][(UINT)_iChapter];
	m_pCurStage->Enter();
}
