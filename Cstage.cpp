#include "pch.h"
#include "CStage.h"

#include "CCore.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CTile.h"

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
			// ������Ʈ�� Dead ���¸� ������Ʈ �迭���� �����Ѵ�
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

void CStage::CreateTile(UINT _iCol, UINT _iRow)
{
	Clear(EOBJ_TYPE::TILE);

	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetScale(Vec{ (float)TILE_SIZE, (float)TILE_SIZE });
			pTile->SetPos(Vec{ (float)(iCol * TILE_SIZE), (float)(iRow * TILE_SIZE) });

			AddObject(pTile, EOBJ_TYPE::TILE);
		}
	}
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
	// ���� �ʱ�ȭ
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_arrObj[j].size(); i++)
		{
			assert(m_arrObj[j][i]);
			delete m_arrObj[j][i];
		}
		m_arrObj[j].clear();
	}
	// �þ ���� ���� ���̱�
	// vector<CObj*> tempVec;
	// m_vecObj.swap(tempVec);
}
