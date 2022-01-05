#pragma once
class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd;
	HDC m_hDC;
	POINT m_ptResolution;

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Update();

public:
	HWND GetMainWndHWND() {return m_hwnd;}
};

