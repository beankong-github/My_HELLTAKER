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
	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	// Ÿ�� ����
	SetType(EOBSTACLE_TYPE::ROCK);

	// �������� �ؽ�ó �ε�
	for (size_t i = 1; i <= 8; i++)
	{
		CTexture* pRockTex = CResMgr::GetInst()->LoadTexture(L"rock_" + std::to_wstring(i), L"texture\\object\\rock\\rock_" + std::to_wstring(i) + L".bmp");

		m_vecTextures.push_back(pRockTex);
	}
	
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> dis(0, 7);

	// ���� ����
	m_pCurTex = m_vecTextures[dis(gen)];

	// ���� ��ġ ����
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
		SetFlip(false);
		break;

	case EDIRECTION::LEFT:
		SetNextTile(pTileMap->FindTile((UINT)curIdx.x - 1, (UINT)curIdx.y));
		SetFlip(true);
		break;
	}

	// �̵��� ��ġ�� Ÿ���� �ִٸ�
	if (nullptr != GetNextTile())
	{
		if (ETILE_TYPE::WALL != GetNextTile()->GetType() || ETILE_TYPE::NPC != GetNextTile()->GetType())
		{
			// Ÿ�� ���� ������Ʈ�� ���ٸ� �̵�
			if (GetNextTile()->GetObstacles()->empty())
			{
				SetState(EOBSTACLE_STATE::MOVE);
			}

			// Ÿ�� ���� ������Ʈ�� �ִ� ���
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
	// ������Ʈ�� ���� Ÿ�� ������ �Ÿ�
	Vec nextPos = Vec{ GetNextTile()->GetPos().x ,GetNextTile()->GetPos().y - 10.f};

	double dif = sqrt(pow(GetPos().x-nextPos.x,2)+pow(GetPos().y-nextPos.y,2));

	// ���� Ÿ�ϰ� �÷��̾��� ��ġ�� ���� ��ġ�ϴٸ�
	if (dif <= 10.f)
	{
		// �÷��̾� ��ġ ����
		m_vOriginalPos = nextPos;
		SetPos(m_vOriginalPos);

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
		// ����ġ
		SetPos(m_vOriginalPos);
		// AddTime �ʱ�ȭ
		m_fAddTime = 0.f;
		// IDLE ���·� ���ƿ�
		SetState(EOBSTACLE_STATE::IDLE);
	}
}

