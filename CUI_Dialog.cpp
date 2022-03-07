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
#include "CSound.h"

#include "CBtn_Option.h"
#include "CStage.h"

#include "CUI_Success.h"


CUI_Dialog::CUI_Dialog(wstring _ID)
	: m_wstrID(_ID)
	, m_iSize(0)
	, m_iCurPage(0)
	, m_bBGFlow(false)
	, m_pDialogs{}
{
	Load();

	m_pDialogBox = CResMgr::GetInst()->LoadTexture(L"dialog_box", L"texture\\ui\\dialog\\dialog_ui\\dialog_box.bmp");

	// 사운드 등록
	m_pButtonConirm = CResMgr::GetInst()->LoadSound(L"button_dialogue_confirm_01", L"sound\\button_dialogue_confirm_01.wav");
	m_pButtonHighLight =CResMgr::GetInst()->LoadSound(L"button_chapter_highlight_01", L"sound\\button_chapter_highlight_01.wav");
	m_pNextPage =CResMgr::GetInst()->LoadSound(L"dialogue_text_end_01", L"sound\\dialogue_text_end_01.wav");


	// booper 애니메이션 추가
}

void CUI_Dialog::Load()
{
	// ===============
	//	절대 경로 찾기
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"dialog\\" + m_wstrID + L".dialog";


	// ===============
	//	  파일 열기
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// 해당 경로의 파일을 읽기 모드로 열어 파일 포인터 변수의 주소값에 파일의 주소를 저장해준다.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"다이어로그 로딩 오류", MB_OK);

		return;
	}

	// =======================
	// 다이어로그 데이터 읽어오기
	// =======================

	// 해상도 사이즈 얻기
	Vec resolution = CCore::GetInst()->GetResolution();

	// 다이어로그 사이즈
	wchar_t szBuff[256] = L"";
	fwscanf_s(pFile, L"%s", szBuff, 256);	// [Dialog_ID]]
	fwscanf_s(pFile, L"%s", szBuff, 256);	// intro
	fwscanf_s(pFile, L"%s", szBuff, 256);	// [Dialog_Size]
	fwscanf_s(pFile, L"%s", szBuff, 256);	// size
	m_iSize = _wtoi(szBuff);

	// 각 컷 정보
	for (UINT i = 0; i < m_iSize; ++i)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);	//[Dialog_Cut_Info]

		Dialog_Page* dialog = new Dialog_Page{};
		
		// 배경
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [BGTex_name]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [BGTex_name]
		if (L"0" != (wstring)szBuff)
		{
			dialog->pBGTex = CResMgr::GetInst()->LoadTexture(szBuff, L"texture\\ui\\dialog\\dialog_bg\\" + wstring(szBuff) + L".bmp");
			m_vBGPos = Vec{ 0, 80 };
		}

		fwscanf_s(pFile, L"%s", szBuff, 256);	// [Flow]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// Flow 여부
		m_bBGFlow = (bool)_wtoi(szBuff);


		// 초상화 이름
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [PortraitTex_name]
		fwscanf_s(pFile, L"%s", szBuff, 256);	// 초상화 이름
		if (L"0" != (wstring)szBuff)
		{
			// 초상화 이미지 구하기
			dialog->pPortrait = CResMgr::GetInst()->LoadTexture(szBuff, L"texture\\ui\\dialog\\dialog_chara\\" + wstring(szBuff) + L".bmp");

			// 초상화 위치 설정
			m_vPortaritPos = Vec{ resolution.x/2 - dialog->pPortrait->Width()/2, 0.f };
			
		}
		else
			dialog->pPortrait = nullptr;

		// 이름
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [name]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// name
		if (L"\r\n" != (wstring)szBuff)
			dialog->wstrName = szBuff;
		else
			dialog->wstrName = L"";

		// 텍스트
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [text]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// 문자열
		if (L"0" != (wstring)szBuff)
			dialog->wstrText = szBuff;
		else
			dialog->wstrText = L"";

		// 선택지 1
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [OptionOneText]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// 문자열
		if (L"\r\n" != (wstring)szBuff)
		{
			m_pFirstOption = new CBtn_Option();

			m_pFirstOption->SetText(szBuff);
			m_vOptionOnePos = Vec{ resolution.x / 2 - 500, 800.f };
			m_pFirstOption->SetPos(m_vOptionOnePos);
			m_pFirstOption->SetOwnerDialog(this);
			m_pFirstOption->SetPage(i);
			m_pFirstOption->Highlight();

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

		// 선택지 2
		fwscanf_s(pFile, L"%s", szBuff, 256);	// [OptionTwoText]
		fwscanf_s(pFile, L"%[^s]s", szBuff, 256);	// 문자열
		if (L"\r\n" != (wstring)szBuff)
		{
			m_pSecondOption = new CBtn_Option();

			m_pSecondOption->SetText(szBuff);
			m_vOptionTwoPos = Vec{ resolution.x / 2 - 500, 900.f };
			m_pSecondOption->SetPos(m_vOptionTwoPos);
			m_pSecondOption->SetOwnerDialog(this);
			m_pSecondOption->SetPage(i);
			AddChildUI(m_pSecondOption);

			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
			if (L"1" == szBuff)
				m_pSecondOption->SetAnswer();

		}
		else
		{
			fwscanf_s(pFile, L"%s", szBuff, 256);	// [IsAnswer]
			fwscanf_s(pFile, L"%s", szBuff, 256);
		}
		
		m_pDialogs.push_back(dialog);
	}
		// ===============
		//	  파일 닫기
		// ===============
		fclose(pFile);
}

void CUI_Dialog::FirstOptionSelected()
{
	// 사운드 재생
	m_pButtonConirm->Play();

	// 동작
	m_pCurStage->FirstOptionSelected();
}

void CUI_Dialog::SecondOptionSelected()
{
	// 사운드 재생
	m_pButtonConirm->Play();

	// 동작
	m_pCurStage->SecondOptionSelected();
}


void CUI_Dialog::Update()
{
	if (IS_KEY_TAP(KEY::ENTER))
	{
		if (m_pFirstOption != nullptr)
		{
			if (m_iCurPage == m_pFirstOption->GetPage() && m_pFirstOption->IsHighlighted())
			{
				FirstOptionSelected();
				return;
			}
		}
		
		if (m_pSecondOption != nullptr)
		{
			if (m_iCurPage == m_pSecondOption->GetPage() && m_pSecondOption->IsHighlighted())
			{
				SecondOptionSelected();
				return;
			}
		}

		// 페이지 이동
		if (m_iCurPage < m_pDialogs.size() - 1)
		{
			// 사운드
			m_pNextPage->Play();
			++m_iCurPage;
		}
		
		// 다이어로그 종료
		else
		{
			m_pCurStage->DialogTermination();
		}
	}

	if (IS_KEY_TAP(KEY::W) || IS_KEY_TAP(KEY::S)
		|| IS_KEY_TAP(KEY::UP) || IS_KEY_TAP(KEY::DOWN))
	{ 
		if (m_pFirstOption != nullptr && m_pSecondOption != nullptr)
		{
			if (m_iCurPage == m_pFirstOption->GetPage() && m_iCurPage == m_pSecondOption->GetPage())
			{
				// 사운드
				m_pButtonHighLight->Play();

				//  첫번째 버튼 하이라이트 전환
				if(m_pFirstOption->IsHighlighted())
					m_pFirstOption->Unhighlight();
				else
					m_pFirstOption->Highlight();

				// 두번째 버튼 하이라이트 전환
				if (m_pSecondOption->IsHighlighted())
					m_pSecondOption->Unhighlight();
				else
					m_pSecondOption->Highlight();
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

	// 배경 이미지 렌더링
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

	// 초상화 렌더링
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


	// 대화 박스 렌더링
	BitBlt(_dc
		, 0	// x
		, 600	// y
		, int(m_pDialogBox->Width())	// width
		, int(m_pDialogBox->Height())	// height
		, m_pDialogBox->GetDC()	// Src's HDC
		, 0, 0
		, SRCCOPY
	);

	// 글씨 렌더링
	CFontMgr::GetInst()->WriteNameText(_dc, (int)resolution.x/2, 570, (int)resolution.x, 100,   curPage->wstrName);
	// Text 렌더링
	CFontMgr::GetInst()->WriteScriptText(_dc, (int)resolution.x/2, 650, (int)resolution.x, 300, curPage->wstrText);

	CUI::Render(_dc);
}


CUI_Dialog::~CUI_Dialog()
{
	Safe_Del_Vec(m_pDialogs);
}
