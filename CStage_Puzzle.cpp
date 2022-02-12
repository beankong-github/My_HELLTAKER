#include "pch.h"
#include "CStage_Puzzle.h"

#include "CCore.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CBackGround.h"
#include "CTile.h"
#include "CTileMap.h"
#include "CHero.h"

CStage_Puzzle::CStage_Puzzle(ECHAPTER _chap)
	: m_eChapter(_chap)
	, m_vTileCount{9, 7}
	, m_vTileStartPos{510.f, 143.f}
	, m_iInitMoveCount(0)
	, m_iCurMoveCount(0)
{
	if (ECHAPTER::NONE == _chap || ECHAPTER::END == _chap)
	{
		assert(nullptr);
	}

	SetStageName(L"CHAP_" + std::to_wstring((UINT)_chap));
}

CStage_Puzzle::~CStage_Puzzle()
{
}

void CStage_Puzzle::Init()
{
	// 해상도 구하기
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// BG 생성
	vector<CObj*> bg_check = GetObjects(EOBJ_TYPE::BG);
	if (bg_check.empty())
	{
		CBackGround* pBG = new CBackGround(m_eChapter);
		AddObject(pBG, EOBJ_TYPE::BG);
	}
	 
	// 타일맵 생성
	CTileMap* pTileMap = new CTileMap;
	pTileMap->Load(L"stage\\" + GetStageName() + L".tilemap");
	//pTileMap->CreateTile(m_vTileCount, m_vTileStartPos);
	//pTileMap->Save(L"stage\\");
	AddObject(pTileMap, EOBJ_TYPE::TILEMAP);


	// hero 추가
	CObj* pHero = new CHero;
	pHero->SetPos(Vec(ptResolution.x / 2.f, ptResolution.y / 2.f));
	pHero->SetScale(Vec(100, 100));
	AddObject(pHero, EOBJ_TYPE::PLAYER);
}

void CStage_Puzzle::Update()
{
	CStage::Update();
}

void CStage_Puzzle::Render(HDC _dc)
{
	CStage::Render(_dc);
}

void CStage_Puzzle::Enter()
{
	Init();
}

void CStage_Puzzle::Exit()
{
}

