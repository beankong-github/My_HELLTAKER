#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CBullet.h"
#include "CCore.h"
#include "CStage.h"

CPlayer::CPlayer()
	:m_fSpeed(400.f)	
{
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
		CObj* bObj = new CBullet;
		bObj->SetPos(GetPos());
		bObj->SetScale(Vec{ 30, 30 });
		g_stage.AddObject(bObj);
	}
	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	CObj::Render(_dc);
}
