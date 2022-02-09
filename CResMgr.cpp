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
	// ���ҽ� �ߺ� üũ
	CResource* pNewTex = FindTexture(_strKey);

	if (nullptr != pNewTex)
		return (CTexture*)pNewTex;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// �ߺ��� ���ҽ��� ������
	pNewTex = new CTexture;

	if (FAILED(pNewTex->Load(strFilePath)))
	{
		// Load ����
		return nullptr;
	}

	pNewTex-> SetKey(_strKey);
	pNewTex-> SetRelativePath(_strRelativePath);
	m_mapTex.insert(make_pair(_strKey, (CTexture*)pNewTex));

	return (CTexture*)pNewTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{	
	// ���ҽ� �ߺ� üũ
	CTexture* pNewTex = FindTexture(_strKey);

	if (nullptr != pNewTex)
		return pNewTex;
	
	// �ؽ�ó ����
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
