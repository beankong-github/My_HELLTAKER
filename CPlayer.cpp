#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CBullet.h"
#include "CStage.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h  "

CPlayer::CPlayer()
	:m_fSpeed(400.f)
	, m_pTex(nullptr)
{
	//// 현재 디렉토리 경로 받아오기
	//wchar_t szPath[256] = {};
	//GetCurrentDirectory(256, szPath);

	//// 비행기(플레이어) 이미지 가져오기
	//wstring strPath = szPath;
	//strPath += L"\\Plane.bmp";

	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();

	// 텍스처 한 장 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", strPath);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	Vec vPos = GetPos();
	
	// Player 이동
	if (IS_KEY_PRESSED(KEY::LEFT)) // VK_LEFT가 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태라면
	{
		vPos.x -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::UP))
	{
		vPos.y -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DS;
	}

	// 총알 생성
	if (IS_KEY_TAP(KEY::SPACE))
	{
		// Bullet 초기화
		CObj* bObj = new CBullet;
		bObj->SetPos(Vec{ GetPos().x, GetPos().y - GetScale().y/2});
		bObj->SetScale(Vec{ 30, 30 });
		
		// StageMgr로부터 현재 스테이지를 가져온다
		CStage* curStage = CStageMgr::GetInst()->GetCurStage();
		curStage->AddObject(bObj);
	}
	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	// 이미지로 출력
	Vec vPos = GetPos();

	BitBlt(_dc, (int)vPos.x - 32, (int)vPos.y - 32, 64, 64, m_pTex->GetDC(), 0, 0, SRCCOPY);
}
