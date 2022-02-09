#include "pch.h"
#include "CStage_Puzzle.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CBackGround.h"

CStage_Puzzle::CStage_Puzzle(ECHAPTER _chap)
	: m_eChapter(_chap)
	, m_vTileCount{}
	, m_iInitMoveCount(0)
	, m_iCurMoveCount(0)
{
	if (ECHAPTER::NONE == _chap || ECHAPTER::END == _chap)
	{
		assert(nullptr);
	}
	
	CBackGround* pBG = new CBackGround(m_eChapter);
	AddObject(pBG, EOBJ_TYPE::BG);
}

CStage_Puzzle::~CStage_Puzzle()
{
}

void CStage_Puzzle::Init()
{
	CreateTile(10, 10);
}

void CStage_Puzzle::Update()
{
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

