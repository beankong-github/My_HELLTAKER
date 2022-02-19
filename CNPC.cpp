#include "pch.h"
#include "CNPC.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CStage_Puzzle.h"
#include "CTile.h"
#include "CTileMap.h"

CNPC::CNPC(const wstring& _strName)
{
	SetName(_strName);

	// animation 생성
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(_strName, L"texture\\animation\\npc\\" +_strName + L"\\", 0.06f, 12);

	//animation 저장
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(_strName);
	//pSaveAnim->Save(L"animation\\npc\\");

	// animation 로드
	pAnimator->LoadAnimation(L"animation\\npc\\" + _strName + L".anim");

	// animator 컴포넌트 추가
	AddComponent(pAnimator);

	// animation play
	pAnimator->PlayAnimation(_strName);
}

CNPC::~CNPC()
{
}

void CNPC::Update()
{
}

void CNPC::Render(HDC _dc)
{
	Render_Component(_dc);
}

