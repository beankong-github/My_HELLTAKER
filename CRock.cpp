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
	// �������� �ؽ�ó ���ϱ�
	for (size_t i = 1; i <= 8; i++)
	{
		CTexture* pRockTex = CResMgr::GetInst()->LoadTexture(L"rock_" + std::to_wstring(i), L"texture\\object\\rock\\rock_" + std::to_wstring(i) + L".bmp");

		m_vecTextures.push_back(pRockTex);
	}
	
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> dis(0, 7);

	// ���� ����
	m_pCurTex = m_vecTextures[dis(gen)];

	// ���� ��ġ ����
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
	// ���� ��ġ ���ϱ�
	Vec OriginPos = Vec{};
	OriginPos.x = GetCurTile()->GetCenterPos().x - m_pCurTex->Width() / 2;
	OriginPos.y = GetCurTile()->GetCenterPos().x - m_pCurTex->Height() / 2 + 10.f;

	if (m_fEffectTime <= m_fAddTime)
	{  
		SetPos(OriginPos + iPingpong * 3.f);
	}

	else
	{
		// ����ġ
		SetPos(OriginPos);

		// AddTime �ʱ�ȭ
		m_fAddTime = 0.f;
	}
}

