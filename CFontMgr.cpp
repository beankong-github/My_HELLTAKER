#include "pch.h"
#include "CFontMgr.h"

#include "CPathMgr.h"

CFontMgr::CFontMgr()
{
	LoadFont();
}

CFontMgr::~CFontMgr()
{
}

void CFontMgr::LoadFont()
{
	// 카운터 폰트 로드
	wstring path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightRegular.ttf").c_str());

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

	m_CounterFont = CreateFontIndirect(&lf);

	// 이름 폰트 로드
	path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightBold.ttf").c_str());

	lf = LOGFONT{};
	lf.lfHeight = 40;			// 폰트 크기
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
	lstrcpy(lf.lfFaceName, TEXT("빛의 계승자 Bold"));

	m_NameFont = CreateFontIndirect(&lf);

	// 텍스트 폰트 로드
	path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightRegular.ttf").c_str());

	lf = LOGFONT{};
	lf.lfHeight = 35;			// 폰트 크기
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

	m_ScriptFont = CreateFontIndirect(&lf);
}

void CFontMgr::WriteCounterText(HDC _dc, int _Xpos, int _Ypos, wstring _szMessage)
{
	// 글자 배경 삭제, 얼라인 센터
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// 글자 색상, 폰트 변경
	COLORREF oldTextColor = SetTextColor(_dc, RGB(255, 255, 255));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_CounterFont);

	// 문자열 출력
	TextOut(_dc, _Xpos, _Ypos, _szMessage.c_str(), (int)_szMessage.length());

	// restore text color and font
	SetTextColor(_dc, oldTextColor);
	SelectObject(_dc, oldFont);
}

void CFontMgr::WriteNameText(HDC _dc, int _Xpos, int _Ypos, int _Width, int _Height, wstring _szMessage)
{	
	// 글자 배경 삭제, 얼라인 센터
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// 글자 색상, 폰트 변경
	COLORREF oldTextColor = SetTextColor(_dc, RGB(112, 12, 41));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_NameFont);

	// 문자열 출력
	RECT rt = { _Xpos, _Ypos, _Xpos + _Width, _Ypos + _Height };
	DrawText(_dc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);

	// restore text color and font
	SetTextColor(_dc, oldTextColor);
	SelectObject(_dc, oldFont);
}

void CFontMgr::WriteScriptText(HDC _dc, int _Xpos, int _Ypos, int _Width, int _Height, wstring _szMessage)
{	
	// 글자 배경 삭제, 얼라인 센터
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// 글자 색상, 폰트 변경
	COLORREF oldTextColor = SetTextColor(_dc, RGB(255, 255, 255));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_ScriptFont);

	// 문자열 출력
	RECT rt = { _Xpos, _Ypos, _Xpos + _Width, _Ypos + _Height };
	DrawText(_dc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);


	// restore text color and font
	SetTextColor(_dc, oldTextColor);
	SelectObject(_dc, oldFont);
}

void CFontMgr::Exit()
{
	RemoveFontResource(L"HeirofLightRegular.ttf");
	RemoveFontResource(L"HeirofLightBold.ttf");

	DeleteObject(m_CounterFont);
	DeleteObject(m_NameFont);
	DeleteObject(m_ScriptFont);
}
