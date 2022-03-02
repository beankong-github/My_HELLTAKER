#include "pch.h"
#include "CEffect.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect::CEffect() 
	: m_wstrCurEffect()
{
	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	
	// �� ȿ��
	pAnimator->CreateAnimation(L"blood_1", L"texture\\animation\\effect\\blood\\blood_1\\", 0.04f, 6);
	pAnimator->CreateAnimation(L"blood_2", L"texture\\animation\\effect\\blood\\blood_2\\", 0.04f, 6);
	pAnimator->CreateAnimation(L"blood_3", L"texture\\animation\\effect\\blood\\blood_3\\", 0.04f, 6);

	// ������ ȿ��
	pAnimator->CreateAnimation(L"item_effect", L"texture\\animation\\effect\\item_effect\\", 0.04f, 9);

	// �̵� ȿ�� 
	pAnimator->CreateAnimation(L"move_effect_1", L"texture\\animation\\effect\\move_effect\\1\\", 0.06f, 3);
	pAnimator->CreateAnimation(L"move_effect_2", L"texture\\animation\\effect\\move_effect\\2\\", 0.06f, 3);
	pAnimator->CreateAnimation(L"move_effect_3", L"texture\\animation\\effect\\move_effect\\3\\", 0.06f, 3);

	// ���� ���� ȿ��
	pAnimator->CreateAnimation(L"small_vfx_1", L"texture\\animation\\effect\\small_vfx\\1\\", 0.05f, 4);
	pAnimator->CreateAnimation(L"small_vfx_2", L"texture\\animation\\effect\\small_vfx\\2\\", 0.05f, 4);

	// ū ���� ȿ��
	pAnimator->CreateAnimation(L"vfx_1", L"texture\\animation\\effect\\vfx\\1\\", 0.05f, 5);
	pAnimator->CreateAnimation(L"vfx_2", L"texture\\animation\\effect\\vfx\\2\\", 0.05f, 5);

	// ���� ȿ��
	pAnimator->CreateAnimation(L"success_effect", L"texture\\animation\\effect\\success_effect\\", 0.06f, 15);

	// �ִϸ��̼� ����
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

	

	// �ִϸ��̼� �ε�
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_2.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\blood_3.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\item_effect.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_2.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\move_effect_3.anim");

	//pAnimator->LoadAnimation(L"animation\\effect\\small_vfx_1.anim");
	//pAnimator->LoadAnimation(L"animation\\effect\\small_vfx_2.anim");

	// �ִϸ��̼� ������Ʈ �߰�
	AddComponent(pAnimator);
}

CEffect::~CEffect()
{
}

void CEffect::PlayEffect(wstring _wstrName, Vec _vPos)
{
	SetPos(_vPos);

	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;
	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());;

	if (L"blood" == _wstrName || L"move_effect" == _wstrName)
	{	
		// 1 ���� 3���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
		std::uniform_int_distribution<int> dis(1, 3);
		m_wstrCurEffect = _wstrName + L"_" + std::to_wstring(dis(gen));
	}
	else if (L"small_vfx" == _wstrName || L"vfx" == _wstrName)
	{
		// 1 ���� 2���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
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

