#pragma once


class CCore
{
	SINGLE(CCore);

	
private:
	HWND m_hwnd;
	HDC m_hDC;
	POINT m_ptResolution;

	HBITMAP m_hBackBitMap;
	HDC m_hBackDC;

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Update();

public:
	HWND GetMainWndHWND() {return m_hwnd;}
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
};

