#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CStage.h"
#include "CTexture.h"
#include "CBullet.h"


CPlayer::CPlayer()
	: m_fSpeed(300.f)
	, m_pTex(nullptr)
{
	// 이름 설정
	SetName(L"Player");

	// 텍스처 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", L"texture\\Plane.bmp");

	// 충돌체 생성
	CCollider* pCol = new CCollider;
	pCol->SetOffsetPos(Vec(0.f, 0.f));
	pCol->SetScale(Vec(60.f, 40.f));
	AddComponent(pCol);
}


CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Vec vPos = GetPos();
	
	// Player 이동
	if (IS_KEY_PRESSED(KEY::LEFT)) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		vPos.x -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::UP))
	{
		vPos.y -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DS;
	}

	// 총알 생성
	if (IS_KEY_TAP(KEY::SPACE))
	{
		// Bullet 초기화
		CObj* pBullet = new CBullet;

		Vec vPos = GetPos();
		Vec vScale = GetScale();
		pBullet->SetScale(vScale / 2.f);
		vPos = Vec(vPos.x, vPos.y - vScale.y / 2.f);

		CreateObject(pBullet, EOBJ_TYPE::PLAYER_PROJECTILE, vPos);
	}

	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	// 이미지로 출력
	Vec vPos = GetPos();

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	//BitBlt(_dc, (int)vPos.x - iWidth/2, (int)vPos.y - iHeight/2, iWidth, iHeight, m_pTex->GetDC(), 0, 0, SRCCOPY);

	TransparentBlt( _dc,
					(int)vPos.x - iWidth / 2,
					(int)vPos.y - iHeight / 2,
					iWidth, iHeight,
					m_pTex->GetDC(),
					0,0,
					iWidth, iHeight,
					RGB(255,0,255));

#ifdef _DEBUG
	// 플레이어 소속 component render
 	Render_Component(_dc);
#endif // DEBUG

}

void CPlayer::OnCollision(CObj* _pOther)
{
}
