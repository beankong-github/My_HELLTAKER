#pragma once
class CObj
{
private:
	wstring m_strName;
	Vec m_vPos;
	Vec m_vScale;

	bool m_bDead;

public:
	void SetName(wstring _name)		{ m_strName = _name; }
	void SetPos(Vec _point)			{ m_vPos = _point; }
	void SetScale(Vec _point)		{ m_vScale = _point; }

	const wstring& GetName()		{ return m_strName; }
	Vec GetPos()					{ return m_vPos; }
	Vec GetScale()					{ return m_vScale; }
	
	bool isDead()					{ return m_bDead; }

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC _dc);

private:
	void SetDead(){	m_bDead = true;	}

public:
	CObj();
	virtual  ~CObj();

	friend class CEventMgr;
};

