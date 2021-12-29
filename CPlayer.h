#pragma once

class CPlayer
{
private:
	POINT m_ptPos;
	POINT m_ptScale;


public:
	void SetPos(POINT _point){m_ptPos = _point;}
	void SetScale(POINT _point){m_ptScale = _point;}

	POINT GetPos() { return m_ptPos; }
	POINT GetScale(){return m_ptScale;}

public:
	void Render(HDC _dc);
	void Update();

public:
	CPlayer();
	~CPlayer();
};

