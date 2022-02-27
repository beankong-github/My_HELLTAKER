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
	// 트랜지션 생성	
	m_pTransition = new CTransition;
	AddObject(m_pTransition, EOBJ_TYPE::TRANSITION);

	// UI 생성
	CUI_Counter* pUI = new CUI_Counter();
	AddObject(pUI, EOBJ_TYPE::UI);

	// BG 생성
	CBackGround* pBG = new CBackGround(m_eChapter);
	AddObject(pBG, EOBJ_TYPE::BG);

	// 타일맵 생성
	CTileMap* pTileMap = new CTileMap; 
	pTileMap->Load(L"stage\\tilemap\\" + GetStageName() + L".tilemap");
	//pTileMap->CreateTile(m_vTileCount, m_vTileStartPos);
	//pTileMap->Save(L"stage\\");
	m_pTileMap = pTileMap;
	AddObject(pTileMap, EOBJ_TYPE::TILEMAP);

	//hero 추가
	CHero* pHero = new CHero;
	pHero->SetCurTile(pTileMap->GetStartTile());
	pHero->SetPos(pTileMap->GetStartTile()->GetCenterPos());
	pHero->SetScale(Vec(100, 100));
	AddObject(pHero, EOBJ_TYPE::PLAYER);

	//npc 추가
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

	// 스테이지 정보 로드
	// moveCount
	// 각종 object들
	Load(L"stage\\puzzle\\" + GetStageName() + L".stage");
}

void CStage_Puzzle::Update()
{
	CStage::Update();

	// 트렌지션이 종료된 이후 transition을 삭제한다.
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
	// 스테이지에 따라 NPC의 이름을 붙여준다.
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
		// 플레이어 이동
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
	//	파일 경로 찾기
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += GetStageName();
	strFilePath += L".stage";

	// ===============
	//	  파일 열기
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// 파일 포인터 변수의 주소값을 받아가서 파일의 주소를 저장해준다.
	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"타일 맵 저장 오류", MB_OK);

		return;
	}

	// =======================
	//  스테이지 데이터 저장하기
	// =======================
	// 스테이지 이름
	fwprintf_s(pFile, L"[TileMap_Stage_Name]\n");
	fwprintf_s(pFile, GetStageName().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 움직임 갯수
	fwprintf_s(pFile, L"[Move_Count]\n");
	fwprintf_s(pFile, std::to_wstring(m_iInitMoveCount).c_str());
	fwprintf_s(pFile, L"\n\n");	
	
	// 바위 정보
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
	//	  파일 닫기
	// ===============
	fclose(pFile);
}

void CStage_Puzzle::Load(const wstring& _strRelativeFilePath)
{
	// ===============
	//	절대 경로 찾기
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;


	// ===============
	//	  파일 열기
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// 해당 경로의 파일을 읽기 모드로 열어 파일 포인터 변수의 주소값에 파일의 주소를 저장해준다.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"타일맵 로딩 오류", MB_OK);

		return;
	}
	// =======================
	//  스테이지 데이터 로드하기
	// =======================	
	wchar_t szBuff[256] = L"";

	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	SetStageName(szBuff);

	// 이동 횟수 로드
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iInitMoveCount = (UINT)_wtoi(szBuff);
	m_iCurMoveCount = m_iInitMoveCount;
	
	// 바위 정보 로드
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iOBRockCount = (UINT)_wtoi(szBuff);

	fwscanf_s(pFile, L"%s", szBuff, 256);
	for (size_t i = 0; i < m_iOBRockCount; i++)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);

		// 바위 좌표 로드
		Vec vecTilePos = Vec{};
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.x = (float)_wtof(szBuff);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.y = (float)_wtof(szBuff);

		// 바위 생성
		CTile* pTile = m_pTileMap->FindTile((UINT)vecTilePos.x, (UINT)vecTilePos.y);
		if (nullptr != pTile)
		{
			CRock* pRock = new CRock(pTile);
			pTile->AddObstacle(pRock);
			AddObject(pRock, EOBJ_TYPE::OBSTACLE);
		}
	}

	// 언데드 정보 로드
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_iOBUndeadCount = (UINT)_wtoi(szBuff);

	fwscanf_s(pFile, L"%s", szBuff, 256);
	for (size_t i = 0; i < m_iOBUndeadCount; i++)
	{
		fwscanf_s(pFile, L"%s", szBuff, 256);

		// 언데드 좌표 로드
		Vec vecTilePos = Vec{};
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.x = (float)_wtof(szBuff);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		vecTilePos.y = (float)_wtof(szBuff);

		// 언데드 생성
		CTile* pTile = m_pTileMap->FindTile((UINT)vecTilePos.x, (UINT)vecTilePos.y);
		if (nullptr != pTile)
		{
			CUndead* pUndead = new CUndead(pTile);
			pTile->AddObstacle(pUndead);
			AddObject(pUndead, EOBJ_TYPE::OBSTACLE);
		}
	}
	
	// ===============
	//	  파일 닫기
	// ===============
	fclose(pFile);
}

CStage_Puzzle::~CStage_Puzzle()
{
}