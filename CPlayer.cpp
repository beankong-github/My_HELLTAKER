#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CPlayer::CPlayer()
	:m_vPos{}
	,m_vScale{}
	,m_fSpeed(400.f)	
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (IS_KEY_PRESSED(KEY::LEFT) || IS_KEY_TAP(KEY::LEFT)) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		m_vPos.x -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::RIGHT) || IS_KEY_TAP(KEY::RIGHT))
	{
		m_vPos.x += m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::UP) || IS_KEY_TAP(KEY::UP))
	{
		m_vPos.y -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::DOWN) || IS_KEY_TAP(KEY::DOWN))
	{
		m_vPos.y += m_fSpeed * DS;
	}
}

void CPlayer::Render(HDC _dc)
{
	Rectangle(_dc,  (int)(m_vPos.x - (m_vScale.x / 2.f)),
				 	(int)(m_vPos.y - (m_vScale.y / 2.f)),
				 	(int)(m_vPos.x + (m_vScale.x / 2.f)),
					(int)(m_vPos.y + (m_vScale.y / 2.f)));
}
