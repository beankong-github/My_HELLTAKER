#pragma once

class CTexture;
class CAnimator;
class CObj;

struct tAnimFrm
{
	CTexture*	pTex;
	wstring		strName;
	wstring		strRelativeTexPath;
	Vec			vSize;
	float		fDuration;
};

class CAnimation
{
private:
	CAnimator*			m_pAnimator;
	wstring				m_strName;

	CTexture*			m_pAtlas;
	vector<tAnimFrm>	m_vecFrm;
	int					m_iCuridx;
	float				m_fAddTime;
	bool				m_bFinish;

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinished() { return m_bFinish; }
	CObj* GetOwner();
	
	void Save(const wstring& _strRelativeFolderPath);
	void Load(const wstring& _strRelativeFilePath);

private:
	void Create(const wstring& _strAnimName, const wstring& _strRelativePath, float _fDuration, UINT _iFrmCount);
	void Reset();

public:
	void Update();
	void Render(HDC _dc);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

