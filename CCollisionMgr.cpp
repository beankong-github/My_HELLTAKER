#include "pch.h"
#include "CCollisionMgr.h"

#include "CStageMgr.h"
#include "Cstage.h"

#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{}

CCollisionMgr::~CCollisionMgr()
{}

void CCollisionMgr::Update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; j++)
		{
			// i 타입 오브젝트와 j 타입 오브젝트 충돌!
			if (m_arrCheck[i] & (1 << j))
			{
				// 충돌한 i 타입 오브젝트와 j 타입 오브젝트 배열을 가져와 충돌 검사
				CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
				CollisionGroup(pCurStage->GetObjects((EOBJ_TYPE)i), pCurStage->GetObjects((EOBJ_TYPE)j));
			}
		}
	}
}

void CCollisionMgr::CollisionGroup(const vector<CObj*>& _left, const vector<CObj*>& _right)
{
	CCollider* pLeftCol = nullptr;
	CCollider* pRightCol = nullptr;

	for (size_t i = 0; i < _left.size(); ++i)
	{
		pLeftCol = _left[i]->GetCollider();
		// 오브젝트에 콜라이더가 없다면 또는 Dead 상태라면
		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < _right.size(); ++j)
		{
			pRightCol = _right[j]->GetCollider();
			// 오브젝트에 콜라이더가 없다면 또는 Dead 상태라면
			if (nullptr == pRightCol)
				continue;

			// 두 충돌체가 이전에 충돌했었는지 검사
			// 두 충돌체의 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeftID = pLeftCol->GetID();
			ID.iRightID = pRightCol->GetID();
			map<LONGLONG, bool> ::iterator iter = m_mapColInfo.find(ID.id);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.id, false));
				iter = m_mapColInfo.find(ID.id);
			}

			// 둘 중 하나라도 Dead 인지 체크
			bool bDead = pRightCol->GetOwner()->IsDead() || pLeftCol->GetOwner()->IsDead();

			// 충돌 검사
			if (IsCollision(pLeftCol, pRightCol))
			{
			// 충돌 O
				// 이전 프레임에도 충돌 중이었다.
				if (iter->second)	
				{
					// 둘 중 한 오브젝트가 Dead 일 경우
					if (bDead)
					{
						// 두 collider에게 충돌 종료 알림
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						m_mapColInfo.erase(iter);
					}
					else
					{
						// 두 collider에게 충돌 알림
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol); 
					}
				}

				// 이전 프레임에는 충돌하지 않았다.
				else
				{
					// 두 collider에게 충돌 시작 알림
					if (!bDead)
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					else
					{
						m_mapColInfo.erase(iter);
					}
				}

			}
			
			// 충돌 x
			else
			{
				// 충돌이 아닐 경우
				// 이전 프레임까지는 충돌중이었다
				if (iter->second)
				{
					// 두 collider에게 충돌 종료 알림
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				if (bDead)
				{
					m_mapColInfo.erase(iter);
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _left, CCollider* _right)
{
	Vec vLColPos =  _left->GetFinalPos();
	Vec vLColScale = _left->GetScale();

	Vec vRColPos = _right->GetFinalPos();
	Vec vRColScale = _right->GetScale();

	float fDist = 0.f;

	// x축 충돌 테스트
	fDist = abs(vLColPos.x - vRColPos.x);
	if (fDist > abs(vLColScale.x / 2 + vRColScale.x / 2))
	{
		//안겹친다
		return false;
	}

	// y축 충돌 테스트
	fDist = abs(vLColPos.y - vRColPos.y);
	if (fDist > abs(vLColScale.y / 2 + vRColScale.y / 2))
	{
		//안겹친다
		return false;
	}

	return true;
}

void CCollisionMgr::CollisionOn(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	// Left와 Right 중 더 큰 값을 열로 활용한다
	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionOff(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	// Left와 Right 중 더 큰 값을 열로 활용한다
	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] &= ~(1 << iCol);
}
