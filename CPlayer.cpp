#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

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
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		m_vPos.x -= m_fSpeed * CTimeMgr::GetInst()->GetDS();
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_vPos.x += m_fSpeed * CTimeMgr::GetInst()->GetDS();
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_vPos.y -= m_fSpeed * CTimeMgr::GetInst()->GetDS();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_vPos.y += m_fSpeed * CTimeMgr::GetInst()->GetDS();
	}
}

void CPlayer::Render(HDC _dc)
{
	Rectangle(_dc,  (int)(m_vPos.x - (m_vScale.x / 2.f)),
				 	(int)(m_vPos.y - (m_vScale.y / 2.f)),
				 	(int)(m_vPos.x + (m_vScale.x / 2.f)),
					(int)(m_vPos.y + (m_vScale.y / 2.f)));
}
