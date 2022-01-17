#pragma once
// 瘤楷 贸府 包府
class CEventMgr
{
	SINGLE(CEventMgr);

private:
	vector<tEventInfo>	m_vecEvent;
	vector<CObj*>		m_vecDead;

public:
	void Update();

public:
	void AddEvent(const tEventInfo& _event)
	{
		m_vecEvent.push_back(_event);
	}
};

