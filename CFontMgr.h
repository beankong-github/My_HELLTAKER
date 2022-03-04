#pragma once
class CFontMgr
{
	SINGLE(CFontMgr);

private:
	HFONT	m_CounterFont;
	HFONT	m_NameFont;
	HFONT	m_ScriptFont;

public:
	void LoadFont();
	
	void WriteCounterText(HDC _dc, int _Xpos, int _Ypos, wstring _szMessage);
	void WriteNameText(HDC _dc, int _Xpos, int _Ypos, wstring _szMessage);
	void WriteScriptText(HDC _dc, int _Xpos, int _Ypos, wstring _szMessage);

public:
	void Exit();
};

