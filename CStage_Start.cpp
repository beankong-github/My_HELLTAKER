#include "pch.h"
#include "CStage_Start.h"
#include "CCore.h"
#include "CPlayer.h"

CStage_Start::CStage_Start()
{
}

CStage_Start::~CStage_Start()
{
}

void CStage_Start::Init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// player ÃÊ±âÈ­
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec{ ptResolution.x / 2, ptResolution.y / 2 });
	pObj->SetScale(Vec{ 100, 100 });
	AddObject(pObj);
}

