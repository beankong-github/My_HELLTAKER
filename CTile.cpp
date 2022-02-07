#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
	:m_iImgIdx(-1)
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
	if (0 > m_iImgIdx || nullptr == m_pAtlas)
		return;

	UINT iWidth = m_pAtlas->Width();
	UINT iHeight = m_pAtlas->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iMaxCount = iMaxCol * iMaxRow;
	
	UINT iRow = m_iImgIdx / iMaxCol;
	UINT iCol = m_iImgIdx % iMaxCol;

	// 최대 인텍스를 넘어 선 경우
	if (m_iImgIdx >= iMaxCount)
		return;

	Vec vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec vSize = GetScale();

	BitBlt(_dc, (int)vPos.x, (int)vPos.y, (int)vSize.x, (int)vSize.y, m_pAtlas->GetDC(), iCol * TILE_SIZE,  iRow * TILE_SIZE, SRCCOPY);
	//Rectangle(_dc, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vSize.x), (int)(vPos.y + vSize.y));
}

