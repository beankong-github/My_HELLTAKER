#include "pch.h"
#include "CUI_Counter.h"

#include "CCore.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CStageMgr.h"
#include "CStage_Puzzle.h"
#include "CPathMgr.h"

CUI_Counter::CUI_Counter()
{
	// 텍스처 로드
	m_pFrontUITex = CResMgr::GetInst()->LoadTexture(L"ui_1", L"texture\\ui\\main_ui\\ui_1_test.bmp");
	m_pBackUITex = CResMgr::GetInst()->LoadTexture(L"ui_2", L"texture\\ui\\main_ui\\ui_2.bmp");

	// 폰트 추가
	CreateFont();

}

void CUI_Counter::Update()
{
}

void CUI_Counter::Render(HDC _dc)
{
	Vec vResolution = CCore::GetInst()->GetResolution();

	// 왼쪽 UI 이미지 렌더링
	Vec vFrontUI_RenderPos = Vec{ 0.f, vResolution.y - m_pFrontUITex->Height() };
	Vec vFrontUI_Size = Vec{ m_pFrontUITex->Width(), m_pFrontUITex->Height() };

	Vec vBackUI_RenderPos = Vec{ 0.f, 0.f };
	Vec vBackUI_Size = Vec{ m_pBackUITex->Width(), m_pBackUITex->Height() };

	BitBlt(
		_dc
		, (int)vBackUI_RenderPos.x
		, (int)vBackUI_RenderPos.y
		, (int)vBackUI_Size.x
		, (int)vBackUI_Size.y
		, m_pBackUITex->GetDC()
		, 0
		, 0
		, SRCCOPY
	);

	TransparentBlt(
		_dc
		, (int)vFrontUI_RenderPos.x
		, (int)vFrontUI_RenderPos.y
		, (int)vFrontUI_Size.x
		, (int)vFrontUI_Size.y
		, m_pFrontUITex->GetDC()
		, 0 , 0
		, (int)vFrontUI_Size.x
		, (int)vFrontUI_Size.y
		, RGB(0, 0, 0)
		);
	
	// 오른쪽 UI 이미지 렌더링
	vFrontUI_RenderPos = Vec{ vResolution.x - m_pFrontUITex->Width(),vResolution.y - m_pFrontUITex->Height() };
	vFrontUI_Size = Vec{ m_pFrontUITex->Width(), m_pFrontUITex->Height() };

	vBackUI_RenderPos = Vec{ vResolution.x - m_pFrontUITex->Width() + 170,0.f};
	vBackUI_Size = Vec{ m_pBackUITex->Width(), m_pBackUITex->Height() };

	// Back
	HDC reverseBackUIDC = CreateCompatibleDC(_dc);
	HBITMAP buffer1 = CreateCompatibleBitmap(m_pBackUITex->GetDC(), (int)vBackUI_Size.x, (int)vBackUI_Size.y);
	HGDIOBJ oldObj1 = SelectObject(reverseBackUIDC, buffer1);

	StretchBlt(reverseBackUIDC				// 출력 대상 HDC
		, (int)vBackUI_Size.x				// 출력을 시작할 x 좌표
		, 0									// 출력을 시작할 y 좌표
		, (int)-(vBackUI_Size.x + 1)		// 출력을 종료할 x 좌료
		, (int)vBackUI_Size.y				// 출력을 종료할 y 좌표
		, m_pBackUITex->GetDC()				// Src's HDC
		, 0, 0								// src image start position
		, (int)vBackUI_Size.x				// image width
		, (int)vBackUI_Size.y				// image height
		, SRCCOPY							// copy 방법
	);

	BitBlt(
		_dc
		, (int)vBackUI_RenderPos.x
		, (int)vBackUI_RenderPos.y
		, (int)vBackUI_Size.x
		, (int)vBackUI_Size.y
		, reverseBackUIDC
		, 0
		, 0
		, SRCCOPY
	);

	DeleteObject(reverseBackUIDC);
	DeleteObject(buffer1);
	DeleteObject(oldObj1);
	
	// Front
	HDC reverseFrontUIDC = CreateCompatibleDC(_dc);
	HBITMAP buffer2 = CreateCompatibleBitmap(m_pFrontUITex->GetDC(), (int)vFrontUI_Size.x, (int)vFrontUI_Size.y);
	HGDIOBJ oldObj2 = SelectObject(reverseFrontUIDC, buffer2);
	
	StretchBlt(reverseFrontUIDC				// 출력 대상 HDC
		, (int)vFrontUI_Size.x				// 출력을 시작할 x 좌표
		, 0									// 출력을 시작할 y 좌표
		, (int)-(vFrontUI_Size.x + 1)		// 출력을 종료할 x 좌료
		, (int)vFrontUI_Size.y				// 출력을 종료할 y 좌표
		, m_pFrontUITex->GetDC()			// Src's HDC
		, 0, 0								// src image start position
		, (int)vFrontUI_Size.x				// image width
		, (int)vFrontUI_Size.y				// image height
		, SRCCOPY							// copy 방법
	);

	TransparentBlt(
		_dc
		, (int)vFrontUI_RenderPos.x
		, (int)vFrontUI_RenderPos.y
		, (int)vFrontUI_Size.x
		, (int)vFrontUI_Size.y
		, reverseFrontUIDC
		, 0 , 0
		, (int)vFrontUI_Size.x
		, (int)vFrontUI_Size.y
		, RGB(0, 0, 0)
		);

	DeleteObject(reverseFrontUIDC);
	DeleteObject(buffer2);
	DeleteObject(oldObj2);

	// Counter 글씨 출력
	CStage_Puzzle* curStage = dynamic_cast<CStage_Puzzle*>(CStageMgr::GetInst()->GetCurStage());
	if (nullptr != curStage)
	{
		Vec vResolution = CCore::GetInst()->GetResolution();
		wstring curCount = std::to_wstring(curStage->GetCurMoveCount());
		wstring curChap = std::to_wstring((UINT)curStage->GetChapter());

		SetBkMode(_dc, 1);
		SetTextColor(_dc, RGB(255, 255, 255)); 
		SetTextAlign(_dc, TA_CENTER);
		HFONT OldFont = (HFONT)SelectObject(_dc, m_hFont); 
		TextOut(_dc, 200, 730, curCount.c_str(), curCount.length());
		TextOut(_dc, vResolution.x - 190, 730, curChap.c_str(), curCount.length());
		DeleteObject(OldFont);
	}


}

void CUI_Counter::CreateFont()
{
	wstring path = wstring(CPathMgr::GetInst()->GetContentPath());
	int a = AddFontResource((path + L"font\\HeirofLightRegular.ttf").c_str());

	LOGFONT lf = LOGFONT{};
	lf.lfHeight = 180;			// 폰트 크기
	lf.lfWeight = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGEUL_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = FIXED_PITCH;
	lstrcpy(lf.lfFaceName, TEXT("빛의 계승자 Regular"));

	m_hFont = CreateFontIndirect(&lf);
}

CUI_Counter::~CUI_Counter()
{
	RemoveFontResource(L"HeirofLightRegular.ttf");
	DeleteObject(m_hFont);
}
