#include "pch.h"
#include "CHero.h"

#include "CKeyMgr.h"
#include  "CStageMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CStage_Puzzle.h"
#include "CTile.h"
#include "CTileMap.h"

bool bCanMove = false;

CHero::CHero()
	: m_fSpeed(300.f)
	, m_eCurState(EPLAYER_STATE::IDLE)
	, m_pCurTile(nullptr)
{
	// �̸� ����
	SetName(L"Hero");

	// �ִϸ��̼� ����
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"idle", L"texture\\animation\\hero\\idle\\", 0.05f, 12);
	//pAnimator->CreateAnimation(L"move", L"texture\\animation\\hero\\move\\", 0.05f, 6);
	//pAnimator->CreateAnimation(L"success", L"texture\\animation\\hero\\success\\", 0.05f, 19);
	//pAnimator->CreateAnimation(L"kick", L"texture\\animation\\hero\\kick\\", 0.05f, 13);
	//pAnimator->CreateAnimation(L"dead", L"texture\\animation\\hero\\dead\\", 0.05f, 18);

	// �ִϸ��̼� ����
	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"idle");
	//pSaveAnim->Save(L"animation\\hero\\");	
	//
	//pSaveAnim = pAnimator->FindAnimation(L"move");
	//pSaveAnim->Save(L"animation\\hero\\");	
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
	pAnimator->LoadAnimation(L"animation\\hero\\move.anim");
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
	if (IS_KEY_TAP(KEY::A)) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		bCanMove = TryMove(EDIRECTION::LEFT);
	}
	if (IS_KEY_TAP(KEY::D))
	{
		bCanMove = TryMove(EDIRECTION::RIGHT);
	}
	if (IS_KEY_TAP(KEY::W))
	{
		bCanMove = TryMove(EDIRECTION::UP);
	}
	if (IS_KEY_TAP(KEY::S))
	{
		bCanMove = TryMove(EDIRECTION::DOWN);
	}

	if (bCanMove)
	{
		Move();
	}
}

void CHero::Render(HDC _dc)
{
	Render_Component(_dc);
}

bool CHero::TryMove(EDIRECTION _eDir)
{
	// ���� �÷��̾��� ���°� idle�̰� ���� �ƴ϶�� �̵�

	// ���� ���� üũ
	if (EPLAYER_STATE::IDLE != m_eCurState)
		return false;

	// ���� ���� �������� ��������
	CStage_Puzzle* curStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	if (nullptr == curStage)
		assert(nullptr);

	// ���������� Ÿ�ϸ� ��������
	CTileMap* pTileMap = curStage->GetTileMap();

	// ���� �÷��̾� Ÿ�� �ε��� ��������
	Vec curIdx = m_pCurTile->GetIndex();
	
	switch (_eDir)
	{
	case EDIRECTION::UP:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y-1);
		if (nullptr != m_pNextTile)
		{
			if (ETILE_TYPE::WALL != m_pNextTile->GetType())
			{
				return true;
			}
		}
		break;

	case EDIRECTION::DOWN:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x, (UINT)curIdx.y + 1);
		if (nullptr != m_pNextTile)
		{
			if (ETILE_TYPE::WALL != m_pNextTile->GetType())
			{
				return true;
			}
		}
		break;

	case EDIRECTION::RIGHT:
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x+1, (UINT)curIdx.y);
		if (nullptr != m_pNextTile)
		{
			if (ETILE_TYPE::WALL != m_pNextTile->GetType())
			{
				return true;
			}
		}
		break;

	case EDIRECTION::LEFT:		
		m_pNextTile = pTileMap->FindTile((UINT)curIdx.x -1, (UINT)curIdx.y);
		if (nullptr != m_pNextTile)
		{
			if (ETILE_TYPE::WALL != m_pNextTile->GetType())
			{
				return true;
			}
		}
		break;
	}
	
	return false;
	 
}

void CHero::Move()
{
	//if(GetPos()	 - m_pNextTile->GetCenterPos())
	//m_eCurState = EPLAYER_STATE::MOVE;
	//SetPos(m_pNextTile->GetCenterPos() * m_fSpeed * DS);
	//GetAnimator()->PlayAnimation(L"move");
	//
}

