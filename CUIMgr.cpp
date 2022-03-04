#include "pch.h"
#include "CUIMgr.h"

#include "CStageMgr.h"
#include "CStage.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pTargetUI(nullptr)
	, m_pFocusedUI(nullptr)
	, m_pPressedUI(nullptr)
	, m_pUpUI(nullptr)
	, m_bMouseLbtnDown(false)
	, m_bMouseLbtnUp(false)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	m_pTargetUI = nullptr;
	m_pFocusedUI = nullptr;

	CStage* pStage = CStageMgr::GetInst()->GetCurStage();
	vector<CObj*>& vecUI = pStage->GetObjectsRef(EOBJ_TYPE::UI);

	// UI 가 없으면 종료
	if (vecUI.empty())
		return;

	// 이번 프레임 키 상태
	m_vMousePos = CKeyMgr::GetInst()->GetMousePos();
	m_bMouseLbtnDown = KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN) ? true : false;
	m_bMouseLbtnUp = KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN) ? true : false;

	// UI 상태 체크
	size_t iFocusedIdx = 0;
	CUI* pParentUI = nullptr;
	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// 이벤트 타겟 UI 찾기
		// m_pTargetUI 에 현재 타겟팅 된 UI 가 설정 됨
		CUI* pTargetUI = GetTargetUI(pUI);

		if (nullptr != pTargetUI)
		{
			m_pTargetUI = pTargetUI;
			pParentUI = pUI;
			iFocusedIdx = i;
		}
	}

	if (m_pTargetUI)
	{
		if (m_bMouseLbtnDown)
		{
			m_pTargetUI->MouseLbtnDown(m_vMousePos);
			m_pPressedUI = m_pTargetUI;
			m_pFocusedUI = pParentUI;

			// FocusedUI 가 변경되면, 맨 끝자리로 보낸다.
			vector<CObj*>::iterator iter = vecUI.begin() + iFocusedIdx;
			vecUI.erase(iter);
			vecUI.push_back(m_pFocusedUI);
		}
		// 마우스가 떼졌으면, 무조건 상태 해제
		else if (m_bMouseLbtnUp)
		{
			m_pTargetUI->MouseLbtnUp(m_vMousePos);
			m_pUpUI = m_pTargetUI;
		}
	}

	// 눌렸던 UI 랑 뗀 UI 가 같았다.
	if (nullptr != m_pPressedUI && m_pPressedUI == m_pUpUI)
	{
		m_pPressedUI->MouseLbtnClicked(m_vMousePos);		
	}

	// 마우스가 떼졌으면, 기존에 기억하던 UI 들 해제
	if (m_bMouseLbtnUp)
	{
		m_pPressedUI = nullptr;
		m_pUpUI = nullptr;
	}
}

CUI* CUIMgr::GetTargetUI(CUI* _pUI)
{
	m_queue.push_back(_pUI);

	CUI* pTargetUI = nullptr;

	while (false == m_queue.empty())
	{
		CUI* pUI = m_queue.front();
		m_queue.pop_front();

		// 마우스가 해당 UI 위에 있냐
		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;

			const vector<CUI*>& vecChildUI = pUI->GetChildUI();
			for (size_t i = 0; i < vecChildUI.size(); ++i)
			{
				m_queue.push_back(vecChildUI[i]);
			}
		}
	}

	return pTargetUI;
}
