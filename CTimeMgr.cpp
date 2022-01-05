#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_liFreqency{}
	, m_liPrevCount{}
	, m_liCurCount{}
	, m_iFPS(0)
	, m_fDS(0.f)
	, m_iElapsedTime(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	/// <summary>
	/// QueryPerformanceCounter (_Out_ LARGE_INTEGER* lpPerformanceCount) 
	/// - 8바이트 정수(longlong)를 돌려 받음
	/// - 초당 카운트하는 수를 반환 (대략 초당 천만)
	/// </summary>
	QueryPerformanceFrequency(&m_liFreqency);
	/// <summary>
	/// QueryPerformanceCounter(_Out_ LARGE_INTEGER* lpPerformanceCount)
	/// - 8바이트 정수(longlong)를 돌려받음
	/// - 현재까지 카운트를 한 수
	/// - Delta Second : 현재까지 카운트를 한 수 / 초당 카운트를 한 수
	/// </summary>
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::Update()
{
	// ===============================
	//			DS 구하기
	// ===============================
	
	// 현재 카운팅 확인
	QueryPerformanceCounter(&m_liCurCount);
	
	// 이전 카운팅과 현재 카운팅의 차이를 초당 카운팅으로 나누어 1프레임이 실행되는데 걸린 시간(Delta Second)을 구한다
	m_fDS = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)m_liFreqency.QuadPart;
	
#ifdef _DEBUG
	// 디버그 모드 한정 강제 60FPS 확보
	if (m_fDS > (1.f / 60.f))
	{
		m_fDS = 1.f / 60.f;
	}
#endif

	// 현재 카운팅 값을 저장해둔다 ( 다음번 DS체크에 활용하기 위해서)
	m_liPrevCount.QuadPart = m_liCurCount.QuadPart;

	// 시간 누적 ( 경과 시간은 프레임 실행 시간의 누적이다 )
	m_fOneSec += m_fDS;


	// ===============================
	//			FPS 구하기
	// ===============================

	m_iFPS++;
	
	// 누적 시간이 1초를 넘는 순간
	if (m_fOneSec >= 1.f)
	{
		m_fOneSec = m_fOneSec - 1.f;
		m_iElapsedTime++;

		wchar_t szStr[255] = L"";
		wsprintf(szStr, L"FPS: %d || Elapsed time: %d", m_iFPS, m_iElapsedTime);
		SetWindowTextW(CCore::GetInst()->GetMainWndHWND(), szStr);

		m_iFPS = 0;
	}

}