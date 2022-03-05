#include "pch.h"
#include "CBtn_Option.h"

#include "CResMgr.h"
#include "CFontMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CUI_Dialog.h"

CBtn_Option::CBtn_Option()
	: m_bSelected(false)
	, m_bAnswer(false)
{
	m_pUnSelectImg = CResMgr::GetInst()->LoadTexture(L"button_1", L"texture\\ui\\dialog\\dialog_ui\\button_1.bmp");
	m_pSelectImg = CResMgr::GetInst()->LoadTexture(L"button_2", L"texture\\ui\\dialog\\dialog_ui\\button_2.bmp");
}

CBtn_Option::~CBtn_Option()
{
}

void CBtn_Option::Update()
{
}

void CBtn_Option::Render(HDC _dc)
{
	if (m_iMyPage != m_pOwnerDialog->GetCurPage())
		return;
	CUI::Render(_dc);

	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	// ÀÌ¹ÌÁö ·»´õ
	if (m_bSelected)
	{
		TransparentBlt(_dc
			, int(vRenderPos.x)	// x
			, int(vRenderPos.y)	// y
			, int(m_pSelectImg->Width())	// width
			, int(m_pSelectImg->Height())	// height
			, m_pSelectImg->GetDC()	// Src's HDC
			, 0, 0
			, int(m_pSelectImg->Width())		// width in atlas
			, int(m_pSelectImg->Height())		// height int atlas
			, RGB(112, 12, 41));
	}
	else
	{
		TransparentBlt(_dc
			, int(vRenderPos.x)	// x
			, int(vRenderPos.y)	// y
			, int(m_pUnSelectImg->Width())	// width
			, int(m_pUnSelectImg->Height())	// height
			, m_pUnSelectImg->GetDC()	// Src's HDC
			, 0, 0
			, int(m_pUnSelectImg->Width())		// width in atlas
			, int(m_pUnSelectImg->Height())		// height int atlas
			, RGB(112, 12, 41));
	}

	// ÅØ½ºÆ® ·»´õ
	CFontMgr::GetInst()->WriteScriptText(_dc, GetPos().x + 1000/2, GetPos().y - 10, 1000, 100, m_wstring);
}

