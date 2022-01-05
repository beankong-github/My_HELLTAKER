#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_liFreqency;
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;

	float m_fDS;			// delta secound : 1 프레임에 걸린 시간
	float m_fOneSec;		// 1초 찾기
	UINT m_iFPS;			// frame per second
	UINT m_iElapsedTime;	// 경과 시간 (초단위) 

public:
	void Init();
	void Update();

public:
	float GetDS() { return m_fDS; }
	UINT GetFPS() { return m_iFPS; }
};

