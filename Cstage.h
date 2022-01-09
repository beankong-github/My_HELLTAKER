#pragma once

class CObj;

// 게임 내의 모든 오브젝트 관리
class CStage
{
private:
	vector<CObj*> m_vecObj;

public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	void AddObject(CObj* _obj)
	{
		m_vecObj.push_back(_obj);
	}

	//const CObj* GetObject(wstring _name)
	//{
	//	for (size_t i = 0; i < m_vecObj.size(); i++)
	//	{
	//		if (_name == m_vecObj[i]->GetName())
	//		{
	//			return m_vecObj[i];
	//		}
	//	}
	//}

public:
	CStage();
	~CStage();

};
