// Default Header
#include "pch.h"
#include "CCore.h"
// Manager Header
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CCollisionMgr.h"
// Stage Header
#include "Cstage.h"


CCore::CCore()
	: m_hwnd(nullptr)
	, m_hDC(nullptr)
	, m_hBackBitMap(nullptr)
	, m_hBackDC(nullptr)
	, m_ptResolution{}
{
}

CCore::~CCore()
{
	// DC 해제
	ReleaseDC(m_hwnd, m_hDC);

	// 백 버퍼 해제
	DeleteObject(m_hBackBitMap);
	DeleteDC(m_hBackDC);			// 직접 생성한 DC는 ReleaseDC가 아닌 DeleteDC를 사용한다.
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 화면 크기 초기화 ( 윈도우 해상도에 맞는 크기로 재설정)
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Device Context 생성
	m_hDC = GetDC(m_hwnd);	// 메인 window를 목적으로 하는 DC
	
	// BackBuffer 생성
 	m_hBackBitMap =  CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC =  CreateCompatibleDC(m_hDC);
 	
	// Backbuffer DC가 새로 만든 bitmap(BackBitMap)을 그리기 목적지로 선택한다.
	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitMap);	// m_hBackBitMap과 m_hBackDC 연결
	DeleteObject(hPrevBitMap);												// 연결 후 임시 비트맵 삭제

	// ==================
	//	 Manager Init
	// ==================
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CStageMgr::GetInst()->Init();

	return S_OK;
}

void CCore::Update()
{	// ==================
	//	 Manager Update
	// ==================
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();

	// ==================
	//	 Stage Update
	// ==================
	CStageMgr::GetInst()->Update();

	// ==================
	//	Collision Check
	// ==================
	CCollisionMgr::GetInst()->Update();

	// ==================
	//	  Game Render
	// ==================

	// BackBuffer 화면 지우기
	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	// BackBuffer에 Stage 그리기
	CStageMgr::GetInst()->Render(m_hBackDC);

	// BackBuffer 내용을 윈도우 비트맵으로 옮기기(복사)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);


	// ==================
	//	 Event Handling
	// ==================
	CEventMgr::GetInst()->Update();
}
