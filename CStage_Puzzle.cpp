#include "pch.h"
#include "CStage_Puzzle.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CKeyMgr.h"


#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CBackGround.h"
#include "CTile.h"
#include "CTileMap.h"
#include "CHero.h"
#include "CNPC.h"
#include "CTransition.h"


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
	// Ʈ������ ����	
	m_pTransition = new CTransition;
	m_pTransition->SetPos(Vec{ CCore::GetInst()->GetResolution().x / 2.f, CCore::GetInst()->GetResolution().y / 2.f });
	AddObject(m_pTransition, EOBJ_TYPE::DEFAULT);
}


void CStage_Puzzle::Init()
{
	// �ػ� ���ϱ�
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// BG ����
	vector<CObj*> bg_check = GetObjects(EOBJ_TYPE::BG);
	if (bg_check.empty())
	{
		CBackGround* pBG = new CBackGround(m_eChapter);
		AddObject(pBG, EOBJ_TYPE::BG);
	}
	 
	// Ÿ�ϸ� ����
	CTileMap* pTileMap = new CTileMap;
	pTileMap->Load(L"stage\\" + GetStageName() + L".tilemap");
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
	// ������ Ƚ�� Load

}

void CStage_Puzzle::Update()
{
	CStage::Update();

	// Ʈ�������� ����� ���Ŀ� ȭ�鿡 Object���� �ε��Ѵ�.
	if (nullptr != m_pTransition)
	{
		CAnimation* pAnimation = m_pTransition->GetAnimator()->GetCurAnimation();
		if (pAnimation->IsFinished())
		{
			DeleteObject(m_pTransition);
			m_pTransition = nullptr;
			Init();
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
		// �̵� Ƚ�� ����

	}
}

void CStage_Puzzle::Exit()
{
	CStage::Clear();
}

CStage_Puzzle::~CStage_Puzzle()
{
}