#include "pch.h"
#include "CBullet.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"

CBullet::CBullet()
	: m_fSpeed(400.f)
	, m_fAddTime(0.f)
	, m_fTailAddTime(0.f)
	, m_pTex(nullptr)
	
{
	// 충돌체 생성
	CCollider* pCol = new CCollider;
	pCol->SetOffsetPos(Vec(0.f, 0.f));
  	pCol->SetScale(Vec(20.f, 20.f));
	AddComponent(pCol);

	// 텍스처 로드
	m_pTex = CResMgr::GetInst()->LoadTexture(L"EnergyBall", L"texture\\EnergyBall.bmp");


}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	// 총알 꼬리 업데이트
	m_fTailAddTime += DS;
	if (m_fTailAddTime > 0.003f)		// 0.02초마다 Tail Update
	{
		m_listTailInfo.push_front(tTailInfo{ GetPos(), CTimeMgr::GetInst()->GetCurTime() });	// 오래된 것일 수록 리스트의 뒤로 밀린다
		m_fTailAddTime = 0.f;
	}

	// 시간에 따라 총알 총알 상승
	Vec Pos = GetPos();
	Pos.y -= m_fSpeed * DS;
	SetPos(Pos);

	// 2초 뒤면 총알 삭제
	m_fAddTime += DS;
	if (m_fAddTime >= 4.f)
	{
		DeleteObject(this);
	}
}

void CBullet::Render(HDC _dc)
{
	// 꼬리 펜 브러쉬 생성
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(66, 198, 255));
	HBRUSH hBrush = CreateSolidBrush(RGB(66, 198, 255));

	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec vTailScale = Vec(23.f, 2.f);

	// 총알 꼬리 렌더링
	float fCurTime = CTimeMgr::GetInst()->GetCurTime();
	list<tTailInfo>::iterator iter = m_listTailInfo.begin();

	float i = 0.f;

	for (;iter !=  m_listTailInfo.end();)
	{
		if (fCurTime >= iter->fLifeTime + 0.3f)	// 꼬리가 0.3초 이상 지난 것들은 삭제
		{
			iter = m_listTailInfo.erase(iter);
		}
		else
		{
			Vec vCurScale = vTailScale - i;

			if (vCurScale.x < 0)
			{
				vCurScale.x = 0;
			}

			// 꼬리 그리기
			Rectangle(_dc
				, int(iter->vPos.x - vCurScale.x / 2.f)
				, int(iter->vPos.y - vCurScale.y / 2.f)
				, int(iter->vPos.x + vCurScale.x / 2.f)
				, int(iter->vPos.y + vCurScale.y / 2.f));

			++iter;
		}
		i += 0.5f;
	}

	// 꼬리 펜, 브러쉬 삭제
	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	// 총알 렌더링
	Vec vPos = GetPos();
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(255, 0, 255));


#ifdef _DEBUG
	Render_Component(_dc);
#endif
}

