#include "pch.h"
#include "CKeyMgr.h"

// KEY enum 순서에 대응하는 키에 대한 아스키코드
int g_iVK[(UINT)KEY::KEY_END] = 
{
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,
	VK_RETURN,
	VK_BACK,
	VK_ESCAPE,
	VK_TAB,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}


void CKeyMgr::Init()
{
	// 키 상태 초기화해서 벡터(동적배열)에 저장
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	// 모든 키의 상태 체크
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		// 키가 눌려있다.
		if (GetAsyncKeyState(g_iVK[i]) & 0x8000)
		{
			// 이전에 눌리지 않았다.
			if (false == m_vecKey[i].bprevCheck)
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			// 이전에 눌려 있었다.
			else
			{
				m_vecKey[i].eState = KEY_STATE::PRESSED;
			}
			
			// 현재 입력상태를 저장
			m_vecKey[i].bprevCheck = true;
		}

		// 키가 눌려있지 않다.
		else
		{
			// 이전에 눌려있었다.
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::PRESSED == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			// 이전에 눌려있지 않았다
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			// 현재 입력상태를 저장
			m_vecKey[i].bprevCheck = false;
		}
	}
}
