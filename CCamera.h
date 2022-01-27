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

struct tCamEffect
{
	ECAM_EFFECT eEffect;
	float		fEffectTime;
	float		fAddTime;

};

class CCamera
{
	SINGLE(CCamera)

private:
	Vec			m_vLookAt;
	Vec			m_vDiff;		// 해상도 중앙 지점과 카메라가 보고있는 지점 차이
	CTexture*	m_pVeilTex;
	
	list<tCamEffect> m_EffectQueue;	// 카메라 이펙트 큐

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
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::FADEIN;
		effect.fEffectTime = _fTime;
		effect.fAddTime = 0.f;
		m_fAlpha = 1.f;

		m_EffectQueue.push_back(effect);
	}

	// 점점 어두워지는 효과
	void FadeOut(float _fTime)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::FADEOUT;
		effect.fEffectTime = _fTime;
		effect.fAddTime = 0.f;
		m_fAlpha = 0.f;

		m_EffectQueue.push_back(effect);
	}

	// 진동 효과
	void Vibration(float _fRange/*진폭*/, float _fTime/*진동유지시간*/, float _fSpeed/*진동속도*/, EDIRECTION _dir /*진동방향*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::VIBRATE;
		effect.fEffectTime = _fTime;
		effect.fAddTime = 0.f;
		m_fRange = _fRange;
		m_fSpeed = _fSpeed;
		m_eVibDir = _dir;
		m_vOriginLookAt = m_vLookAt;

		m_EffectQueue.push_back(effect);
	}
};

