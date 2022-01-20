#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_liFreqency;
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;

	float m_fDS;			// delta secound : 1 프레임에 걸린 시간
	float m_fAddTime;		// 1초 찾기
	float m_fCurTime;		// 경과 시간 (초단위) 

	UINT m_iFPS;			// frame per second

public:
	void Init();
	void Update();

public:
	float GetDS()		{ return m_fDS;}
	float GetCurTime()	{ return m_fCurTime; }
	UINT GetFPS()		{ return m_iFPS;}

};

