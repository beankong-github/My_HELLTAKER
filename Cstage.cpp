#include "pch.h"
#include "CStage.h"
#include "CCore.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CBullet.h"

CStage::CStage()
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
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			m_vecObj[j][i]->Update();
		}
	}
}

void CStage::Render(HDC _dc)
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			m_vecObj[j][i]->Render(_dc);
		}
	}
}

void CStage::Clear()
{
	// 벡터 초기화
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			assert(m_vecObj[j][i]);
			delete m_vecObj[j][i];
		}
		m_vecObj[j].clear();
	}
	// 늘어난 백터 공간 줄이기
	// vector<CObj*> tempVec;
	// m_vecObj.swap(tempVec);
}
