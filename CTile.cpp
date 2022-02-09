#include "pch.h"
#include "CTile.h"

#include "CCamera.h"
#include "CCore.h"

#include "CCollider.h"

CTile::CTile()
{
	// 이름 설정
	SetName(L"Tile");

	// 충돌체 생성
	CCollider* pCol = new CCollider;
	pCol->SetOffsetPos(Vec {(TILE_SIZE/2), (TILE_SIZE / 2) });
	pCol->SetScale(Vec(TILE_SIZE, TILE_SIZE));
	AddComponent(pCol);
}

CTile::~CTile()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{
#ifdef _DEBUG
	Rectangle(_dc,(int)GetPos().x, (int)GetPos().y, (int)GetPos().x + TILE_SIZE, (int)GetPos().y + TILE_SIZE);

	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	SelectObject(_dc, CCore::GetInst()->GetRedPen());
	SelectObject(_dc, hBrush);
#endif // _DEBUG

	Render_Component(_dc);
}

void CTile::OnCollisionEnter(CObj* _pOther)
{
}

void CTile::OnCollision(CObj* _pOther)
{
}

void CTile::OnCollisionExit(CObj* _pOther)
{
}

