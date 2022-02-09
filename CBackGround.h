#pragma once
#include "CObj.h"
class CBackGround :
    public CObj
{
private:
	ECHAPTER	m_eChap;	
	CTexture*	m_pTex;		// 플레이어의 이미지

public:
	ECHAPTER GetChapter() { return m_eChap; }

public:
	virtual void Update();
	void Render(HDC _dc);

	void OnCollisionEnter(CObj* _pOther) override;
	void OnCollision(CObj* _pOther) override;
	void OnCollisionExit(CObj* _pOther) override;

public:
	CBackGround(ECHAPTER _chap);
	virtual ~CBackGround();
};

