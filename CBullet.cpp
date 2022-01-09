#include "pch.h"
#include "CBullet.h"
#include "CTimeMgr.h"

CBullet::CBullet()
	:m_fSpeed(200.f)
{
}

CBullet::~CBullet()
{
}

void CBullet::Init()
{
}

void CBullet::Update()
{
	Vec Pos = GetPos();
	
	Pos.y -= m_fSpeed * DS;

	SetPos(Pos);
}

void CBullet::Render(HDC _dc)
{
	Vec vPos = GetPos();
	Vec vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - (vScale.x / 2.f)),
		(int)(vPos.y - (vScale.y / 2.f)),
		(int)(vPos.x + (vScale.x / 2.f)),
		(int)(vPos.y + (vScale.y / 2.f)));
}

