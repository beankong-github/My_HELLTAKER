#include "pch.h"
#include "CStage_Play01.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCollider.h"

CStage_Play01::CStage_Play01()
{
	SetStageName(L"Play01");
}

CStage_Play01::~CStage_Play01()
{
}

void CStage_Play01::Enter()
{
	Init();
	CCamera::GetInst()->FadeOut(0.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CStage_Play01::Init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// player 추가
	CObj* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec(ptResolution.x / 2.f, (ptResolution.y * 3.f) / 4.f));
	pPlayer->SetScale(Vec(100, 100));
	AddObject(pPlayer, EOBJ_TYPE::PLAYER);

	// Monster 추가
	CObj* pMonster = new CMonster;
	pMonster->SetPos(Vec(ptResolution.x / 2.f, (ptResolution.y * 1.f) / 4.f));
	pMonster->SetScale(Vec(50, 50));
	pMonster->GetCollider()->SetScale(pMonster->GetScale());
	AddObject(pMonster, EOBJ_TYPE::MONSTER);

	// 충돌
	CCollisionMgr::GetInst()->CollisionOn(EOBJ_TYPE::MONSTER, EOBJ_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionOn(EOBJ_TYPE::MONSTER, EOBJ_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionOn(EOBJ_TYPE::PLAYER, EOBJ_TYPE::MONSTER_PROJECTILE);
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


void CStage_Play01::Exit()
{
	CStage::Clear();
}
