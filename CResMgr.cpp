#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"

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

	pNewTex -> SetKey(_strKey);
	pNewTex->SetRelativePath(_strRelativePath);
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));

	return (CTexture*)pNewTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter =  m_mapTex.find(_strKey);
	
	if(iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}
