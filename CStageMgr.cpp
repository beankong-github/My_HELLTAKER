#include "pch.h"
#include "CStageMgr.h"
#include "CStage.h"
#include "CStage_Start.h"
#include "CStage_Play01.h"
#include "CStage_Tool.h"
//#include "CStage_Play02.h"
//#include "CStage_Exit.h"

CStageMgr::CStageMgr()
	:m_arrStage{}
	,m_pCurStage(nullptr)
{}

CStageMgr::~CStageMgr()
{
	// 스테이지는 Heap 메모리 영역에 동적할당 할 것이므로 
	// 스테이지가 종료될 때 할당 해제해야 한다.
	for (size_t i = 0; i < (int)ESTAGE_TYPE::STAGE_END; i++)
	{
		if (nullptr != m_arrStage[i])
		{
			delete m_arrStage[i];
		}
	}

}

void CStageMgr::Init()
{
	// 모든 스테이지 생성
	m_arrStage[(UINT)ESTAGE_TYPE::TOOL] = new CStage_Tool;
	m_arrStage[(UINT)ESTAGE_TYPE::START] = new CStage_Start;
	m_arrStage[(UINT)ESTAGE_TYPE::PLAY_01] = new CStage_Play01;
	//m_arrStage[(UINT)ESTAGE_TYPE::PLAY_02] = new CStage_Play02;
	//m_arrStage[(UINT)ESTAGE_TYPE::EXIT] = new CStage_Exit;
	
	// 첫 스테이지 지정
	m_pCurStage = m_arrStage[(UINT)ESTAGE_TYPE::TOOL];
	m_pCurStage->Init();
}

void CStageMgr::Update()
{
	m_pCurStage->Update();
	m_pCurStage->LateUpdate();
}

void CStageMgr::Render(HDC _dc)
{
	m_pCurStage->Render(_dc);
}

void CStageMgr::ChangeStage(ESTAGE_TYPE _eNextStage)
{
	// 같은 Stage로 change 요청이 들어오면 assert
	assert(m_pCurStage != m_arrStage[(UINT)_eNextStage]);

	m_pCurStage->Exit();
	m_pCurStage= m_arrStage[(UINT)_eNextStage];	
	m_pCurStage->Enter();
}
