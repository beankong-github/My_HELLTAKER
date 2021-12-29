#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
	:m_ptPos{},
	m_ptScale{}
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		m_ptPos.x += 1;
	}
}

void CPlayer::Render(HDC _dc)
{
	Rectangle(_dc, m_ptPos.x - (m_ptScale.x / 2),
		m_ptPos.y - (m_ptScale.y / 2),
		m_ptPos.x + (m_ptScale.x / 2),
		m_ptPos.y + (m_ptScale.y / 2));
}
