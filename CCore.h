#pragma once
class CCore
{

private:
	HWND m_hwnd;

public:
	// 데이터 영역 싱글톤
	static CCore* GetInstance()
	{
		static CCore c;			// 최초 1회만 실행된다.
		return &c;
	}

	int Init(HWND _hwnd, POINT _ptResolution);

private:
	CCore();
	~CCore();
};

