#include "pch.h"
#include "CBackGround.h"

#include "CStageMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CStage_Puzzle.h"

CBackGround::CBackGround(ECHAPTER _chap)
	: m_eChap(_chap)
	, m_pTex(nullptr)
{
	// BackGround ����
	if (ECHAPTER::NONE == _chap || ECHAPTER::END == _chap)
	{
		assert(nullptr);
	}
	wstring wstrStageName = CStageMgr::GetInst()->GetCurStage()->GetStageName();
	m_pTex = CResMgr::GetInst()->LoadTexture(wstrStageName + L"_BG", L"texture\\background\\stage_bg\\" + wstrStageName + L".bmp");

}

CBackGround::~CBackGround()
{
}

void CBackGround::Update()
{
}

void CBackGround::Render(HDC _dc)
{	
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());	// ī�޶� ��ġ�� ���� �÷��̾� ���� ������ ��ġ ���ϱ�

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();
	
	TransparentBlt( _dc
					, (int)vRenderPos.x
					, (int)vRenderPos.y,
					iWidth, iHeight,
					m_pTex->GetDC(),
					0,0,
					iWidth, iHeight,
					RGB(255,0,255));

	Render_Component(_dc);
}

void CBackGround::OnCollisionEnter(CObj* _pOther)
{
}

void CBackGround::OnCollision(CObj* _pOther)
{
}

void CBackGround::OnCollisionExit(CObj* _pOther)
{
}

