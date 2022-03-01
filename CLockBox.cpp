#include "pch.h"
#include "CLockBox.h"

#include "CStageMgr.h"
#include "CStage_Puzzle.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"

#include "CTile.h"
#include "CTileMap.h"

int iSwitch = 1;

CLockBox::CLockBox(CTile* _pTile)
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
	SetType(EOBSTACLE_TYPE::LOCKBOX);

	// �ؽ�ó �ε�
	m_pCurTex = CResMgr::GetInst()->LoadTexture(L"lockbox", L"texture\\object\\lock_box\\lockbox.bmp");

	// ���� ��ġ ����
	m_vOriginalPos = GetCurTile()->GetPos();
	SetPos(GetCurTile()->GetPos());
}

CLockBox::~CLockBox()
{

}

void CLockBox::Update()
{
	if(EOBSTACLE_STATE::KICKED == GetState())
		Shake();
}

void CLockBox::Render(HDC _dc)
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

void CLockBox::Shake()
{
	if (m_fEffectTime >= m_fAddTime)
	{
		SetPos(m_vOriginalPos + iSwitch * 2.5f);
		m_fAddTime += DS;
		iSwitch *= -1;
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

