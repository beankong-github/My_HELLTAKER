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
		Vec renderPos = CCamera::GetInst()->GetRenderPos(GetPos());

		if (mousePos.x >= renderPos.x
		&&  mousePos.x <= renderPos.x + GetScale().x
		&&	mousePos.y >= renderPos.y
		&&  mousePos.y <= renderPos.y + GetScale().y)
		{
			ETILE_TYPE type = (ETILE_TYPE)((UINT)m_eType + 1);
			if (type >= ETILE_TYPE::END)
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
	case ETILE_TYPE::NPC:
		SelectObject(_dc, CCore::GetInst()->GetGreenBRUSH());
		break;
	case ETILE_TYPE::START:
		SelectObject(_dc, CCore::GetInst()->GetBlueBRUSH());
		break;
	case ETILE_TYPE::CLEAR:
		SelectObject(_dc, CCore::GetInst()->GetRedBRUSH());
		break;
	default:
		SelectObject(_dc, hBrush);
		break;
	}
	
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Rectangle(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)vRenderPos.x + TILE_SIZE
			, (int)vRenderPos.y + TILE_SIZE);
#endif // _DEBUG

	Render_Component(_dc);
}