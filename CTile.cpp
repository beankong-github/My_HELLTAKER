#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
{
	m_pAtlas = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\tile\\TILE.bmp");
}

CTile::~CTile()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{
	Vec vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec vSize = GetScale();

	BitBlt(_dc, (int)vPos.x, (int)vPos.y, (int)vSize.x, (int)vSize.y, m_pAtlas->GetDC(), 0, 0, SRCCOPY);
	//Rectangle(_dc, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vSize.x), (int)(vPos.y + vSize.y));
}

