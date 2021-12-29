#pragma once

class CPlayer
{
private:
	Vec m_vPos;
	Vec m_vScale;


public:
	void SetPos(Vec _point){m_vPos = _point;}
	void SetScale(Vec _point){m_vScale = _point;}

	Vec GetPos() { return m_vPos; }
	Vec GetScale(){return m_vScale;}

public:
	void Render(HDC _dc);
	void Update();

public:
	CPlayer();
	~CPlayer();
};

