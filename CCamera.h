#pragma once

class CTexture;

enum class ECAM_EFFECT
{
	NONE,
	FADEIN,
	FADEOUT,
	VIBRATE,


	END
};

class CCamera
{
	SINGLE(CCamera)

private:
	Vec			m_vLookAt;
	Vec			m_vDiff;		// 해상도 중앙 지점과 카메라가 보고있는 지점 차이
	CTexture*	m_pVeilTex;

	// EFFECT
	ECAM_EFFECT m_eEffect;
	float		m_fEffectTime;
	float		m_fAddTime;		// 누적시간

	// EFFECT :: FADE
	float		m_fAlpha;		// 0 ~ 1

	// EFFECT :: VIBRATE
	float		m_fRange;
	float		m_fSpeed;
	EDIRECTION	m_eVibDir;
	Vec			m_vOriginLookAt;


public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	Vec GetRenderPos(Vec _vPos) { return _vPos - m_vDiff; }

public:
	void FadeIn(float _fTime)
	{
		m_eEffect = ECAM_EFFECT::FADEIN;
		m_fEffectTime = _fTime;
		m_fAlpha = 1.f;
		m_fAddTime = 0.f;
	}

	// 점점 어두워지는 효과
	void FadeOut(float _fTime)
	{
		m_eEffect = ECAM_EFFECT::FADEOUT;
		m_fEffectTime = _fTime;
		m_fAlpha = 0.f;
		m_fAddTime = 0.f;
	}

	// 진동 효과
	void Vibration(float _fRange/*진폭*/, float _fTime/*진동유지시간*/, float _fSpeed/*진동속도*/, EDIRECTION _dir /*진동방향*/)
	{
		m_eEffect = ECAM_EFFECT::VIBRATE;
		m_fRange = _fRange;
		m_fEffectTime = _fTime;
		m_fSpeed = _fSpeed;
		m_eVibDir = _dir;
		m_vOriginLookAt = m_vLookAt;
		m_fAddTime = 0.f;
	}
};

