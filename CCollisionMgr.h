#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	UINT m_arrCheck[MAX_LAYER];

public:
	void Update();

public:
	void CollisionOn(EOBJ_TYPE _left, EOBJ_TYPE _right);
	void CollisionOff(EOBJ_TYPE _left, EOBJ_TYPE _right);

private:
	void CollisionGroup(const vector<CObj*>& _left, const vector<CObj*>& _right);
	bool IsCollision(CCollider* _left, CCollider* _right);

};

