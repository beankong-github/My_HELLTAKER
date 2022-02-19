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
	Vec			m_vDiff;		// �ػ� �߾� ������ ī�޶� �����ִ� ���� ����
	CTexture*	m_pVeilTex;
	
	list<tCamEffect> m_EffectQueue;	// ī�޶� ����Ʈ ť

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
	Vec GetOriginalPos(Vec _vPos) { return m_vLookAt + _vPos; }
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

	// ���� ��ο����� ȿ��
	void FadeOut(float _fTime)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::FADEOUT;
		effect.fEffectTime = _fTime;
		effect.fAddTime = 0.f;
		m_fAlpha = 0.f;

		m_EffectQueue.push_back(effect);
	}

	// ���� ȿ��
	void Vibration(float _fRange/*����*/, float _fTime/*���������ð�*/, float _fSpeed/*�����ӵ�*/, EDIRECTION _dir /*��������*/)
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

