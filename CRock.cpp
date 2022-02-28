#include "pch.h"
#include "CRock.h"

#include "CStageMgr.h"
#include "CStage_Puzzle.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"

#include "CTile.h"
#include "CTileMap.h"

int iPingpong = 1;

CRock::CRock(CTile* _pTile)
	: CObstacle(_pTile)
	, m_fEffectTime(0.1f)
	, m_fAddTime(0.f)
	, m_pCurTex(nullptr)
	, m_vecTextures()
	, m_vOriginalPos{}
{	
	// 현재 스테이지 설정
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	// 타입 저장
	SetType(EOBSTACLE_TYPE::ROCK);

	// 랜덤으로 텍스처 로드
	for (size_t i = 1; i <= 8; i++)
	{
		CTexture* pRockTex = CResMgr::GetInst()->LoadTexture(L"rock_" + std::to_wstring(i), L"texture\\object\\rock\\rock_" + std::to_wstring(i) + L".bmp");

		m_vecTextures.push_back(pRockTex);
	}
	
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(0, 7);

	// 난수 생성
	m_pCurTex = m_vecTextures[dis(gen)];

	// 현재 위치 설정
	m_vOriginalPos.x = GetCurTile()->GetPos().x;
	m_vOriginalPos.y = GetCurTile()->GetPos().y - 10.f;
	SetPos(m_vOriginalPos);
}

CRock::~CRock()
{
}
 
void CRock::Update()
{
	EOBSTACLE_STATE eCurState = GetState();

	switch (eCurState)
	{
	case EOBSTACLE_STATE::MOVE:
		Move();
		break;
	case EOBSTACLE_STATE::KICKED:
		Shake();
		break;
	}
}

void CRock::Render(HDC _dc)
{
	if (nullptr != m_pCurTex)
	{
		TransparentBlt(_dc
			, (int)GetPos().x
			, (int)GetPos().y
			, m_pCurTex->Width()
			, m_pCurTex->Height()
			, m_pCurTex->GetDC()
			, 0, 0
			, m_pCurTex->Width()
			, m_pCurTex->Height()
			, RGB(112, 12, 41)
		);
	}
}

void CRock::TryMove(EDIRECTION _eDir)
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
		SetFlip(false);
		break;

	case EDIRECTION::LEFT:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x - 1, (UINT)curIdx.y));
		SetFlip(true);
		break;
	}

	// 이동할 위치에 타일이 있다면
	if (nullptr != GetNextTile())
	{
		if (ETILE_TYPE::WALL != GetNextTile()->GetType() || ETILE_TYPE::NPC != GetNextTile()->GetType())
		{
			// 타일 위에 오브젝트가 없다면 이동
			if (GetNextTile()->GetObstacles()->empty())
			{
				SetState(EOBSTACLE_STATE::MOVE);
			}

			// 타일 위에 오브젝트가 있는 경우
			else
			{
				if(GetNextTile()->FindObstacle(EOBSTACLE_TYPE::ROCK)
					||GetNextTile()->FindObstacle(EOBSTACLE_TYPE::UNDEAD))
				{
					SetState(EOBSTACLE_STATE::KICKED);
				}
				else
					SetState(EOBSTACLE_STATE::MOVE);
			}
		}
		else
		{
			SetState(EOBSTACLE_STATE::KICKED);
		}
	}
	else
	{
		SetState(EOBSTACLE_STATE::KICKED);
	}
}

void CRock::Move()
{
	// 오브젝트와 다음 타일 사이의 거리
	Vec nextPos = Vec{ GetNextTile()->GetPos().x ,GetNextTile()->GetPos().y - 10.f};

	double dif = sqrt(pow(GetPos().x-nextPos.x,2)+pow(GetPos().y-nextPos.y,2));

	// 다음 타일과 플레이어의 위치가 거의 일치하다면
	if (dif <= 10.f)
	{
		// 플레이어 위치 보정
		m_vOriginalPos = nextPos;
		SetPos(m_vOriginalPos);

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
			SetPos(Vec{ GetPos().x, GetPos().y + (GetSpeed() * DS * -1)});
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

void CRock::Shake()
{
	if (m_fEffectTime >= m_fAddTime)
	{  
		SetPos(m_vOriginalPos + iPingpong * 2.5f);
		m_fAddTime += DS;
		iPingpong *= -1;
	}

	else
	{
		// 원위치
		SetPos(m_vOriginalPos);
		// AddTime 초기화
		m_fAddTime = 0.f;
		// IDLE 상태로 돌아옴
		SetState(EOBSTACLE_STATE::IDLE);
	}
}

