#include "pch.h"
#include "CStage_Start.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"

CStage_Start::CStage_Start()
{
}

CStage_Start::~CStage_Start()
{
}

void CStage_Start::Init()
{
}

void CStage_Start::Update()
{
	CStage::Update();

	if (IS_KEY_TAP(KEY::ENTER))
	{
		CStageMgr::GetInst()->ChangeStage(ESTAGE_TYPE::PLAY_01);
	}
}

void CStage_Start::Render(HDC _dc)
{
	CStage::Render(_dc);

	TextOut(_dc, 10, 10, L"Here is Start Stage", wcslen(L"Here is Start Stage"));
}

void CStage_Start::Enter()
{
	Init();
}

void CStage_Start::Exit()
{
}

