#include "pch.h"
#include "CStage_Tool.h"

#include "resource.h"
#include "CCore.h"

#include "CObj.h"
#include "CTile.h"

CStage_Tool::CStage_Tool()
	:m_hMenu(nullptr)
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
	for (int iRow = 0; iRow < 10; ++iRow)
	{
		for (int iCol = 0; iCol < 10; ++iCol)
		{
			CObj* pTile = new CTile;
			pTile->SetScale(Vec{ (float)TILE_SIZE, (float)TILE_SIZE });
			pTile->SetPos(Vec{ (float)(iCol * TILE_SIZE), (float)(iRow * TILE_SIZE) });
			AddObject(pTile, EOBJ_TYPE::TILE);
		}
	}
}

void CStage_Tool::Exit()
{
	// 메뉴 제거
	SetMenu(CCore::GetInst()->GetMainWndHWND(), nullptr);
	CCore::GetInst()->ChangeWindowSize(CCore::GetInst()->GetResolution(), false);
}

