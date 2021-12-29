#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"

CPlayer player;

CCore::CCore()
	: m_hwnd(nullptr),
	m_hDC(nullptr),
	m_ptResolution{}
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

	// 화면 크기 초기화
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Device Context 생성
	m_hDC = GetDC(m_hwnd);
	
	// 플레이어 배치
	player.SetPos(POINT{m_ptResolution.x/2, m_ptResolution.y/2});
	player.SetScale(POINT{100, 100});


	return S_OK;
}

void CCore::Update()
{ 
	static int i = 0;
	i++;	// 초당 함수 실행 횟수 카운트

	static ULONGLONG iPrevCount = GetTickCount64();		// 최초 1회만 실행
	ULONGLONG iCurCount = GetTickCount64();				// 매번 실행
	
	// 1초에 한번씩 조건에 걸림
	if (iCurCount - iPrevCount > 1000)
	{
		wchar_t szOut[255] = {};
		wsprintf(szOut, L"초당 CCore::Update 함수 호출 횟수: %d", i);
		SetWindowText(m_hwnd, szOut);

		i = 0;
		iPrevCount = iCurCount;
	}

	player.Update();

	
	// 화면 지우기
	Rectangle(m_hDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	player.Render(m_hDC);
}
