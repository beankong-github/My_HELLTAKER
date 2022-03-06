#include "pch.h"
#include "CStage.h"

#include "CCore.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CTile.h"

CStage::CStage()
	:m_wstrStageName()
{
}

CStage::~CStage()
{
	Clear();
}


void CStage::Update()
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_arrObj[j].size(); i++)
		{
			if (m_arrObj[j][i]->IsDead())
				continue;

			m_arrObj[j][i]->Update();
		}
	}
}

void CStage::LateUpdate()
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_arrObj[j].size(); i++)
		{
			if (m_arrObj[j][i]->IsDead())
				continue;

			m_arrObj[j][i]->LateUpdate();
		}
	}
}

void CStage::Render(HDC _dc)
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		vector<CObj*>::iterator iter = m_arrObj[j].begin();

		for (; iter != m_arrObj[j].end();)
		{
			// 오브젝트가 Dead 상태면 오브젝트 배열에서 삭제한다
			if ((*iter)->IsDead())
				iter = m_arrObj[j].erase(iter);

			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}

CObj* CStage::GetStageObject(EOBJ_TYPE _eType, const wstring& _strName)
{
	for (UINT i = 0; i < m_arrObj[(UINT)_eType].size(); i++)
	{
		if (_strName == m_arrObj[(UINT)_eType][i]->GetName())
			return m_arrObj[(UINT)_eType][i];
	}

	return nullptr;
}

void CStage::Clear(EOBJ_TYPE _type)
{
	vector<CObj*>& vecObj = m_arrObj[(UINT)_type];
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		delete vecObj[i];
	}

	vecObj.clear();
}

void CStage::Clear()
{
	// 벡터 초기화
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_arrObj[j].size(); i++)
		{
			assert(m_arrObj[j][i]);
			delete m_arrObj[j][i];
		}
		m_arrObj[j].clear();
	}
	// 늘어난 백터 공간 줄이기
	// vector<CObj*> tempVec;
	// m_vecObj.swap(tempVec);
}

void CStage::FirstOptionSelected()
{
}

void CStage::SecondOptionSelected()
{
}

void CStage::DialogTermination()
{
}
