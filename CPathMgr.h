#pragma once

// vs, debug, release 어떤 방식으로 실행하든 동일한 경로로 접근해 리소스 가져올 수 있게 함
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_strContentPath[255];

public:
	void Init();

public:
	const wchar_t* GetContentPath() { return  m_strContentPath; }
};

