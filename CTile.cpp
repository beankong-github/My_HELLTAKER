#include "pch.h"
#include "CTile.h"

#include "CCamera.h"
#include "CCore.h"
#include "CKeyMgr.h"

#include "CCollider.h"

CTile::CTile()
	:m_eType(ETILE_TYPE::NONE)
{
	// 이름 설정
	SetName(L"Tile");

	//// 충돌체 생성
	//CCollider* pCol = new CCollider;
	//pCol->SetOffsetPos(Vec {(TILE_SIZE/2), (TILE_SIZE / 2) });
	//pCol->SetScale(Vec(TILE_SIZE, TILE_SIZE));
	//AddComponent(pCol);
}

CTile::~CTile()
{
}

void CTile::Update()
{
#ifdef _DEBUG
	// 디버그 모드에서 타일을 클릭하면 타입이 바뀐다.
	if (IS_KEY_TAP(KEY::LBTN))
	{
		Vec mousePos = CKeyMgr::GetInst()->GetMousePos();

		if (mousePos.x >= GetPos().x
		&&  mousePos.x <= GetPos().x + GetScale().x
		&&	mousePos.y >= GetPos().y
		&&  mousePos.y <= GetPos().y + GetScale().y)
		{
			ETILE_TYPE type = (ETILE_TYPE)((UINT)m_eType + 1);
			if (type == ETILE_TYPE::END)
				type = ETILE_TYPE::NONE;

			m_eType = type;
		}
	}
#endif
}

void CTile::Render(HDC _dc)
{
#ifdef _DEBUG
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	SelectObject(_dc, CCore::GetInst()->GetRedPen());
	
	switch (m_eType)
	{
	case ETILE_TYPE::WALL:
		SelectObject(_dc, CCore::GetInst()->GetWhiteBRUSH());
		break;
	case ETILE_TYPE::OBSTACLE:
		SelectObject(_dc, CCore::GetInst()->GetGreenBRUSH());
		break;
	case ETILE_TYPE::START:
		SelectObject(_dc, CCore::GetInst()->GetBlueBRUSH());
		break;
	default:
		SelectObject(_dc, hBrush);
		break;
	}

	Rectangle(_dc, (int)GetPos().x, (int)GetPos().y, (int)GetPos().x + TILE_SIZE, (int)GetPos().y + TILE_SIZE);
#endif // _DEBUG

	Render_Component(_dc);
}

//void CTile::OnCollisionEnter(CObj* _pOther)
//{
//}
//
//void CTile::OnCollision(CObj* _pOther)
//{
//}
//
//void CTile::OnCollisionExit(CObj* _pOther)
//{
//}

