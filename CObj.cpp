#include "pch.h"
#include "CObj.h"

void CObj::Render(HDC _dc)
{
	Rectangle(_dc, (int)(m_vPos.x - (m_vScale.x / 2.f)),
		(int)(m_vPos.y - (m_vScale.y / 2.f)),
		(int)(m_vPos.x + (m_vScale.x / 2.f)),
		(int)(m_vPos.y + (m_vScale.y / 2.f)));
}

CObj::CObj()
	:m_vPos{}
	,m_vScale{}
{
}

CObj::~CObj()
{
}
