#pragma once

class CPlayer
{
private:
	Vec m_vPos;
	Vec m_vScale;
	float m_fSpeed;		// 초당  이동 픽셀


public:
	void SetPos(Vec _point){m_vPos = _point;}
	void SetScale(Vec _point){m_vScale = _point;}
	void SetSpeed(float _speed){ m_fSpeed = _speed; }

	Vec GetPos() { return m_vPos; }
	Vec GetScale(){return m_vScale;}
	float GetSpeed() { return m_fSpeed;}

public:
	void Render(HDC _dc);
	void Update();

public:
	CPlayer();
	~CPlayer();
};

