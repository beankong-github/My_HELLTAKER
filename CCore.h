#pragma once


class CCore
{
	SINGLE(CCore);

	
private:
	HWND		m_hwnd;
	HDC			m_hDC;
	POINT		m_ptResolution;

	HBITMAP		m_hBackBitMap;
	HDC			m_hBackDC;

	HPEN		m_hGreenPen;
	HPEN		m_hRedPen;
	
	HBRUSH		m_hBGBrush;
	HBRUSH		m_hWhiteBrush;
	HBRUSH		m_hRedBrush;
	HBRUSH		m_hGreenBrush;
	HBRUSH		m_hBlueBrush;



public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Update();

public:
	HWND	GetMainWndHWND()	{ return m_hwnd;}
	HDC		GetMainDC()			{ return m_hDC; }
	POINT	GetResolution()		{ return m_ptResolution; }

	HPEN	GetGreenPen()		{ return m_hGreenPen; }
	HPEN	GetRedPen()			{ return m_hRedPen; }

	HBRUSH	GetBGBRUSH()		{ return m_hBGBrush; }
	HBRUSH	GetWhiteBRUSH()		{ return m_hWhiteBrush; }
	HBRUSH	GetRedBRUSH()		{ return m_hRedBrush; }
	HBRUSH	GetGreenBRUSH()		{ return m_hGreenBrush; }
	HBRUSH	GetBlueBRUSH()		{ return m_hBlueBrush; }


	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);
};

