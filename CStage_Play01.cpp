#include "pch.h"
#include "CStage_Play01.h"
#include "CPlayer.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"

CStage_Play01::CStage_Play01()
{
}

CStage_Play01::~CStage_Play01()
{
}

void CStage_Play01::Init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// player ÃÊ±âÈ­
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec{ ptResolution.x / 2, ptResolution.y / 2 });
	pObj->SetScale(Vec{ 100, 100 });
	AddObject(pObj);
}

void CStage_Play01::Update()
{
	CStage::Update();

	if (IS_KEY_TAP(KEY::ENTER))
	{
		CStageMgr::GetInst()->ChangeStage(ESTAGE_TYPE::START);
	}

}

void CStage_Play01::Render(HDC _dc)
{
	CStage::Render(_dc);

	TextOut(_dc, 10, 10, L"Here is Play01 Stage",(int)wcslen(L"Here is Play01 Stage"));
}

void CStage_Play01::Enter()
{
	Init();
}

void CStage_Play01::Exit()
{
	CStage::Clear();
}
