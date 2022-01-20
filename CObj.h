#pragma once

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CFSM.h"

class CComponent;

class CObj
{
private:
	wstring		m_strName;
	Vec			m_vPos;
	Vec			m_vScale;
	
	CComponent* m_arrCom[(UINT)ECOM_TYPE::END];

	bool		m_bDead;

public:
	void SetName(wstring _name)					{ m_strName = _name; }
	void SetPos(Vec _point)						{ m_vPos = _point; }
	void SetScale(Vec _point)					{ m_vScale = _point; }

	const wstring& GetName()					{ return m_strName; }
	Vec GetPos()								{ return m_vPos; }
	Vec GetScale()								{ return m_vScale; }

	void AddComponent(CComponent* _pCom);
	CComponent* GetComponent(ECOM_TYPE _eType)	{ return m_arrCom[(UINT)_eType]; }
	CCollider* GetCollider()					{ return (CCollider*)m_arrCom[(UINT)ECOM_TYPE::COLLIDER]; }
	CAnimator* GetAnimator()					{ return (CAnimator*)m_arrCom[(UINT)ECOM_TYPE::ANIMATOR]; }
	CFSM* GetFSM()								{ return (CFSM*)m_arrCom[(UINT)ECOM_TYPE::FSM]; }

	bool isDead()								{ return m_bDead; }

	
public:
	virtual void Update() = 0;
	virtual void LateUpdate() final;
	virtual void Render(HDC _dc);

	void Render_Component(HDC _dc);

private:
	void SetDead(){	m_bDead = true;	}

public:
	CObj();
	virtual  ~CObj();

	friend class CEventMgr;
};

