#include "pch.h"
#include "CEffect.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect::CEffect() 
	: m_wstrCurEffect()
{
	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	
	// 피 효과
	pAnimator->CreateAnimation(L"blood_1", L"texture\\animation\\effect\\blood\\blood_1\\", 0.04f, 6);
	pAnimator->CreateAnimation(L"blood_2", L"texture\\animation\\effect\\blood\\blood_2\\", 0.04f, 6);
	pAnimator->CreateAnimation(L"blood_3", L"texture\\animation\\effect\\blood\\blood_3\\", 0.04f, 6);

	// 아이템 효과
	pAnimator->CreateAnimation(L"item_effect", L"texture\\animation\\effect\\item_effect\\", 0.04f, 9);

	// 이동 효과 
	pAnimator->CreateAnimation(L"move_effect_1", L"texture\\animation\\effect\\move_effect\\1\\", 0.06f, 3);
	pAnimator->CreateAnimation(L"move_effect_2", L"texture\\animation\\effect\\move_effect\\2\\", 0.06f, 3);
	pAnimator->CreateAnimation(L"move_effect_3", L"texture\\animation\\effect\\move_effect\\3\\", 0.06f, 3);

	// 작은 마찰 효과
	pAnimator->CreateAnimation(L"small_vfx_1", L"texture\\animation\\effect\\small_vfx\\1\\", 0.05f, 4);
	pAnimator->CreateAnimation(L"small_vfx_2", L"texture\\animation\\effect\\small_vfx\\2\\", 0.05f, 4);

	// 큰 마찰 효과
	pAnimator->CreateAnimation(L"vfx_1", L"texture\\animation\\effect\\vfx\\1\\", 0.05f, 5);
	pAnimator->CreateAnimation(L"vfx_2", L"texture\\animation\\effect\\vfx\\2\\", 0.05f, 5);

	// 성공 효과
	pAnimator->CreateAnimation(L"success_effect", L"texture\\animation\\effect\\success_effect\\", 0.06f, 15);

	// 애니메이션 저장
	CAnimation* pSaveAnim = nullptr;
	pSaveAnim = pAnimator->FindAnimation(L"blood_1");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"blood_2");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"blood_3");
	pSaveAnim->Save(L"animation\\effect\\");	

	pSaveAnim = pAnimator->FindAnimation(L"item_effect");
	pSaveAnim->Save(L"animation\\effect\\");	

	pSaveAnim = pAnimator->FindAnimation(L"move_effect_1");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"move_effect_2");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"move_effect_3");
	pSaveAnim->Save(L"animation\\effect\\");	

	pSaveAnim = pAnimator->FindAnimation(L"small_vfx_1");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"small_vfx_2");
	pSaveAnim->Save(L"animation\\effect\\");

	pSaveAnim = pAnimator->FindAnimation(L"vfx_1");
	pSaveAnim->Save(L"animation\\effect\\");	
	pSaveAnim = pAnimator->FindAnimation(L"vfx_2");
	pSaveAnim->Save(L"animation\\effect\\");

	pSaveAnim = pAnimator->FindAnimation(L"success_effect");
	pSaveAnim->Save(L"animation\\effect\\");	

	

	// 애니메이션 로드
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_2.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_3.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\item_effect.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_2.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_3.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\small_vfx_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\small_vfx_2.anim");

	// 애니메이션 컴포넌트 추가
	AddComponent(pAnimator);
}

CEffect::~CEffect()
{
}

void CEffect::PlayEffect(wstring _wstrName, Vec _vPos)
{
	SetPos(_vPos);

	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;
	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());;

	if (L"blood" == _wstrName || L"move_effect" == _wstrName)
	{	
		// 1 부터 3까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> dis(1, 3);
		m_wstrCurEffect = _wstrName + L"_" + std::to_wstring(dis(gen));
	}
	else if (L"small_vfx" == _wstrName || L"vfx" == _wstrName)
	{
		// 1 부터 2까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> dis(1, 2);
		m_wstrCurEffect = _wstrName + L"_" + std::to_wstring(dis(gen));
	}

	GetAnimator()->PlayAnimation(m_wstrCurEffect, false);
}

void CEffect::Update()
{
	CAnimation* curAnim = GetAnimator()->GetCurAnimation();
	if (curAnim != nullptr && !m_wstrCurEffect.empty())
	{
		if (m_wstrCurEffect == curAnim->GetName())
		{
			if (curAnim->IsFinished())
			{
				curAnim->Reset();
				GetAnimator()->InitAnimator();
				m_wstrCurEffect = L"";
			}
		}
	}
}

void CEffect::Render(HDC _dc)
{
	Render_Component(_dc);
}

