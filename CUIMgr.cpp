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

	// UI �� ������ ����
	if (vecUI.empty())
		return;

	// �̹� ������ Ű ����
	m_vMousePos = CKeyMgr::GetInst()->GetMousePos();
	m_bMouseLbtnDown = KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN) ? true : false;
	m_bMouseLbtnUp = KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN) ? true : false;

	// UI ���� üũ
	size_t iFocusedIdx = 0;
	CUI* pParentUI = nullptr;
	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// �̺�Ʈ Ÿ�� UI ã��
		// m_pTargetUI �� ���� Ÿ���� �� UI �� ���� ��
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

			// FocusedUI �� ����Ǹ�, �� ���ڸ��� ������.
			vector<CObj*>::iterator iter = vecUI.begin() + iFocusedIdx;
			vecUI.erase(iter);
			vecUI.push_back(m_pFocusedUI);
		}
		// ���콺�� ��������, ������ ���� ����
		else if (m_bMouseLbtnUp)
		{
			m_pTargetUI->MouseLbtnUp(m_vMousePos);
			m_pUpUI = m_pTargetUI;
		}
	}

	// ���ȴ� UI �� �� UI �� ���Ҵ�.
	if (nullptr != m_pPressedUI && m_pPressedUI == m_pUpUI)
	{
		m_pPressedUI->MouseLbtnClicked(m_vMousePos);		
	}

	// ���콺�� ��������, ������ ����ϴ� UI �� ����
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

		// ���콺�� �ش� UI ���� �ֳ�
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
