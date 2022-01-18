#pragma once

class CObj;

class CComponent
{
private:
	ECOM_TYPE	m_eType;	// 컴포넌트 타입 값
	CObj*		m_pOwer;	// 컴포넌트를 소유하고 있는 본체 오브젝트 주소

public: 
	ECOM_TYPE GetType() { return m_eType; }
	CObj* GetOwner() { return m_pOwer; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC _dc);

public:
	CComponent(ECOM_TYPE _eType);
	~CComponent();

	friend class CObj;
};

