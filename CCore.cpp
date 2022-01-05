#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CPlayer player;

CCore::CCore()
	: m_hwnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
{
}

CCore::~CCore()
{
	// DC 해제
	ReleaseDC(m_hwnd, m_hDC);
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
	m_hDC = GetDC(m_hwnd);
	
	// Manager 초기화
	CTimeMgr::GetInst()->Init();


	// 플레이어 배치
	player.SetPos(Vec{m_ptResolution.x / 2, m_ptResolution.y / 2 });
	player.SetScale(Vec{100, 100});


	return S_OK;
}

void CCore::Update()
{	// ==================
	//	 Manager Update
	// ==================
	CTimeMgr::GetInst()->Update();


	// ==================
	//	 Object Update
	// ==================

	player.Update();


	// ==================
	//	  Game Render
	// ==================

	// 화면 지우기
	//Rectangle(m_hDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	player.Render(m_hDC);
}
