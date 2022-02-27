#include "pch.h"
#include "CHero.h"

#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CStage_Puzzle.h"
#include "CTile.h"
#include "CTileMap.h"

#include "CRock.h"
#include "CUndead.h"
#include "CStatic_Spike.h"

CHero::CHero()
	: m_fSpeed(600.f)
	, m_eState(EPLAYER_STATE::IDLE)
	, m_pCurTile(nullptr)
	, m_eMovDir(EDIRECTION::NONE)
{
	// 이름 설정
	SetName(L"Hero");

	// 현재 스테이지 설정
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	// 애니메이션 생성
	CAnimator* pAnimator = new CAnimator;
	//pAnimator->CreateAnimation(L"idle", L"texture\\animation\\hero\\idle\\", 0.05f, 12);
	//pAnimator->CreateAnimation(L"move", L"texture\\animation\\hero\\move\\", 0.07f, 6);
	//pAnimator->CreateAnimation(L"success", L"texture\\animation\\hero\\success\\", 0.11f, 19);
	//pAnimator->CreateAnimation(L"kick", L"texture\\animation\\hero\\kick\\", 0.03f, 10);
	//pAnimator->CreateAnimation(L"dead", L"texture\\animation\\hero\\dead\\", 0.05f, 18);

	// 애니메이션 저장
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

	// 애니메이션 로드
	pAnimator->LoadAnimation(L"animation\\hero\\idle.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\move.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\success.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\kick.anim");
	pAnimator->LoadAnimation(L"animation\\hero\\dead.anim");

	AddComponent(pAnimator);

	// 시작 애니메이션 설정
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
	CAnimation* pCurAnim = GetAnimator()->GetCurAnimation();
	// 상태에 따른 동작
	switch (m_eState)
	{
	case EPLAYER_STATE::IDLE:
		// Animation Play
		GetAnimator()->PlayAnimation(L"idle");
		break;

	case EPLAYER_STATE::MOVE:
	case EPLAYER_STATE::DAMAGED:
		// player move event 추가
		tEventInfo eventInfo;
		eventInfo.eType = EEVENT_TYPE::PLAYER_MOVE;
		eventInfo.lParam = (DWORD)m_eMovDir;
		CEventMgr::GetInst()->AddEvent(eventInfo);
		break;

	case EPLAYER_STATE::KICK:
		GetAnimator()->PlayAnimation(L"kick", false);
		if (pCurAnim->IsFinished())
		{
			// 애니메이션 리셋
			GetAnimator()->GetCurAnimation()->Reset();
			// IDLE로 전환
			SetState(EPLAYER_STATE::IDLE);
			GetAnimator()->PlayAnimation(L"idle");
			// 이동 방향 초기화
			m_eMovDir = EDIRECTION::NONE;
			// 다음 타일 초기화
			m_pNextTile = nullptr;
		}
		break;

	case EPLAYER_STATE::SUCCESS:
		GetAnimator()->PlayAnimation(L"success", false);
		if (pCurAnim->IsFinished())
		{
			// 다음 씬으로 이동
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
	

	// 현재 타일이 GOAL 타일이라면 성공
	if (ETILE_TYPE::GOAL == m_pCurTile->GetType())
	{
		m_eState = EPLAYER_STATE::SUCCESS;
	}

	Render_Component(_dc);
}

void CHero::KeyCheck()
{
	// Idle 상태가 아니라면 키 입력은 받지 않는다.
	if (EPLAYER_STATE::IDLE != m_eState)
		return;

	if (IS_KEY_TAP(KEY::A)) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
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
}

void CHero::CountDown()
{	
	UINT minus = 0;

	switch (m_eState)
	{
	case EPLAYER_STATE::MOVE:
	case EPLAYER_STATE::KICK:
		minus = 1;
		break;
	case EPLAYER_STATE::DAMAGED:
		minus = 2;
		break;
	}

	// 남은 이동 횟수 설정 
	m_pCurStage->SetCurMoveCount(m_pCurStage->GetCurMoveCount() - minus);
	

	// 남은 이동 횟수가 0이라면 Dead
	if (0 == m_pCurStage->GetCurMoveCount())
	{
		if (ETILE_TYPE::GOAL == m_pCurTile->GetType())
			return;

		SetPos(GetPos() + Vec{ 0, -300 });
		m_pCurStage->PlayerDead();
		SetState(EPLAYER_STATE::DEAD);
	}
}

void CHero::TryMove()
{
	/* 이동할 타일이 벽이 아니라면 이동 */

	// 스테이지의 타일맵 가져오기
	CTileMap* pTileMap = m_pCurStage->GetTileMap();

	// 현재 플레이어 타일 인덱스 가져오기
	Vec curIdx = m_pCurTile->GetIndex();

	// 이동할 위치의 타일 가져오기
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

	// 이동할 위치에 타일이 있다면
	if (nullptr != m_pNextTile)
	{
		// 다음에 이동할 타일이 벽이 아닐 때
		if(ETILE_TYPE::WALL != m_pNextTile->GetType())
		{
			list<CObstacle*>* pObstacleList = m_pNextTile->GetObstacles();
			
			// 다음 타일에 Object가 없으면 이동
			if (pObstacleList->empty())
			{
				m_eState = EPLAYER_STATE::MOVE;
			}
			
			// Object가 있으면 Object에 따라 행동
			else
			{ 
				// Rock -> Kick
				CRock* pRock = (CRock*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::ROCK);
				if (nullptr != pRock)
				{
					// 플레이어 상태 전환
					m_eState = EPLAYER_STATE::KICK; 
					if (EPLAYER_STATE::DEAD == m_eState)
						return;
					// 오브젝트 움직임
					pRock->TryMove(m_eMovDir);
				}

				// Undead 일 때
				CUndead* pUndead = (CUndead*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::UNDEAD);
				if (nullptr != pUndead)
				{
					// 플레이어 상태 전환
					m_eState = EPLAYER_STATE::KICK;
					if (EPLAYER_STATE::DEAD == m_eState)
						return;
					// 오브젝트 움직임
					pUndead->TryMove(m_eMovDir);
				}

				// Static Spike 일 때
				CStatic_Spike* pSSpike = (CStatic_Spike*)m_pNextTile->FindObstacle(EOBSTACLE_TYPE::STATIC_SPIKE);
				if (nullptr != pSSpike)
				{
					// 플레이어 상태 전환
					m_eState = EPLAYER_STATE::DAMAGED;
					if (EPLAYER_STATE::DEAD == m_eState)
						return;
			
				}
			}

			// 이동 횟수 감소
			CountDown();
		}
	}
}

void CHero::Move(EDIRECTION _eDir)
{
	//if (nullptr == m_pNextTile || EDIRECTION::NONE == _eDir)
	//	return;

	CAnimation* pCurAnim = GetAnimator( )->GetCurAnimation();

	// 플레이어와 다음 타일 사이의 거리
	double dif = sqrt(pow(GetPos().x - m_pNextTile->GetCenterPos().x, 2)
		+ pow(GetPos().y - m_pNextTile->GetCenterPos().y, 2));

	// 다음 타일과 플레이어의 위치가 거의 일치하다면
	if (dif <= 15.f)
	{
		// 플레이어 위치 보정
		SetPos(m_pNextTile->GetCenterPos());
		// Move Animation 초기화
		pCurAnim->Reset();
		// 현재 상태 Idle
		m_eState = EPLAYER_STATE::IDLE;
		// 이동 방향 초기화
		m_eMovDir = EDIRECTION::NONE;
		// 목적지 타일을 현재 타일로 설정
		SetCurTile(m_pNextTile);
		// 목적지 타일 초기화
		m_pNextTile = nullptr;
	}
	else
	{
		if( L"move" != pCurAnim->GetName())
			GetAnimator()->PlayAnimation(L"move", false);
 
		switch (m_eMovDir)
		{
			break;
		case EDIRECTION::UP:
			SetPos(Vec{ GetPos().x, GetPos().y + (m_fSpeed * DS * -1)});
			break;
		case EDIRECTION::DOWN:
			SetPos(Vec{ GetPos().x, GetPos().y + (m_fSpeed * DS * 1) });
			break;
		case EDIRECTION::RIGHT:
			SetPos(Vec{ GetPos().x + (m_fSpeed * DS * 1) , GetPos().y});
			break;
		case EDIRECTION::LEFT:
			SetPos(Vec{ GetPos().x + (m_fSpeed * DS * -1) , GetPos().y });
			break;
		}
	}
}


