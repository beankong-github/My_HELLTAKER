#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_bMouseOn(false)
	, m_bMouseLbtnPressed(false)
	, m_ClickDelegate{}
{
}

CUI::CUI(const CUI& _origin)
	: CObj(_origin)
	, m_pParent(nullptr)	
	, m_bMouseOn(false)
	, m_bMouseLbtnPressed(false)
	, m_ClickDelegate(_origin.m_ClickDelegate)
{
	// _origin.m_vecChildUI; -> m_vecChildUI;
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_origin.m_vecChildUI[i]->Clone());		
	}
}

CUI::~CUI()
{
	Safe_Del_Vec(m_vecChildUI);
}

void CUI::DragDrop_update()
{
	if (IsLbtnPressed())
	{
		// 현재 마우스 위치
		Vec vMousePos = CKeyMgr::GetInst()->GetMousePos();

		// 현재 마우스 위치에서 UI 를 눌렀을때 좌표를 빼서 차이값을 구함
		Vec vDiff = vMousePos - GetLbtnPressedPos();

		// 차이값 만큼 더해줌
		SetPos(GetPos() + vDiff);

		// 마우스를 눌린 위치를 현재 마우스 위치로 갱신
		SetLbtnPressedPos(vMousePos);
	}
}

void CUI::Update()
{
	Vec vPos = GetPos();

	if (nullptr == m_pParent)
	{
		m_vFinalPos = vPos;
	}
	else
	{
		m_vFinalPos = vPos + m_pParent->GetFinalPos();
	}

	// MouseOn Check
	m_bMouseOn = IsMouseOn(CKeyMgr::GetInst()->GetMousePos());

	// Mouse Up Check
	if (IS_KEY_AWAY(KEY::LBTN))
	{
		m_bMouseLbtnPressed = false;
	}


	// ChildUI update
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void CUI::Render(HDC _dc)
{
	Vec vFinalPos = GetFinalPos();
	Vec vScale = GetScale();

	Rectangle(_dc
		, int(vFinalPos.x)
		, int(vFinalPos.y)
		, int(vFinalPos.x + vScale.x)
		, int(vFinalPos.y + vScale.y));

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}


bool CUI::IsMouseOn(Vec _vMouseRealPos)
{
	Vec vPos = GetFinalPos();
	Vec vScale = GetScale();

	if (vPos.x <= _vMouseRealPos.x && _vMouseRealPos.x <= (vPos.x + vScale.x)
		&& vPos.y <= _vMouseRealPos.y && _vMouseRealPos.y <= (vPos.y + vScale.y))
	{
		return true;
	}

	return false;
}


void CUI::MouseLbtnClicked(Vec _vMousePos)
{
	if (nullptr != m_ClickDelegate.pStage && nullptr != m_ClickDelegate.pMemFunc)
	{
		(m_ClickDelegate.pStage->*m_ClickDelegate.pMemFunc)();
	}
}
