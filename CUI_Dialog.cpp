#include "pch.h"
#include "CUI_Dialog.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CFontMgr.h"
#include "CKeyMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CBtn_Option.h"
#include "CStage.h"


CUI_Dialog::CUI_Dialog(wstring _ID)
	: m_wstrID(_ID)
	, m_iSize(0)
	, m_iCurPage(0)
	, m_bBGFlow(false)
	, m_pDialogs{}
{
	Load();

	m_pDialogBox = CResMgr::GetInst()->LoadTexture(L"dialog_box", L"texture\\ui\\dialog\\dialog_ui\\dialog_box.bmp");
}

void CUI_Dialog::Load()
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"dialog\\" + m_wstrID + L".dialog";


	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// �ش� ����� ������ �б� ���� ���� ���� ������ ������ �ּҰ��� ������ �ּҸ� �������ش�.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"���̾�α� �ε� ����", MB_OK);

		return;
	}

	// =======================
	// ���̾�α� ������ �о����
	// =======================

	// �ػ� ������ ���
	Vec resolution = CCore::GetInst()->GetResolution();

	// ���̾�α� ������
	wchar_t szBuff[256] = L"";
	fwscanf_s(pFile, L"%s", szBuff, 256);	// [Dialog_ID]]
	fwscanf_s(pFile, L"%s", szBuff, 256);	// intro
	fwscanf_s(pFile, L"%s", szBuff, 256);	// [Dialog_Size]
	fwscanf_s(pFile, L"%s", szBuff, 256);	// size
	m_iSize = _wtoi(szBuff);

	// �� �� ����
	for (UINT i = 0; i < m_iSize; ++i)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);	//[Dialog_Cut_Info]

		Dialog_Page* dialog = new Dialog_Page{};
		
		// ���
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [BGTex_name]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [BGTex_name]
		if (L"0" != (wstring)szBuff)
		{
			dialog->pBGTex = CResMgr::GetInst()->LoadTexture(szBuff, L"texture\\ui\\dialog\\dialog_bg\\" + wstring(szBuff) + L".bmp");
			m_vBGPos = Vec{ 0, 80 };
		}

		fwscanf_s(pFile, L"%s", szBuff, 256);	// [Flow]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// Flow ����
		m_bBGFlow = (bool)_wtoi(szBuff);


		// �ʻ�ȭ �̸�
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [PortraitTex_name]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// �ʻ�ȭ �̸�
		if (L"0" != (wstring)szBuff)
		{
			// �ʻ�ȭ �̹��� ���ϱ�
			dialog->pPortrait = CResMgr::GetInst()->LoadTexture(szBuff, L"texture\\ui\\dialog\\dialog_chara\\" + wstring(szBuff) + L".bmp");

			// �ʻ�ȭ ��ġ ����
			m_vPortaritPos = Vec{ resolution.x/2 - dialog->pPortrait->Width()/2, 0.f };
			
		}
		else
			dialog->pPortrait = nullptr;

		// �̸�
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [name]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// name
		if (L"\r\n" != (wstring)szBuff)
			dialog->wstrName = szBuff;
		else
			dialog->wstrName = L"";

		// �ؽ�Ʈ
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [text]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// ���ڿ�
		if (L"0" != (wstring)szBuff)
			dialog->wstrText = szBuff;
		else
			dialog->wstrText = L"";

		// ������ 1
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [OptionOneText]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// ���ڿ�
		if (L"\r\n" != (wstring)szBuff)
		{
			m_pFirstOption = new CBtn_Option();

			m_pFirstOption->SetText(szBuff);
			m_vOptionOnePos = Vec{ resolution.x / 2 - 500, 800.f };
			m_pFirstOption->SetPos(m_vOptionOnePos);
			m_pFirstOption->SetOwnerDialog(this);
			m_pFirstOption->SetPage(i);
			m_pFirstOption->Select();

			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
			if (L"1" == szBuff)
				m_pFirstOption->SetAnswer();

			AddChildUI(m_pFirstOption);
		}
		else
		{
			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
		}

		// ������ 2
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [OptionTwoText]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// ���ڿ�
		if (L"\r\n" != (wstring)szBuff)
		{
			m_pSecondeOption = new CBtn_Option();

			m_pSecondeOption->SetText(szBuff);
			m_vOptionTwoPos = Vec{ resolution.x / 2 - 500, 900.f };
			m_pSecondeOption->SetPos(m_vOptionTwoPos);
			m_pSecondeOption->SetOwnerDialog(this);
			m_pSecondeOption->SetPage(i);
			AddChildUI(m_pSecondeOption);

			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
			if (L"1" == szBuff)
				m_pSecondeOption->SetAnswer();

		}
		else
		{
			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
		}
		
		m_pDialogs.push_back(dialog);
	}
		// ===============
		//	  ���� �ݱ�
		// ===============
		fclose(pFile);
}

void CUI_Dialog::FirstOptionSelected()
{
	m_pCurStage->FirstOptionSelected();
}

void CUI_Dialog::SecondOptionSelected()
{
	m_pCurStage->SecondOptionSelected();
}


void CUI_Dialog::Update()
{
	if (IS_KEY_TAP(KEY::ENTER))
	{
		if (m_pFirstOption != nullptr)
		{
			if (m_iCurPage == m_pFirstOption->GetPage() && m_pFirstOption->IsSelected())
			{
				FirstOptionSelected();
				return;
			}
		}
		
		if (m_pSecondeOption != nullptr)
		{
			if (m_iCurPage == m_pSecondeOption->GetPage() && m_pSecondeOption->IsSelected())
			{
				SecondOptionSelected();
				return;
			}
		}

		if (m_iCurPage < m_pDialogs.size()-1)
			++m_iCurPage;
		else
		{
			m_pCurStage->DialogTermination();
		}
	}

	if (IS_KEY_TAP(KEY::W) || IS_KEY_TAP(KEY::S)
		|| IS_KEY_TAP(KEY::UP) || IS_KEY_TAP(KEY::DOWN))
	{ 
		if (m_pFirstOption != nullptr)
		{
			if (m_iCurPage == m_pFirstOption->GetPage())
			{
				if(m_pFirstOption->IsSelected())
					m_pFirstOption->Unselect();
				else
					m_pFirstOption->Select();
			}
		}

		if (m_pSecondeOption != nullptr)
		{
			if (m_iCurPage == m_pSecondeOption->GetPage())
			{
				if (m_pSecondeOption->IsSelected())
					m_pSecondeOption->Unselect();
				else
					m_pSecondeOption->Select();
			}
		}
	}
	CUI::Update();

}

void CUI_Dialog::Render(HDC _dc)
{
	if (m_iCurPage >= m_iSize)
		return;

	Dialog_Page* curPage = m_pDialogs[m_iCurPage];

	Vec resolution = CCore::GetInst()->GetResolution();

	// ��� �̹��� ������
	if (curPage->pBGTex != nullptr)
	{
		BitBlt(_dc
			, int(m_vBGPos.x)	// x
			, int(m_vBGPos.y)	// y
			, int(resolution.x)	// width
			, int(curPage->pBGTex->Height())	// height
			, curPage->pBGTex->GetDC()	// Src's HDC
			, 0, 0
			, SRCCOPY
		);
	}

	// �ʻ�ȭ ������
	if (curPage->pPortrait != nullptr)
	{
		TransparentBlt(_dc
			, int(m_vPortaritPos.x)	// x
			, int(m_vPortaritPos.y)	// y
			, int(curPage->pPortrait->Width())	// width
			, int(curPage->pPortrait->Height())	// height
			, curPage->pPortrait->GetDC()	// Src's HDC
			, 0, 0
			, int(curPage->pPortrait->Width())		// width in atlas
			, int(curPage->pPortrait->Height())		// height int atlas
			, RGB(0, 0, 0));
	}


	// ��ȭ �ڽ� ������
	BitBlt(_dc
		, 0	// x
		, 600	// y
		, int(m_pDialogBox->Width())	// width
		, int(m_pDialogBox->Height())	// height
		, m_pDialogBox->GetDC()	// Src's HDC
		, 0, 0
		, SRCCOPY
	);

	// �۾� ������
	CFontMgr::GetInst()->WriteNameText(_dc, (int)resolution.x/2, 570, (int)resolution.x, 100,   curPage->wstrName);
	// Text ������
	CFontMgr::GetInst()->WriteScriptText(_dc, (int)resolution.x/2, 650, (int)resolution.x, 300, curPage->wstrText);

	CUI::Render(_dc);
}


CUI_Dialog::~CUI_Dialog()
{
	Safe_Del_Vec(m_pDialogs);
}
