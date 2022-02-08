#include "pch.h"
#include "CTile.h"

#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
	:m_iImgIdx(-1)
{
	//m_pAtlas = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\tile\\TILE.bmp");
}

CTile::~CTile()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{

}

