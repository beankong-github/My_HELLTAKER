#include "pch.h"
#include "CStage_Tool.h"

#include "resource.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"

#include "CObj.h"
#include "CTile.h"

UINT g_iCol;
UINT g_iRow;

CStage_Tool::CStage_Tool()
	: m_hMenu(nullptr)
	, m_eMode(ETOOL_MODE::TILE)
{
}

CStage_Tool::~CStage_Tool()
{
	// 메뉴 삭제
	DestroyMenu(m_hMenu);
}

void CStage_Tool::Init()
{
	// 메뉴생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_WINAPISTUDY));

	Enter();
}

void CStage_Tool::Update()
{
	CStage::Update();

	switch (m_eMode)
	{
	case ETOOL_MODE::TILE:
		Update_Tile();
		break;

	case ETOOL_MODE::OBJECT:
		Update_Object();
		break;

	case ETOOL_MODE::ANIMATION:
		Update_Animation();
		break;
	}

	if (IS_KEY_TAP(KEY::ESC))
	{
		ChangeStage(ESTAGE_TYPE::START);
	}

}

void CStage_Tool::Update_Tile()
{
	// 마우스 클릭 발생 -> 해당 타일 접근 -> 타일 인덱스 증가
	if (IS_KEY_TAP(KEY::LBTN))
	{
		Vec vMousePos = CKeyMgr::GetInst()->GetMousePos();
	}
}

void CStage_Tool::Update_Object()
{
}

void CStage_Tool::Update_Animation()
{
}


void CStage_Tool::Render(HDC _dc)
{
	CStage::Render(_dc);
}

void CStage_Tool::Enter()
{
	// 메뉴 부착
	SetMenu(CCore::GetInst()->GetMainWndHWND(), m_hMenu);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), true);

	// 타일 임시 생성 (10x10) 
	//CreateTile(10, 10);
}

void CStage_Tool::Exit()
{
	// 메뉴 제거
	SetMenu(CCore::GetInst()->GetMainWndHWND(), nullptr);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), false);
}


INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CStage_Tool::PopupCreateTile()
{
	INT_PTR dwID = DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILE_COUNT), CCore::GetInst()->GetMainWndHWND(), TileCountProc);

	// OK 버튼이 눌렸을 떄
	if (IDOK == dwID)
	{
		CreateTile(g_iCol, g_iRow);
	}

	// CANCEL 버튼이 눌렸을 때
	else if (IDCANCEL == dwID)
		return;
}


// ================================================
// TileCount 다이얼로그의 전용 메세지 처리기 (전역)함수
// ================================================

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// EidtControl에서 입력한 값을 가져온다.
			g_iCol = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, true);
			g_iRow = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, true);
			
			EndDialog(hDlg, LOWORD(wParam));
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			// EndDialog의 두번째 인자는 Dialog 종료시 반환되는 값이다.
			// 어떤 버튼이 눌려서 종료된 것인지 알리기 위해서 눌린 버튼의 아이디 값을 넣어 놓는다.
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		
		break;
	}
	return (INT_PTR)FALSE;
}

