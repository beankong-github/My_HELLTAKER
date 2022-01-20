#include "pch.h"
#include "CStage_Play01.h"
#include "CKeyMgr.h"
#include "CCore.h"

#include "CPlayer.h"
#include "CMonster.h"

CStage_Play01::CStage_Play01()
{
}

CStage_Play01::~CStage_Play01()
{
}

void CStage_Play01::Init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// player 추가
	CObj* pPlayerObj = new CPlayer;
	pPlayerObj->SetPos(Vec(ptResolution.x / 2.f, (ptResolution.y * 3.f) / 4.f));
	pPlayerObj->SetScale(Vec(100, 100));
	AddObject(pPlayerObj, EOBJ_TYPE::PLAYER);

	// Monster 추가
	CObj* pMonsterObj = new CMonster;
	pMonsterObj->SetPos(Vec(ptResolution.x / 2.f, (ptResolution.y * 1.f) / 4.f));
	pMonsterObj->SetScale(Vec(50, 50));
	AddObject(pMonsterObj, EOBJ_TYPE::MONSTER);
}

void CStage_Play01::Update()
{
	CStage::Update();

	if (IS_KEY_TAP(KEY::ESC))
	{
		ChangeStage(ESTAGE_TYPE::START);
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
