#include "pch.h"
#include "CTileMap.h"

#include "CCore.h"
#include "CPathMgr.h"

#include "CStageMgr.h"
#include "CStage.h"

#include "CTile.h"

CTileMap::CTileMap()
{
	m_strStageName = CStageMgr::GetInst()->GetCurStage()->GetStageName();
}

CTileMap::~CTileMap()
{
	ClearTileMap();
}

void CTileMap::CreateTile(UINT _iCol, UINT _iRow, Vec _vPos)
{
	m_vSize = Vec(_iCol, _iRow);
	m_vPos = _vPos;

	// ���� ���������� Ÿ���� ��� �����
	ClearTileMap();

	// Ÿ�� ����
	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetScale(Vec{ (float)TILE_SIZE, (float)TILE_SIZE });
			pTile->SetPos(Vec{ _vPos.x + (float)(iCol * TILE_SIZE), _vPos.y + (float)(iRow * TILE_SIZE) });

			m_mTileMap.insert(make_pair( Vec(iCol, iRow), pTile ));
		}
	}
}

void CTileMap::CreateTile(Vec _vSize, Vec _vPos)
{	
	m_vSize = _vSize;
	m_vPos = _vPos;

	// ���� ���������� Ÿ���� ��� �����
	ClearTileMap();

	// Ÿ�� ����
	for (UINT iRow = 0; iRow < _vSize.y; ++iRow)
	{
		for (UINT iCol = 0; iCol < _vSize.x; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetScale(Vec{ (float)TILE_SIZE, (float)TILE_SIZE });
			pTile->SetPos(Vec{ _vPos.x + (float)(iCol * TILE_SIZE), _vPos.y + (float)(iRow * TILE_SIZE) });

			m_mTileMap.insert(make_pair(Vec(iCol, iRow), pTile));
		}
	}
}

void CTileMap::ClearTileMap()
{
	map<Vec, CTile*>::iterator iter = m_mTileMap.begin();
	for (; iter != m_mTileMap.end(); ++iter)
	{
		delete iter->second;
	}
	m_mTileMap.clear();
}

void CTileMap::Update()
{
	map<Vec, CTile*>::iterator iter = m_mTileMap.begin();
	for (; iter != m_mTileMap.end(); ++iter)
	{
		iter->second->Update();
		iter->second->LateUpdate();
	}
}


void CTileMap::Render(HDC _dc)
{
	map<Vec, CTile*>::iterator iter = m_mTileMap.begin();
	for (; iter != m_mTileMap.end(); ++iter)
	{
		iter->second->Render(_dc);
	}
}


void CTileMap::Save(const wstring& _strRelativeFolderPath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += m_strStageName;
	strFilePath += L".tilemap";

	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// ���� ������ ������ �ּҰ��� �޾ư��� ������ �ּҸ� �������ش�.
	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"Ÿ�� �� ���� ����", MB_OK);
	
		return;
	}

	// =======================
	//  Ÿ�ϸ� ������ �����ϱ�
	// =======================

	// �������� �̸�
	fwprintf_s(pFile, L"[TileMap_Stage_Name]\n");
	fwprintf_s(pFile, m_strStageName.c_str());
	fwprintf_s(pFile, L"\n\n");

	// Ÿ�ϸ� ���� ���� ����
	fwprintf_s(pFile, L"[TileMap_Size]\n");
	fwprintf_s(pFile, std::to_wstring(m_vSize.x).c_str());
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, std::to_wstring(m_vSize.y).c_str());
	fwprintf_s(pFile, L"\n\n");

	// Ÿ�ϸ� ��ġ
	fwprintf_s(pFile, L"[TileMap_Position]\n");
	fwprintf_s(pFile, std::to_wstring(m_vPos.x).c_str());
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, std::to_wstring(m_vPos.y).c_str());
	
	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

void CTileMap::Load(const wstring& _strRelativeFilePath)
{
	ClearTileMap();

	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;


	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// �ش� ����� ������ �б� ���� ���� ���� ������ ������ �ּҰ��� ������ �ּҸ� �������ش�.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"Ÿ�ϸ� �ε� ����", MB_OK);

		return;
	}

	// =======================
	// Ÿ�ϸ� ������ �о����
	// =======================

	// Ÿ�� �� �̸�
	wchar_t szBuff[256] = L"";
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_strStageName = szBuff;

	// Ÿ�� ũ��
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring size_x = szBuff;
	m_vSize.x =	(float)_wtof(size_x.c_str());

	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring size_y = szBuff;
	m_vSize.y = (float)_wtof(size_y.c_str());

	// Ÿ��  ��ġ
	// �� ������ ����
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring pos_x = szBuff;
	m_vPos.x = (float)_wtof(pos_x.c_str());

	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring pos_y = szBuff;
	m_vPos.y = (float)_wtof(pos_y.c_str());
	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);

	CreateTile(m_vSize, m_vPos);
}