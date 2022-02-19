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

	// animation ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(_strName, L"texture\\animation\\npc\\" +_strName + L"\\", 0.06f, 12);

	//animation ����
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(_strName);
	//pSaveAnim->Save(L"animation\\npc\\");

	// animation �ε�
	pAnimator->LoadAnimation(L"animation\\npc\\" + _strName + L".anim");

	// animator ������Ʈ �߰�
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

