#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	list<CUI*>	m_queue;


	CUI*		m_pTargetUI;  // 마우스가 올라가 있는 UI, 우선순위는 자식UI 가 더 높음
	CUI*		m_pFocusedUI; // 부모 UI 중에 우선순위가 가장 높은 UI

	CUI*		m_pPressedUI; // 마우스가 눌렸을때 타겟 UI
	CUI*		m_pUpUI;	  // 마우스가 뗄 때 타겟이었던 UI

	Vec			m_vMousePos;
	bool		m_bMouseLbtnDown;
	bool		m_bMouseLbtnUp;

public:
	void Update();

private:
	CUI* GetTargetUI(CUI* _pUI);

};

