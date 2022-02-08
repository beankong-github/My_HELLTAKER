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
#include "CCamera.h"
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
	// DC ����
	ReleaseDC(m_hwnd, m_hDC);

	// ��&�귯�� ����
	DeleteObject(m_hGreenPen);
	DeleteObject(m_hRedPen);
	DeleteObject(m_hBGBrush);

	// �� ���� ����
	DeleteObject(m_hBackBitMap);
	DeleteDC(m_hBackDC);			// ���� ������ DC�� ReleaseDC�� �ƴ� DeleteDC�� ����Ѵ�.
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;

	// ������ ������ ����
	ChangeWindowSize(_ptResolution, false);

	// Pen ����
	m_hGreenPen = CreatePen(PS_SOLID, 1, RGB(120, 250, 50));
	m_hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_hBGBrush = CreateSolidBrush(RGB(2, 2, 27));

	// Device Context ����
	m_hDC = GetDC(m_hwnd);	// ���� window�� �������� �ϴ� DC
	
	// BackBuffer ����
 	m_hBackBitMap =  CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC =  CreateCompatibleDC(m_hDC);
	SelectObject(m_hBackDC, m_hBGBrush);		// �⺻ Brush ���� ����

	// Backbuffer DC�� ���� ���� bitmap(BackBitMap)�� �׸��� �������� �����Ѵ�.
	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitMap);	// m_hBackBitMap�� m_hBackDC ����
	DeleteObject(hPrevBitMap);												// ���� �� �ӽ� ��Ʈ�� ����

	// ==================
	//	 Manager Init
	// ==================
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CStageMgr::GetInst()->Init();
	CCamera::GetInst()->Init();

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
	CCamera::GetInst()->Update();
	CStageMgr::GetInst()->Update();

	// ==================
	//	Collision Check
	// ==================
	CCollisionMgr::GetInst()->Update();

	// ==================
	//	  Game Render
	// ==================

	// BackBuffer ȭ�� �����
	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	// BackBuffer�� Stage �׸���
	CStageMgr::GetInst()->Render(m_hBackDC);
	CCamera::GetInst()->Render(m_hBackDC);

	// BackBuffer ������ ������ ��Ʈ������ �ű��(����)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);


	// ==================
	//	 Event Handling
	// ==================
	CEventMgr::GetInst()->Update();
}

void CCore::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	// ȭ�� ũ�� �ʱ�ȭ ( ������ �ػ󵵿� �´� ũ��� �缳��)
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	m_ptResolution = _ptResolution;
}
