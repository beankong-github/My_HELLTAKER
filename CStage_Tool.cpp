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
	SetStageName(L"Tool");
}

CStage_Tool::~CStage_Tool()
{
	// �޴� ����
	DestroyMenu(m_hMenu);
}

void CStage_Tool::Init()
{
	// �޴�����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_MYGAMEENGINE));

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
	// ���콺 Ŭ�� �߻� -> �ش� Ÿ�� ���� -> Ÿ�� �ε��� ����
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
	Init();

	// �޴� ����
	SetMenu(CCore::GetInst()->GetMainWndHWND(), m_hMenu);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), true);

	// Ÿ�� �ӽ� ���� (10x10) 
	//CreateTile(10, 10);
}

void CStage_Tool::Exit()
{
	// �޴� ����
	SetMenu(CCore::GetInst()->GetMainWndHWND(), nullptr);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), false);
}


INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CStage_Tool::PopupCreateTile()
{
	INT_PTR dwID = DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILE_COUNT), CCore::GetInst()->GetMainWndHWND(), TileCountProc);

	// OK ��ư�� ������ ��
	if (IDOK == dwID)
	{
		//CreateTile(g_iCol, g_iRow, Vec{0.f, 0.f});
	}

	// CANCEL ��ư�� ������ ��
	else if (IDCANCEL == dwID)
		return;
}


// ================================================
// TileCount ���̾�α��� ���� �޼��� ó���� (����)�Լ�
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
			// EidtControl���� �Է��� ���� �����´�.
			g_iCol = GetDlgItemInt(hDlg, IDC_EDIT1, FALSE, true);
			g_iRow = GetDlgItemInt(hDlg, IDC_EDIT2, FALSE, true);
			
			EndDialog(hDlg, LOWORD(wParam));
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			// EndDialog�� �ι�° ���ڴ� Dialog ����� ��ȯ�Ǵ� ���̴�.
			// � ��ư�� ������ ����� ������ �˸��� ���ؼ� ���� ��ư�� ���̵� ���� �־� ���´�.
			EndDialog(hDlg, LOWORD(wParam));
		}
		
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

