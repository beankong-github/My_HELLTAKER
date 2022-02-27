#include "pch.h"
#include "CStage_Puzzle.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CBackGround.h"
#include "CUI_Counter.h"
#include "CTile.h"
#include "CTileMap.h"
#include "CHero.h"
#include "CNPC.h"
#include "CTransition.h"
#include "CObstacle.h"
#include "CRock.h"
#include "CUndead.h"


CStage_Puzzle::CStage_Puzzle(ECHAPTER _chap)
	: m_eChapter(_chap)
	, m_vTileCount{0, 0}
	, m_vTileStartPos{0, 0}
	, m_iInitMoveCount(0)
	, m_iCurMoveCount(0)
	, m_pTileMap(nullptr)
{
	if (ECHAPTER::NONE == _chap || ECHAPTER::END == _chap)
	{
		assert(nullptr);
	}

	SetStageName(L"CHAP_" + std::to_wstring((UINT)_chap));
	SetNPCName(m_eChapter);
}

void CStage_Puzzle::Enter()
{
	Init();
}


void CStage_Puzzle::Init()
{
	// Ʈ������ ����	
	m_pTransition = new CTransition;
	AddObject(m_pTransition, EOBJ_TYPE::TRANSITION);

	// UI ����
	CUI_Counter* pUI = new CUI_Counter();
	AddObject(pUI, EOBJ_TYPE::UI);

	// BG ����
	CBackGround* pBG = new CBackGround(m_eChapter);
	AddObject(pBG, EOBJ_TYPE::BG);

	// Ÿ�ϸ� ����
	CTileMap* pTileMap = new CTileMap; 
	pTileMap->Load(L"stage\\tilemap\\" + GetStageName() + L".tilemap");
	//pTileMap->CreateTile(m_vTileCount, m_vTileStartPos);
	//pTileMap->Save(L"stage\\");
	m_pTileMap = pTileMap;
	AddObject(pTileMap, EOBJ_TYPE::TILEMAP);

	//hero �߰�
	CHero* pHero = new CHero;
	pHero->SetCurTile(pTileMap->GetStartTile());
	pHero->SetPos(pTileMap->GetStartTile()->GetCenterPos());
	pHero->SetScale(Vec(100, 100));
	AddObject(pHero, EOBJ_TYPE::PLAYER);

	//npc �߰�
	map<Vec, CTile*>::iterator iter = pTileMap->GetTileMap()->begin();
	for (; iter != pTileMap->GetTileMap()->end(); ++iter)
	{
		if (ETILE_TYPE::NPC == iter->second->GetType())
		{
			if (!m_strNPCName.empty())
			{
				CNPC* pNPC = new CNPC(m_strNPCName);
				pNPC->SetPos(iter->second->GetCenterPos() + Vec{0, -30});
				pNPC->SetScale(Vec(100, 100));
				AddObject(pNPC, EOBJ_TYPE::NPC);
			}
		}
	}

	// �������� ���� �ε�
	// moveCount
	// ���� object��
	Load(L"stage\\puzzle\\" + GetStageName() + L".stage");
}

void CStage_Puzzle::Update()
{
	CStage::Update();

	// Ʈ�������� ����� ���� transition�� �����Ѵ�.
	if (nullptr != m_pTransition)
	{
		CAnimation* pAnimation = m_pTransition->GetAnimator()->GetCurAnimation();
		if (pAnimation->IsFinished())
		{
			DeleteObject(m_pTransition);
			m_pTransition = nullptr;
		}
	}
}

void CStage_Puzzle::Render(HDC _dc)
{
	CStage::Render(_dc);

#ifdef _DEBUG
	TextOut(_dc, 10, 10, GetStageName().c_str(), (int)GetStageName().size());
#endif // _DEBUG

}

void CStage_Puzzle::SetNPCName(ECHAPTER _eChap)
{
	// ���������� ���� NPC�� �̸��� �ٿ��ش�.
	switch (_eChap)
	{
	case ECHAPTER::CHAP_1:
		m_strNPCName = L"pandemonica";
		break;
	case ECHAPTER::CHAP_2:
		m_strNPCName = L"modeus";
		break;
	case ECHAPTER::CHAP_3:
		m_strNPCName = L"cerberus";
		break;
	case ECHAPTER::CHAP_4:
		m_strNPCName = L"malina";
		break;
	case ECHAPTER::CHAP_5:
		m_strNPCName = L"zdrada"; 
		break;
	case ECHAPTER::CHAP_6:
		m_strNPCName = L"azazel"; 
		break;
	case ECHAPTER::CHAP_7:
		m_strNPCName = L"justice";
		break;
	case ECHAPTER::CHAP_8:
		m_strNPCName = L"lucy";
		break;
	}
}

void CStage_Puzzle::PlayerMove(EDIRECTION _eDir)
{
	CHero* pHero = dynamic_cast<CHero*>(GetStageObject(EOBJ_TYPE::PLAYER, L"Hero"));

	if (nullptr != pHero)
	{
		// �÷��̾� �̵�
		pHero->Move(_eDir);
	}
}

void CStage_Puzzle::PlayerDead()
{
	for (UINT i = 0; i < (UINT)EOBJ_TYPE::END; i++)
	{
		if ((EOBJ_TYPE)i == EOBJ_TYPE::PLAYER)
			continue;
		CStage::Clear((EOBJ_TYPE)i);	
	}
}

void CStage_Puzzle::StageClear()
{
}

void CStage_Puzzle::Exit()
{
	CStage::Clear();
}

void CStage_Puzzle::Save(const wstring& _strRelativeFolderPath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += GetStageName();
	strFilePath += L".stage";

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
	//  �������� ������ �����ϱ�
	// =======================
	// �������� �̸�
	fwprintf_s(pFile, L"[TileMap_Stage_Name]\n");
	fwprintf_s(pFile, GetStageName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// ������ ����
	fwprintf_s(pFile, L"[Move_Count]\n");
	fwprintf_s(pFile, std::to_wstring(m_iInitMoveCount).c_str());
	fwprintf_s(pFile, L"\n\n");	
	
	// ���� ����
	//fwprintf_s(pFile, L"[Rock_Inform]\n");
	//fwprintf_s(pFile, L"[Rock_Count]\n");
	//fwprintf_s(pFile, std::to_wstring(m_iOBRockCount).c_str());
	//fwprintf_s(pFile, L"\n\n");

	//fwprintf_s(pFile, L"[Rock_Position]\n");
	//vector<CObj*> vecObs = GetObjects(EOBJ_TYPE::OBSTACLE);
	//for (size_t i = 0; i < vecObs.size(); i++)
	//{
	//	fwprintf_s(pFile, (L"[Rock_" + std::to_wstring(i) + L"]\n").c_str());
	//	CRock* pRock = dynamic_cast<CRock*>(vecObs[i]);
	//	if (nullptr != pRock)
	//	{
	//		Vec pos = pRock->GetCurTile()->GetIndex();

	//		fwprintf_s(pFile, std::to_wstring(pos.x).c_str());
	//		fwprintf_s(pFile, L"\n");	
	//		fwprintf_s(pFile, std::to_wstring(pos.y).c_str());
	//		fwprintf_s(pFile, L"\n\n");
	//	}
	//}



	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

void CStage_Puzzle::Load(const wstring& _strRelativeFilePath)
{
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
	//  �������� ������ �ε��ϱ�
	// =======================	
	wchar_t szBuff[256] = L"";

	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	SetStageName(szBuff);

	// �̵� Ƚ�� �ε�
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iInitMoveCount = (UINT)_wtoi(szBuff);
	m_iCurMoveCount = m_iInitMoveCount;
	
	// ���� ���� �ε�
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iOBRockCount = (UINT)_wtoi(szBuff);

	fwscanf_s(pFile, L"%s", szBuff, 256);
	for (size_t i = 0; i < m_iOBRockCount; i++)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);

		// ���� ��ǥ �ε�
		Vec vecTilePos = Vec{};
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.x = (float)_wtof(szBuff);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.y = (float)_wtof(szBuff);

		// ���� ����
		CTile* pTile = m_pTileMap->FindTile((UINT)vecTilePos.x, (UINT)vecTilePos.y);
		if (nullptr != pTile)
		{
			CRock* pRock = new CRock(pTile);
			pTile->AddObstacle(pRock);
			AddObject(pRock, EOBJ_TYPE::OBSTACLE);
		}
	}

	// �𵥵� ���� �ε�
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iOBUndeadCount = (UINT)_wtoi(szBuff);

	fwscanf_s(pFile, L"%s", szBuff, 256);
	for (size_t i = 0; i < m_iOBUndeadCount; i++)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);

		// �𵥵� ��ǥ �ε�
		Vec vecTilePos = Vec{};
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.x = (float)_wtof(szBuff);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.y = (float)_wtof(szBuff);

		// �𵥵� ����
		CTile* pTile = m_pTileMap->FindTile((UINT)vecTilePos.x, (UINT)vecTilePos.y);
		if (nullptr != pTile)
		{
			CUndead* pUndead = new CUndead(pTile);
			pTile->AddObstacle(pUndead);
			AddObject(pUndead, EOBJ_TYPE::OBSTACLE);
		}
	}
	
	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

CStage_Puzzle::~CStage_Puzzle()
{
}