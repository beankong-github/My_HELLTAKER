#include "pch.h"
#include "CRock.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTile.h"

int iPingpong = 1;

CRock::CRock(CTile* _pTile)
	: CObstacle(_pTile)
	, m_fEffectTime(1.f)
	, m_fAddTime(0.f)
	, m_pCurTex(nullptr)
	, m_vecTextures()
{	
	// 랜덤으로 텍스처 구하기
	for (size_t i = 1; i <= 8; i++)
	{
		CTexture* pRockTex = CResMgr::GetInst()->LoadTexture(L"rock_" + std::to_wstring(i), L"texture\\object\\rock\\rock_" + std::to_wstring(i) + L".bmp");

		m_vecTextures.push_back(pRockTex);
	}
	
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(0, 7);

	// 난수 생성
	m_pCurTex = m_vecTextures[dis(gen)];

	// 현재 위치 설정
	Vec vecPos = Vec{};
	vecPos.x = GetCurTile()->GetCenterPos().x - m_pCurTex->Width() / 2;
	vecPos.y = GetCurTile()->GetCenterPos().y - m_pCurTex->Height() / 2 + 10.f;
	SetPos(vecPos);
}

CRock::~CRock()
{
}
void CRock::Update()
{
	EOBSTACLE_STATE eCurState = GetState();

	switch (eCurState)
	{
	case EOBSTACLE_STATE::IDLE:
		break;
	case EOBSTACLE_STATE::MOVE:
		break;
	case EOBSTACLE_STATE::KICKED:
		Shake();
		break;
	case EOBSTACLE_STATE::DEAD:
		break;
	case EOBSTACLE_STATE::END:
		break;
	default:
		break;
	}
}

void CRock::Render(HDC _dc)
{
	if (nullptr != m_pCurTex)
	{
		TransparentBlt(_dc
			, (int)GetPos().x
			, (int)GetPos().y
			, m_pCurTex->Width()
			, m_pCurTex->Height()
			, m_pCurTex->GetDC()
			, 0, 0
			, m_pCurTex->Width()
			, m_pCurTex->Height()
			, RGB(112, 12, 41)
		);
	}
}

void CRock::TryMove()
{
}

void CRock::Move(EDIRECTION _eDir)
{
}

void CRock::Shake()
{
	// 원래 위치 구하기
	Vec OriginPos = Vec{};
	OriginPos.x = GetCurTile()->GetCenterPos().x - m_pCurTex->Width() / 2;
	OriginPos.y = GetCurTile()->GetCenterPos().x - m_pCurTex->Height() / 2 + 10.f;

	if (m_fEffectTime <= m_fAddTime)
	{  
		SetPos(OriginPos + iPingpong * 3.f);
	}

	else
	{
		// 원위치
		SetPos(OriginPos);

		// AddTime 초기화
		m_fAddTime = 0.f;
	}
}

