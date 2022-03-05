#include "pch.h"
#include "CStage_Start.h"

#include "CStageMgr.h"
#include "CKeyMgr.h"
#include "CTexture.h"

#include "CUI_Dialog.h"

CStage_Start::CStage_Start()
{
	SetStageName(L"Start");
}

CStage_Start::~CStage_Start()
{
}

void CStage_Start::Init()
{
	CUI_Dialog* dialog = new CUI_Dialog(L"intro");
	AddObject(dialog, EOBJ_TYPE::DIALOG);
}

void CStage_Start::Update()
{
	CStage::Update();
}

void CStage_Start::Render(HDC _dc)
{
	CStage::Render(_dc);

	TextOut(_dc, 10, 10, L"Here is Start Stage", (int)wcslen(L"Here is Start Stage"));
}

void CStage_Start::Enter()
{
	Init();
}

void CStage_Start::Exit()
{
	CStage::Clear();
}

