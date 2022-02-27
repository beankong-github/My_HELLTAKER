#include "pch.h"
#include "CStatic_Spike.h"

#include "CStageMgr.h"
#include "CStage_Puzzle.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTile.h"
#include "CTileMap.h"

CStatic_Spike::CStatic_Spike(CTile* _pTile)
	:CObstacle(_pTile)
{
	// ���� �������� ����
	m_pCurStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());

	// Ÿ�� ����
	SetType(EOBSTACLE_TYPE::STATIC_SPIKE);

	// �ؽ�ó �ε�
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"spike_3", L"texture\\object\\spike\\spike_3.bmp");

	// ���� ��ġ ����
	SetPos(_pTile->GetPos());
}

CStatic_Spike::~CStatic_Spike()
{
}

void CStatic_Spike::Update()
{
}

void CStatic_Spike::Render(HDC _dc)
{
	TransparentBlt(_dc
		, (int)GetPos().x
		, (int)GetPos().y
		, m_pTexture->Width()
		, m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, m_pTexture->Width()
		, m_pTexture->Height()
		, RGB(112, 12, 41)
	);
}

