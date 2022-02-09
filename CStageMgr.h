#pragma once

class CStage;

class CStageMgr
{
	SINGLE(CStageMgr);

private:
	CStage* m_arrStage[(UINT)ESTAGE_TYPE::STAGE_END][(UINT)ECHAPTER::END];	// 모든 스테이지 배열
	CStage* m_pCurStage; // 현재 스테이지

public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	CStage* GetCurStage() { return m_pCurStage; }

private:
	void ChangeStage(ESTAGE_TYPE _eNextStage, ECHAPTER _iChapter = ECHAPTER::NONE);
	friend class CEventMgr;
};

