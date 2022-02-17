#pragma once

class CComponent;
class CAnimator;
class CCollider;
class CFSM;

class CObj
{
private:
	wstring		m_strName;
	Vec			m_vPos;
	Vec			m_vScale;
	
	CComponent* m_arrCom[(UINT)ECOM_TYPE::END];

	bool		m_bDead;
	bool        m_bFlip;        // Filp image horizontally (T: left F:right)

public:
	void SetName(wstring _name)			{ m_strName = _name; }
	void SetPos(Vec _point)				{ m_vPos = _point; }
	void SetScale(Vec _point)			{ m_vScale = _point; }
	void SetFlip(bool _bFlip)			{ m_bFlip = _bFlip; }

	const wstring&	GetName()			{ return m_strName; }
	Vec				GetPos()			{ return m_vPos; }
	Vec				GetScale()			{ return m_vScale; }
	bool			IsFlip()			{ return m_bFlip; }
	
public:
	void		AddComponent(CComponent* _pCom);
	CComponent* GetComponent(ECOM_TYPE _eType)		{ return m_arrCom[(UINT)_eType];}
	CCollider*	GetCollider()						{ return (CCollider*)m_arrCom[(UINT)ECOM_TYPE::COLLIDER]; }
	CAnimator*	GetAnimator()						{ return (CAnimator*)m_arrCom[(UINT)ECOM_TYPE::ANIMATOR]; }
	CFSM*		GetFSM()							{ return (CFSM*)m_arrCom[(UINT)ECOM_TYPE::FSM]; }

	bool IsDead()								{ return m_bDead; }

	void Render_Component(HDC _dc);
	
public:
	virtual void Update() = 0;
	virtual void LateUpdate() final;
	virtual void Render(HDC _dc);


	virtual void OnCollisionEnter(CObj* _pOther);
	virtual void OnCollision(CObj* _pOther);
	virtual void OnCollisionExit(CObj* _pOther);

private:
	void SetDead(){	m_bDead = true;	}

public:
	CObj();
	virtual  ~CObj();

	friend class CEventMgr;
};

