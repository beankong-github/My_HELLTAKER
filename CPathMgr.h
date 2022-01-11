#pragma once

// vs, debug, release 어떤 방식으로 실행하든 동일한 경로로 접근해 리소스 가져올 수 있게 함
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	void Init();
public:
	wchar_t* GetContentPath();
};

