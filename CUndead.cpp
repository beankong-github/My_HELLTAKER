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
	// 현재 스테이지 저장
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	
	// 타입 저장
	SetType(EOBSTACLE_TYPE::UNDEAD);

	// 속도 설정
	SetSpeed(600.f);

	// 현재 위치 설정
	SetPos(GetCurTile()->GetCenterPos());

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"undead_idle", L"texture\\animation\\undead\\idle\\", 0.07f, 11);
	pAnimator->CreateAnimation(L"undead_move", L"texture\\animation\\undead\\move\\", 0.05f, 7);
	
	// 애니메이션 저장
	CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"undead_idle");
	//pSaveAnim->Save(L"animation\\undead\\");
	pSaveAnim = pAnimator->FindAnimation(L"undead_move");
	pSaveAnim->Save(L"animation\\undead\\");

	// 애니메이션 로드
	pAnimator->LoadAnimation(L"animation\\undead\\undead_idle.anim");
	//pAnimator->LoadAnimation(L"animation\\undead\\undead_move.anim");

	// 애니메이터 컴포넌트 추가
	AddComponent(pAnimator);

	// 시작 애니메이션 설정
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

	// 스테이지의 타일맵 가져오기
	CTileMap* pTileMap = m_pCurStage->GetTileMap();

	// 현재 플레이어 타일 인덱스 가져오기
	Vec curIdx = GetCurTile()->GetIndex();

	// 이동 방향 설정
	SetDirection(_eDir);

	// 이동할 위치의 타일 가져오기
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

	// 이동할 위치에 타일이 있다면
	if (nullptr != GetNextTile())
	{
		if (ETILE_TYPE::WALL != GetNextTile()->GetType())
		{
			// 타일 위에 오브젝트가 없다면 이동
			if (GetNextTile()->GetObstacles()->empty())
			{
				SetState(EOBSTACLE_STATE::MOVE);
			}

			// 타일 위에 오브젝트가 있는 경우
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
					// Dynamic Spike 활성 체크
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
	// 오브젝트와 다음 타일 사이의 거리
	Vec nextPos = GetNextTile()->GetCenterPos();

	double dif = sqrt(pow(GetPos().x - nextPos.x, 2) + pow(GetPos().y - nextPos.y, 2));

	// 다음 타일과 플레이어의 위치가 거의 일치하다면
	if (dif <= 10.f)
	{
		// 플레이어 위치 보정
		m_vOriginalPos = nextPos;
		SetPos(m_vOriginalPos);

		// 애니메이션 초기화
		GetAnimator()->GetCurAnimation()->Reset();

		// 이동 방향 초기화
		SetDirection(EDIRECTION::NONE);

		// 목적지 타일을 현재 타일로 설정
		SetCurTile(GetNextTile());

		// 목적지 타일 초기화
		SetNextTile(nullptr);

		// 현재 상태 Idle
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
	// 삭제 이펙트 재생
	

	// 오브젝트 삭제
	DeleteObject(this);
}
 