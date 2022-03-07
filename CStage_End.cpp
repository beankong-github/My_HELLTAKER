#include "pch.h"
#include "CStage_End.h"

#include "CCore.h"
#include "CStageMgr.h"
#include "CKeyMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"

#include "CSound.h"
#include "CTexture.h"
#include "CUI_Dialog.h"

void CStage_End::Init()
{
}

void CStage_End::Update()
{
	CStage::Update();
}

void CStage_End::Render(HDC _dc)
{
	Vec resolution = CCore::GetInst()->GetResolution();


	CStage::Render(_dc);

	CTexture* pTex;

	if (m_pDailog->GetCurPage() == 0)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"cutscene_4", L"texture\\ui\\dialog\\dialog_cutscene\\cutscene_4.bmp");

		BitBlt(_dc, resolution.x / 2 - pTex->Width() / 2, 30, pTex->Width(), pTex->Height(), pTex->GetDC(), 0, 0, SRCCOPY);

		pTex = nullptr;
		return;
	}

	if (m_pDailog->GetCurPage() == 1)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"cutscene_5", L"texture\\ui\\dialog\\dialog_cutscene\\cutscene_5.bmp");

		BitBlt(_dc, resolution.x / 2 - pTex->Width() / 2, 30, pTex->Width(), pTex->Height(), pTex->GetDC(), 0, 0, SRCCOPY);

		pTex = nullptr;
		return;
	}

	if (m_pDailog->GetCurPage() == 2)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"cutscene_5", L"texture\\ui\\dialog\\dialog_cutscene\\cutscene_5.bmp");

		BitBlt(_dc, resolution.x / 2 - pTex->Width() / 2, 30, pTex->Width(), pTex->Height(), pTex->GetDC(), 0, 0, SRCCOPY);

		pTex = nullptr;
		return;
	}
}

void CStage_End::Enter()
{
}

void CStage_End::Exit()
{
	m_pEndBGM = CResMgr::GetInst()->LoadSound(L"Apropos", L"sound\\Apropos.wav");
	m_pEndBGM->SetVolume(100);
	m_pEndBGM->PlayToBGM(true);
}

void CStage_End::DialogTermination()
{
	HWND hWnd = CCore::GetInst()->GetMainWndHWND();
	if (hWnd) SendMessage(hWnd, WM_CLOSE, 0, 0);
}

CStage_End::CStage_End()
{
	SetStageName(L"End");

	m_pDailog = new CUI_Dialog(L"end");
	m_pDailog->SetCurStage(this);
	AddObject(m_pDailog, EOBJ_TYPE::DIALOG);


}

CStage_End::~CStage_End()
{
}
