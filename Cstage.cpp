#include "pch.h"
#include "CStage.h"
#include "CCore.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CBullet.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

void CStage::Init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// player ÃÊ±âÈ­
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec{ ptResolution.x / 2, ptResolution.y / 2 });
	pObj->SetScale(Vec{ 100, 100 });
	AddObject(pObj);
}

void CStage::Update()
{
	for (size_t i = 0; i < m_vecObj.size(); i++)
	{
		m_vecObj[i]->Update();
	}
}

void CStage::Render(HDC _dc)
{
	for (size_t i = 0; i < m_vecObj.size(); i++)
	{
		m_vecObj[i]->Render(_dc);
	}
}
