#pragma once

// 한번 만들어진 리소스가 중복되어 만들어지지 않도록 관리

class CTexture;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CTexture*>	 m_mapTex;
	map<wstring, CSound*>	 m_mapSound;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidthm, UINT _iHeight);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);

};

