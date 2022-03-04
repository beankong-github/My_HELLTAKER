#include "pch.h"
#include "CBtn_Option.h"

#include "CCamera.h"

#include "CTexture.h"
#include "CResMgr.h"

CBtn_Option::CBtn_Option()
{
	m_pUnSelectImg = CResMgr::GetInst()->LoadTexture(L"button_1", L"texture\\ui\\dialog\\dialog_ui\\");
	m_pSelectImg = CResMgr::GetInst()->LoadTexture(L"button_2", L"texture\\ui\\dialog\\dialog_ui\\");
}

CBtn_Option::~CBtn_Option()
{
}

void CBtn_Option::MouseLbtnClicked(Vec _vMousePos)
{
}

void CBtn_Option::Update()
{
}

void CBtn_Option::Render(HDC _dc)
{
	CUI::Render(_dc);

	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	// 이미지 렌더
	if (IsMouseOn())
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

	// 텍스트 렌더

}

