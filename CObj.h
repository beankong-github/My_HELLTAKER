#pragma once
class CObj
{
private:
	wstring m_strName;
	Vec m_vPos;
	Vec m_vScale;

public:
	void SetName(wstring _name) { m_strName = _name; }
	void SetPos(Vec _point) { m_vPos = _point; }
	void SetScale(Vec _point) { m_vScale = _point; }

	const wstring& GetName() { return m_strName; }
	Vec GetPos() { return m_vPos; }
	Vec GetScale() { return m_vScale; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC _dc);

public:
	CObj();
	~CObj();
};

