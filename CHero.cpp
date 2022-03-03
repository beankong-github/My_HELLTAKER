#include "pch.h"
#include "CHero.h"

#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CEffect.h"

#include "CStage_Puzzle.h"
#include "CTile.h"
#include "CTileMap.h"

#include "CRock.h"
#include "CUndead.h"
#include "CStatic_Spike.h"
#include "CDynamic_Spike.h"
#include "CLockBox.h"
#include "CKey.h"

CHero::CHero()
	: m_fSpeed(666.f)
	, m_eState(EPLAYER_STATE::IDLE)
	, m_pCurTile(nullptr)
	, m_eMovDir(EDIRECTION::NONE)
{
	// �̸� ����
	SetName(L"Hero");

	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	// ���� ������ ���� �ؽ�ó ����
	m_pRedTex = CResMgr::GetInst()->CreateTexture(L"red_blender", 100, 100);
	for (UINT i = 0; i < 100; i++)
	{
		for (UINT j = 0; j < 100; j++)
		{
			// veil �ؽ�ó�� ��� �ȼ��� ���������� ĥ�Ѵ�.
			SetPixel(m_pRedTex->GetDC(), j, i, RGB(255, 0, 0));
		}
	}

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"idle", L"texture\\animation\\hero\\idle\\", 0.05f, 12);
	pAnimator->CreateAnimation(L"move", L"texture\\animation\\hero\\move\\", 0.01f, 6);
	//pAnimator->CreateAnimation(L"success", L"texture\\animation\\hero\\success\\", 0.11f, 19);
	//pAnimator->CreateAnimation(L"kick", L"texture\\animation\\hero\\kick\\", 0.02f, 7);
	//pAnimator->CreateAnimation(L"dead", L"texture\\animation\\hero\\dead\\", 0.05f, 18);

	// �ִϸ��̼� ����
	CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"idle");
	//pSaveAnim->Save(L"animation\\hero\\");	
	//
	pSaveAnim = pAnimator->FindAnimation(L"move");
	pSaveAnim->Save(L"animation\\hero\\");	
	//
	//pSaveAnim = pAnimator->FindAnimation(L"success");
	//pSaveAnim->Save(L"animation\\hero\\");	
	//
	//pSaveAnim = pAnimator->FindAnimation(L"kick");
	//pSaveAnim->Save(L"animation\\hero\\");	
	//
	//pSaveAnim = pAnimator->FindAnimation(L"dead");
	//pSaveAnim->Save(L"animation\\hero\\");

	// �ִϸ��̼� �ε�
	pAnimator->LoadAnimation(L"animation\\hero\\idle.anim");
	//pAnimator->LoadAnimation(L"animation\\hero\\move.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\success.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\kick.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\dead.anim");

	AddComponent(pAnimator);

	// ���� �ִϸ��̼� ����
	pAnimator->PlayAnimation(L"idle");
}

CHero::~CHero()
{ 
}

void CHero::Update()
{
	KeyCheck();
}

void CHero::Render(HDC _dc)
{
	// ���¿� ���� ����
	switch (m_eState)
	{
	case EPLAYER_STATE::IDLE:
		// Animation Play
		GetAnimator()->PlayAnimation(L"idle");
		break;

	case EPLAYER_STATE::MOVE:
		Move();
		break;

	case EPLAYER_STATE::KICK:
		Kick();
		break;

	case EPLAYER_STATE::SUCCESS:
		StageClear();
		break;

	case EPLAYER_STATE::DEAD:
		GetAnimator()->PlayAnimation(L"dead", false);
		if (GetAnimator()->GetCurAnimation()->IsFinished())
		{
			tEventInfo eventInfo;
			eventInfo.eType = EEVENT_TYPE::STAGE_CHANGE;
			eventInfo.lParam = (DWORD)ESTAGE_TYPE::PUZZLE;
			eventInfo.wParam = (DWORD)m_pCurStage->GetChapter();
			CEventMgr::GetInst()->AddEvent(eventInfo);
		}
		break;
	}


	// ���� Ÿ���� GOAL Ÿ���̶�� ����
	if (ETILE_TYPE::GOAL == m_pCurTile->GetType())
	{
		m_eState = EPLAYER_STATE::SUCCESS;
	}

	Render_Component(_dc);
}

void CHero::KeyCheck()
{
	// Idle ���°� �ƴ϶�� Ű �Է��� ���� �ʴ´�.
	if (EPLAYER_STATE::IDLE != m_eState)
		return;

	if (IS_KEY_TAP(KEY::A)) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		m_eMovDir = EDIRECTION::LEFT;
		TryMove();
	}
	else if (IS_KEY_TAP(KEY::D))
	{
		m_eMovDir = EDIRECTION::RIGHT;
		TryMove();
	}
	else if (IS_KEY_TAP(KEY::W))
	{
		m_eMovDir = EDIRECTION::UP;
		TryMove();
	}
	else if (IS_KEY_TAP(KEY::S))
	{
		m_eMovDir = EDIRECTION::DOWN;
		TryMove();
	}
	else if (IS_KEY_TAP(KEY::R))
	{
		tEventInfo eventInfo;
		eventInfo.eType = EEVENT_TYPE::STAGE_CHANGE;
		eventInfo.lParam = (DWORD)ESTAGE_TYPE::PUZZLE;
		eventInfo.wParam = (DWORD)m_pCurStage->GetChapter();
		CEventMgr::GetInst()->AddEvent(eventInfo);
	}
}

void CHero::CountDown(int _num)
{
	// ���� �̵� Ƚ�� ���� 
	m_pCurStage->SetCurMoveCount(m_pCurStage->GetCurMoveCount() - _num);
}

void CHero::TryMove()
{
	/* �̵��� Ÿ���� ���� �ƴ϶�� �̵� */

	// ���� �̵� Ƚ���� 0�̶�� Dead
	if (0 >= m_pCurStage->GetCurMoveCount())
	{
		if (ETILE_TYPE::GOAL == m_pCurTile->GetType())
			return;

		SetState(EPLAYER_STATE::DEAD);
		SetPos(GetPos() + Vec{ 0, -300 });
		m_pCurStage->PlayerDead();
		return;
	}

	// ���������� Ÿ�ϸ� ��������
	CTileMap* pTileMap = m_pCurStage->GetTileMap();

	// ���� �÷��̾� Ÿ�� �ε��� ��������
	Vec curIdx = m_pCurTile->GetIndex();

	// �̵��� ��ġ�� Ÿ�� ��������
	switch (m_eMovDir)
	{
	case EDIRECTION::UP:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y - 1);
		break;

	case EDIRECTION::DOWN:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y + 1);
		break;

	case EDIRECTION::RIGHT:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x + 1, (UINT)curIdx.y);
		SetFlip(false);
		break;

	case EDIRECTION::LEFT:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x - 1, (UINT)curIdx.y);
		SetFlip(true);
		break;
	}

	// �̵��� ��ġ�� Ÿ���� �ִٸ�
	if (nullptr != m_pNextTile)
	{
		// ������ �̵��� Ÿ���� ���� �ƴ� ��
		if(ETILE_TYPE::WALL != m_pNextTile->GetType())
		{
			list<CObstacle*>* pObstacleList = m_pNextTile->GetObstacles();

			// ���� Ÿ�Ͽ� Object�� ������ �̵�
			if (pObstacleList->empty())
			{
				m_eState = EPLAYER_STATE::MOVE;					
				return;
			}
			
			// Object�� ������ Object�� ���� �ൿ
			else
			{
				// Rock �� ��
				CRock* pRock = (CRock*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::ROCK);
				if (nullptr != pRock)
				{
					// �÷��̾� ���� ��ȯ
					m_eState = EPLAYER_STATE::KICK;
					// ������Ʈ ������
					pRock->TryMove(m_eMovDir);
					return;
				}

				// LockBox �� ��
				CLockBox* pBox = (CLockBox*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::LOCKBOX);
				if (nullptr != pBox)
				{
					if (m_bKey)
					{
						// ����Ʈ
						m_pCurStage->GetEffect()->PlayEffect(L"item_effect", m_pNextTile->GetCenterPos());
						// ���� ����
						DeleteObject(pBox);
						// �÷��̾� ���� ��ȯ
						m_eState = EPLAYER_STATE::MOVE;
					}
					else
					{
						// �÷��̾� ���� ��ȯ
						m_eState = EPLAYER_STATE::KICK;
						// ������Ʈ ������
						pBox->SetState(EOBSTACLE_STATE::KICKED);
						return;
					}
				}

				// Key�� ��
				CKey* pKey = (CKey*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::KEY);
				// ���� Ÿ���� Ű�� �ִ� Ÿ���̸�
				if (nullptr != pKey)
				{
					// ����Ʈ
					m_pCurStage->GetEffect()->PlayEffect(L"item_effect", m_pNextTile->GetCenterPos());
					// Ű ����
					DeleteObject(pKey);

					// �÷��̾� �̵�
					m_eState = EPLAYER_STATE::MOVE;
					// Ű ȹ�� ó��
					m_bKey = true;
					return;
				}

				// Undead �� ��
				CUndead* pUndead = (CUndead*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::UNDEAD);
				if (nullptr != pUndead)
				{
					// �÷��̾� ���� ��ȯ
					m_eState = EPLAYER_STATE::KICK;
					// ������Ʈ ������
					pUndead->TryMove(m_eMovDir);
					return;
				}

				// Static Spike �� ��
				CStatic_Spike* pSSpike = (CStatic_Spike*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::STATIC_SPIKE);
				if (nullptr != pSSpike)
				{
					// �÷��̾� ���� ��ȯ
					m_eState = EPLAYER_STATE::MOVE;
					return;
				}

				// Dynamic Spike �� ��
				CDynamic_Spike* pDSpike = (CDynamic_Spike*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE);
				if (nullptr != pDSpike)
				{
					// �÷��̾� ���� ��ȯ
						m_eState = EPLAYER_STATE::MOVE;
						return;
				}
			}
		}
	}
}

void CHero::Move()
{
	CAnimation* pCurAnim = GetAnimator( )->GetCurAnimation();
	if (L"move" != pCurAnim->GetName())
	{
		// �ִϸ��̼� ���
		GetAnimator()->PlayAnimation(L"move", false);

		// ����Ʈ
		m_pCurStage->GetEffect()->PlayEffect(L"move_effect", m_pCurTile->GetCenterPos());

		// ���� �ٴڿ� ���ð� ������ ������ ������ ī��Ʈ
		if (m_pNextTile->IsContainObstacle(EOBSTACLE_TYPE::STATIC_SPIKE))
		{
			GetDamaged(2, m_pNextTile->GetCenterPos());
		}
		else if (m_pNextTile->IsContainObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE))
		{
			CDynamic_Spike* dspike = (CDynamic_Spike*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE);
			if (!dspike->IsActive())
			{
				GetDamaged(2, m_pNextTile->GetCenterPos());
			}
			else
			{
				CountDown();
			}
		}
		else
			CountDown();
	}
	else
	{
		if (pCurAnim->IsFinished())
		{

			// �÷��̾� ��ġ ����
			SetPos(m_pNextTile->GetCenterPos());
			// Move Animation �ʱ�ȭ
			pCurAnim->Reset();
			// ���� ���� Idle
			m_eState = EPLAYER_STATE::IDLE;
			// �̵� ���� �ʱ�ȭ
			m_eMovDir = EDIRECTION::NONE;
			// ������ Ÿ���� ���� Ÿ�Ϸ� ����
			SetCurTile(m_pNextTile);
			// ������ Ÿ�� �ʱ�ȭ
			m_pNextTile = nullptr;
		}
		else
		{
			// �÷��̾� �̵�
			switch (m_eMovDir)
			{
				break;
			case EDIRECTION::UP:
				SetPos(Vec{ GetPos().x, GetPos().y + (m_fSpeed * DS * -1) });
				break;
			case EDIRECTION::DOWN:
				SetPos(Vec{ GetPos().x, GetPos().y + (m_fSpeed * DS * 1) });
				break;
			case EDIRECTION::RIGHT:
				SetPos(Vec{ GetPos().x + (m_fSpeed * DS * 1) , GetPos().y });
				break;
			case EDIRECTION::LEFT:
				SetPos(Vec{ GetPos().x + (m_fSpeed * DS * -1) , GetPos().y });
				break;
			}
		}
	}
}

void CHero::Kick()
{
	CAnimation* pCurAnim = GetAnimator()->GetCurAnimation();

	if (L"kick" != pCurAnim->GetName())
	{
		// �ִϸ��̼� ���
		GetAnimator()->PlayAnimation(L"kick", false);

		// ���� �ٴڿ� ���ð� ������ ������
		if (m_pCurTile->IsContainObstacle(EOBSTACLE_TYPE::STATIC_SPIKE))
		{
			GetDamaged(2, m_pCurTile->GetCenterPos());
		}
		else if (m_pCurTile->IsContainObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE))
		{
			CDynamic_Spike* dspike = (CDynamic_Spike*)m_pCurTile->FindObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE);
			if (!dspike->IsActive())
				GetDamaged(2, m_pCurTile->GetCenterPos());		
			else
				CountDown();
		}
		else
			CountDown();
	}
	else if (pCurAnim->IsFinished())
	{

		// �ִϸ��̼� ����
		GetAnimator()->GetCurAnimation()->Reset();
		// IDLE�� ��ȯ
		SetState(EPLAYER_STATE::IDLE);
		GetAnimator()->PlayAnimation(L"idle");
		// �̵� ���� �ʱ�ȭ
		m_eMovDir = EDIRECTION::NONE;
		// ���� Ÿ�� �ʱ�ȭ
		m_pNextTile = nullptr;
	}
}

void CHero::StageClear()
{
	CAnimation* pCurAnim = GetAnimator()->GetCurAnimation();

	if (L"success" != pCurAnim->GetName())
	{
		GetAnimator()->PlayAnimation(L"success", false);

		// ����Ʈ ���
		CTileMap* pTileMap = m_pCurStage->GetTileMap();
		map<Vec, CTile*>::iterator iter = pTileMap->GetTileMap()->begin();
		for (; iter != pTileMap->GetTileMap()->end(); ++iter)
		{
			if (ETILE_TYPE::NPC == iter->second->GetType())
			{
				m_pCurStage->GetEffect()->PlayEffect(L"success_effect", iter->second->GetCenterPos());
			}
		}
	}
	else if (pCurAnim->IsFinished())
	{
		// ���� ������ �̵� �̺�Ʈ �߰�
		tEventInfo eventInfo;
		eventInfo.eType = EEVENT_TYPE::STAGE_CHANGE;
		eventInfo.lParam = (DWORD)ESTAGE_TYPE::PUZZLE;

		ECHAPTER eNextStage = (ECHAPTER)((UINT)m_pCurStage->GetChapter() + 1);
		if (ECHAPTER::END == eNextStage)
		{
			eNextStage = ECHAPTER::CHAP_1;
		}
		eventInfo.wParam = (DWORD)eNextStage;

		CEventMgr::GetInst()->AddEvent(eventInfo);
	}
}

void CHero::GetDamaged(int damage, Vec pos)
{
	// ī��Ʈ �ٿ�
	CountDown(damage);

	// ������ ����Ʈ
	m_pCurStage->GetEffect()->PlayEffect(L"blood", pos);

	// ī�޶� ����
	CCamera::GetInst()->Vibration(1.5, 0.3f, 200, EDIRECTION::HORIZIONTAL);
}


