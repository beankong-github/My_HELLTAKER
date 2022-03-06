#include "pch.h"
#include "CSoundMgr.h"
#include "CResMgr.h" 
#include "CSound.h"

#include "CCore.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}

int CSoundMgr::Init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = CCore::GetInst()->GetMainWndHWND();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}