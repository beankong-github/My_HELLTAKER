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
	// ī�޶� ��ġ�� ȭ�� ���߾����� ����
	Vec vResolution = CCore::GetInst()->GetResolution();
	m_vLookAt = vResolution / 2.f;

	// ���̵忡 ����� �帷 �ؽ�ó ����
	if (nullptr == m_pVeilTex)
	{
		m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"Veil", (UINT)vResolution.x, (UINT)vResolution.y);

		// ���������� ���� (������ �ؽ�ó �ʱⰪ�� �������̶� �ʿ�x)
		//for (UINT i = 0; i < (UINT)vResolution.y; i++)
		//{
		//	for (UINT j = 0; j < (UINT)vResolution.x; j++)
		//	{
		//		// veil �ؽ�ó�� ��� �ȼ��� ���������� ĥ�Ѵ�.
		//		SetPixel(m_pVeilTex->GetDC(), j, i, RGB(0, 0, 0)); 
		//	}
		//}
	}
}

void CCamera::Update()
{
	//// Ű �Է¿� ���� ī�޶� �̵�
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

	// �ػ� �߾Ӱ� ���ϱ�
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

		// ����Ʈ �ð��� �ʰ��� ���
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

