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
	// ī���� ��Ʈ �ε�
	wstring path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightRegular.ttf").c_str());

	LOGFONT lf = LOGFONT{};
	lf.lfHeight = 180;			// ��Ʈ ũ��
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
	lstrcpy(lf.lfFaceName, TEXT("���� ����� Regular"));

	m_CounterFont = CreateFontIndirect(&lf);

	// �̸� ��Ʈ �ε�
	path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightBold.ttf").c_str());

	lf = LOGFONT{};
	lf.lfHeight = 40;			// ��Ʈ ũ��
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
	lstrcpy(lf.lfFaceName, TEXT("���� ����� Bold"));

	m_NameFont = CreateFontIndirect(&lf);

	// �ؽ�Ʈ ��Ʈ �ε�
	path = wstring(CPathMgr::GetInst()->GetContentPath());
	AddFontResource((path + L"font\\HeirofLightRegular.ttf").c_str());

	lf = LOGFONT{};
	lf.lfHeight = 35;			// ��Ʈ ũ��
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
	lstrcpy(lf.lfFaceName, TEXT("���� ����� Regular"));

	m_ScriptFont = CreateFontIndirect(&lf);
}

void CFontMgr::WriteCounterText(HDC _dc, int _Xpos, int _Ypos, wstring _szMessage)
{
	// ���� ��� ����, ����� ����
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// ���� ����, ��Ʈ ����
	COLORREF oldTextColor = SetTextColor(_dc, RGB(255, 255, 255));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_CounterFont);

	// ���ڿ� ���
	TextOut(_dc, _Xpos, _Ypos, _szMessage.c_str(), (int)_szMessage.length());

	// restore text color and font
	SetTextColor(_dc, oldTextColor);
	SelectObject(_dc, oldFont);
}

void CFontMgr::WriteNameText(HDC _dc, int _Xpos, int _Ypos, int _Width, int _Height, wstring _szMessage)
{	
	// ���� ��� ����, ����� ����
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// ���� ����, ��Ʈ ����
	COLORREF oldTextColor = SetTextColor(_dc, RGB(112, 12, 41));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_NameFont);

	// ���ڿ� ���
	RECT rt = { _Xpos, _Ypos, _Xpos + _Width, _Ypos + _Height };
	DrawText(_dc, _szMessage.c_str(), -1, &rt, DT_LEFT | DT_NOCLIP);

	// restore text color and font
	SetTextColor(_dc, oldTextColor);
	SelectObject(_dc, oldFont);
}

void CFontMgr::WriteScriptText(HDC _dc, int _Xpos, int _Ypos, int _Width, int _Height, wstring _szMessage)
{	
	// ���� ��� ����, ����� ����
	SetBkMode(_dc, 1);
	SetTextAlign(_dc, TA_CENTER);

	// ���� ����, ��Ʈ ����
	COLORREF oldTextColor = SetTextColor(_dc, RGB(255, 255, 255));
	HFONT oldFont = (HFONT)SelectObject(_dc, m_ScriptFont);

	// ���ڿ� ���
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
