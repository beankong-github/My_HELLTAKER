#pragma once
// 지연 처리 관리
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