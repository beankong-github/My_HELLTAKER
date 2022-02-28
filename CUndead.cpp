#include "pch.h"
#include "CUndead.h"

#include "CEventMgr.h"
#include "CStageMgr.h"
#include "CStage_Puzzle.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTile.h"
#include "CTileMap.h"

#include "CDynamic_Spike.h"

CUndead::CUndead(CTile* _pTile)
	:CObstacle(_pTile)
{
	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	
	// Ÿ�� ����
	SetType(EOBSTACLE_TYPE::UNDEAD);

	// �ӵ� ����
	SetSpeed(600.f);

	// ���� ��ġ ����
	SetPos(GetCurTile()->GetCenterPos());

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"undead_idle", L"texture\\animation\\undead\\idle\\", 0.07f, 11);
	pAnimator->CreateAnimation(L"undead_move", L"texture\\animation\\undead\\move\\", 0.05f, 7);
	
	// �ִϸ��̼� ����
	CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"undead_idle");
	//pSaveAnim->Save(L"animation\\undead\\");
	pSaveAnim = pAnimator->FindAnimation(L"undead_move");
	pSaveAnim->Save(L"animation\\undead\\");

	// �ִϸ��̼� �ε�
	pAnimator->LoadAnimation(L"animation\\undead\\undead_idle.anim");
	//pAnimator->LoadAnimation(L"animation\\undead\\undead_move.anim");

	// �ִϸ����� ������Ʈ �߰�
	AddComponent(pAnimator);

	// ���� �ִϸ��̼� ����
	pAnimator->PlayAnimation(L"undead_idle");
}

CUndead::~CUndead()
{
}

void CUndead::Update()
{
	EOBSTACLE_STATE eCurState = GetState();

	switch (eCurState)
	{
	case EOBSTACLE_STATE::IDLE:
		GetAnimator()->PlayAnimation(L"undead_idle");
		break;

	case EOBSTACLE_STATE::MOVE:
		GetAnimator()->PlayAnimation(L"undead_move", false);
		Move();
		break;
	
	case EOBSTACLE_STATE::DEAD:
		Dead();
		break;
	}
}

void CUndead::Render(HDC _dc)
{
	Render_Component(_dc);
}

void CUndead::TryMove(EDIRECTION _eDir)
{

	// ���������� Ÿ�ϸ� ��������
	CTileMap* pTileMap = m_pCurStage->GetTileMap();

	// ���� �÷��̾� Ÿ�� �ε��� ��������
	Vec curIdx = GetCurTile()->GetIndex();

	// �̵� ���� ����
	SetDirection(_eDir);

	// �̵��� ��ġ�� Ÿ�� ��������
	switch (_eDir)
	{
	case EDIRECTION::UP:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y - 1));
		break;

	case EDIRECTION::DOWN:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y + 1));
		break;

	case EDIRECTION::RIGHT:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x + 1, (UINT)curIdx.y));
		break;

	case EDIRECTION::LEFT:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x - 1, (UINT)curIdx.y));
		break;
	}

	// �̵��� ��ġ�� Ÿ���� �ִٸ�
	if (nullptr != GetNextTile())
	{
		if (ETILE_TYPE::WALL != GetNextTile()->GetType())
		{
			// Ÿ�� ���� ������Ʈ�� ���ٸ� �̵�
			if (GetNextTile()->GetObstacles()->empty())
			{
				SetState(EOBSTACLE_STATE::MOVE);
			}

			// Ÿ�� ���� ������Ʈ�� �ִ� ���
			else
			{
				if (GetNextTile()->FindObstacle(EOBSTACLE_TYPE::ROCK)
					|| GetNextTile()->FindObstacle(EOBSTACLE_TYPE::STATIC_SPIKE))
				{
					SetState(EOBSTACLE_STATE::DEAD);
				}
				else if (GetNextTile()->FindObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE))
				{
					CDynamic_Spike* nextObject = (CDynamic_Spike*)GetNextTile()->FindObstacle(EOBSTACLE_TYPE::DYNAMC_SPIKE);
					// Dynamic Spike Ȱ�� üũ
					nextObject->Update();

					if (nextObject->IsActive())
					{
						SetState(EOBSTACLE_STATE::DEAD);
					}
					else
					{
						SetState(EOBSTACLE_STATE::MOVE);
					}
				}
			}
		}
		else
		{
			SetState(EOBSTACLE_STATE::DEAD);
		}
	}
}

void CUndead::Move()
{
	// ������Ʈ�� ���� Ÿ�� ������ �Ÿ�
	Vec nextPos = GetNextTile()->GetCenterPos();

	double dif = sqrt(pow(GetPos().x - nextPos.x, 2) + pow(GetPos().y - nextPos.y, 2));

	// ���� Ÿ�ϰ� �÷��̾��� ��ġ�� ���� ��ġ�ϴٸ�
	if (dif <= 10.f)
	{
		// �÷��̾� ��ġ ����
		m_vOriginalPos = nextPos;
		SetPos(m_vOriginalPos);

		// �ִϸ��̼� �ʱ�ȭ
		GetAnimator()->GetCurAnimation()->Reset();

		// �̵� ���� �ʱ�ȭ
		SetDirection(EDIRECTION::NONE);

		// ������ Ÿ���� ���� Ÿ�Ϸ� ����
		SetCurTile(GetNextTile());

		// ������ Ÿ�� �ʱ�ȭ
		SetNextTile(nullptr);

		// ���� ���� Idle
		SetState(EOBSTACLE_STATE::IDLE);
	}
	else
	{
		switch (GetDirection())
		{
			break;
		case EDIRECTION::UP:
			SetPos(Vec{ GetPos().x, GetPos().y + (GetSpeed() * DS * -1) });
			break;
		case EDIRECTION::DOWN:
			SetPos(Vec{ GetPos().x, GetPos().y + (GetSpeed() * DS * 1) });
			break;
		case EDIRECTION::RIGHT:
			SetPos(Vec{ GetPos().x + (GetSpeed() * DS * 1) , GetPos().y });
			break;
		case EDIRECTION::LEFT:
			SetPos(Vec{ GetPos().x + (GetSpeed() * DS * -1) , GetPos().y });
			break;
		}
	}
}

void CUndead::Dead()
{
	// ���� ����Ʈ ���
	

	// ������Ʈ ����
	DeleteObject(this);
}
 