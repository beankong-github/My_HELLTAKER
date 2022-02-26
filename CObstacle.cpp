#include "pch.h"
#include "CObstacle.h"

#include "CTile.h"

int bSwitch = 1;	

CObstacle::CObstacle(CTile* _pTile)
	: m_eState(EOBSTACLE_STATE::IDLE)
	, m_eType(EOBSTACLE_TYPE::NONE)
	, m_pCurTile(_pTile)
	, m_pNextTile(nullptr)
	, m_eMoveDir(EDIRECTION::NONE)
	, m_fSpeed(500.f)
{
}

CObstacle::~CObstacle()
{
}
void CObstacle::SetCurTile(CTile* _tile)
{
	// ���� Ÿ�Ͽ��� �ڽ��� ���� ����
	if (nullptr != m_pCurTile)
	{
		m_pCurTile->DeleteObstacle(this);
	}

	// �� Ÿ�� ����
	m_pCurTile = _tile;
	m_pCurTile->AddObstacle(this);
}

void CObstacle::Update()
{
}

void CObstacle::Render(HDC _dc)
{
}

