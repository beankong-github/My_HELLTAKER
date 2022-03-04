#pragma once

class CObj;

// 게임 내의 모든 오브젝트 관리
class CStage
{
private:
	wstring			m_wstrStageName;
	vector<CObj*>	m_arrObj[(UINT)EOBJ_TYPE::END];

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _dc);
	
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	const wstring&		GetStageName()				{ return m_wstrStageName; }

protected:
	void SetStageName(wstring _str) { m_wstrStageName = _str; }

public:
	void					AddObject(CObj* _obj, EOBJ_TYPE _objType)	{ m_arrObj[(UINT)_objType].push_back(_obj);	}

	const vector<CObj*>&	GetObjects(EOBJ_TYPE _eType)				{ return m_arrObj[(UINT)_eType]; }
	CObj*					GetStageObject(EOBJ_TYPE _eType, const wstring& _strName);

	void Clear(EOBJ_TYPE _type);
	void Clear();

private:
	vector<CObj*>& GetObjectsRef(EOBJ_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CStage();
	virtual ~CStage();

	friend class CUIMgr;

};
