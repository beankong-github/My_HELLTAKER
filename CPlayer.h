#pragma once
#include "CObj.h"

class CTexture;

class CPlayer
	: public CObj
{
private:
	float		m_fSpeed;		// �ʴ�  �̵� �ȼ�
	CTexture*	 m_pTex;		// �÷��̾��� �̹���

public:
	void SetSpeed(float _speed){ m_fSpeed = _speed; }
	float GetSpeed() { return m_fSpeed;}

public:
	void Update();
	void Render(HDC _dc);

	void OnCollisionEnter(CObj* _pOther) override;
	void OnCollision(CObj* _pOther) override;
	void OnCollisionExit(CObj* _pOther) override;

public:
	CPlayer();
	virtual ~CPlayer();
};

