#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CStageMgr.h"
#include "CTexture.h"

int iVibSwitch = 1;

CCamera::CCamera()
	: m_pVeilTex(nullptr)
	, m_vDiff()
	, m_vLookAt()
	, m_fAlpha(0)
	, m_fRange(0)
	, m_fSpeed(0)
	, m_eVibDir(EDIRECTION::HORIZIONTAL)
{
}

CCamera::~CCamera()
{}

void CCamera::Init()
{
	// 카메라 위치를 화면 정중앙으로 설정
	Vec vResolution = CCore::GetInst()->GetResolution();
	m_vLookAt = vResolution / 2.f;

	// 페이드에 사용할 장막 텍스처 생성
	if (nullptr == m_pVeilTex)
	{
		m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"Veil", (UINT)vResolution.x, (UINT)vResolution.y);

		// 검은색으로 설정 (생성된 텍스처 초기값이 검은색이라 필요x)
		//for (UINT i = 0; i < (UINT)vResolution.y; i++)
		//{
		//	for (UINT j = 0; j < (UINT)vResolution.x; j++)
		//	{
		//		// veil 텍스처의 모든 픽셀을 검은색으로 칠한다.
		//		SetPixel(m_pVeilTex->GetDC(), j, i, RGB(0, 0, 0)); 
		//	}
		//}
	}
}

void CCamera::Update()
{
	//// 키 입력에 따라 카메라 이동
	//if (IS_KEY_PRESSED(KEY::UP))
	//{
	//	m_vLookAt.y += DS * 200.f;
	//}

	//if (IS_KEY_PRESSED(KEY::DOWN))
	//{
	//	m_vLookAt.y -= DS * 200.0f;
	//}

	//if (IS_KEY_PRESSED(KEY::LEFT))
	//{
	//	m_vLookAt.x -= DS * 200.f;
	//}
	//if (IS_KEY_PRESSED(KEY::RIGHT))
	//{
	//	m_vLookAt.x += DS * 200.f;
	//}

	// 해상도 중앙값 구하기
	Vec vCenter = CCore::GetInst()->GetResolution();
	vCenter /= 2.f;
	m_vDiff = m_vLookAt - vCenter;
	
}

void CCamera::Render(HDC _dc)
{
	while (true)
	{
		if (m_EffectQueue.empty())
			return;

		tCamEffect& effect = m_EffectQueue.front();
		effect.fAddTime += DS;

		// 이펙트 시간이 초과된 경우
		if (effect.fAddTime > effect.fEffectTime)
		{
			if (ECAM_EFFECT::VIBRATE == effect.eEffect)
				m_vLookAt = m_vOriginLookAt;

			m_EffectQueue.pop_front();
		}
		else
			break;
	}

	tCamEffect& effect = m_EffectQueue.front();

	// ============================
	//			Vibration
	// ============================

	if (ECAM_EFFECT::VIBRATE == effect.eEffect)
	{
		if (EDIRECTION::VERTICAL == m_eVibDir)
		{
			if ((m_vOriginLookAt.y + m_fRange) < m_vLookAt.y)
				iVibSwitch = -1;
			else if ((m_vOriginLookAt.y - m_fRange) > m_vLookAt.y)
				iVibSwitch = 1;

			m_vLookAt.y += iVibSwitch * m_fRange * m_fSpeed * DS;
		}
		if (EDIRECTION::HORIZIONTAL == m_eVibDir)
		{
			if ((m_vOriginLookAt.x + m_fRange) < m_vLookAt.x)
				iVibSwitch = -1;
			else if ((m_vOriginLookAt.x - m_fRange) > m_vLookAt.x)
				iVibSwitch = 1;

			m_vLookAt.x += iVibSwitch * m_fRange * m_fSpeed * DS;
		}

		return;
	}


	// ============================
	//		PADEIN / PADEOUT
	// ============================
	
	if (ECAM_EFFECT::FADEOUT == effect.eEffect)
	{
		m_fAlpha = effect.fAddTime / effect.fEffectTime;
	}
	else if (ECAM_EFFECT::FADEIN == effect.eEffect)
	{
		m_fAlpha = 1.f - (effect.fAddTime / effect.fEffectTime);
	}

	UINT iWidth = m_pVeilTex->Width();
	UINT iHeight = m_pVeilTex->Height();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(255 * m_fAlpha);
	bf.AlphaFormat = 0;

	if (m_fAlpha <= 0.f)
		return;

	AlphaBlend(_dc, 0, 0, iWidth, iHeight, m_pVeilTex->GetDC(), 0, 0, iWidth, iHeight, bf);
}

