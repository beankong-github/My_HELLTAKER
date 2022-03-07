#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CSoundMgr.h"

#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
	m_mapTex.clear();

	map<wstring, CSound*>::iterator iter_2 = m_mapSound.begin();
	for (; iter_2 != m_mapSound.end(); ++iter_2)
	{
		delete iter_2->second;
	}
	m_mapSound.clear();
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 리소스 중복 체크
	CResource* pNewTex = FindTexture(_strKey);

	if (nullptr != pNewTex)
		return (CTexture*)pNewTex;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 중복된 리소스가 없으면
	pNewTex = new CTexture;

	if (FAILED(pNewTex->Load(strFilePath)))
	{
		// Load 실패
		return nullptr;
	}

	pNewTex-> SetKey(_strKey);
	pNewTex-> SetRelativePath(_strRelativePath);
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));

	return (CTexture*)pNewTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{	
	// 리소스 중복 체크
	CTexture* pNewTex = FindTexture(_strKey);

	if (nullptr != pNewTex)
		return pNewTex;
	
	// 텍스처 생성
	pNewTex = new CTexture;
	pNewTex-> Create(_iWidth, _iHeight);
	
	pNewTex->SetKey(_strKey);
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));
	
	return pNewTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter =  m_mapTex.find(_strKey);
	
	if(iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	if (nullptr != FindSound(_strKey))
		return FindSound(_strKey);

	CSound* pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}