#pragma once
class CResource
{
private:
	wstring m_strKey;			// 리소스 키값
	wstring m_strRelativePath;	// 리소스 상대 경로

public:
	void SetKey(const wstring _strKey){	m_strKey = _strKey;	}
	void SetRelativePath(const wstring _strPath) { m_strRelativePath = _strPath; }
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

private:
	virtual int Load(const wstring& _strFullPath) = 0;

public:
	CResource();
	virtual ~CResource();

	friend class CResMgr;

};

