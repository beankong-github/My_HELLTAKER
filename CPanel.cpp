#include "pch.h"
#include "CPanel.h"

CPanel::CPanel()
{
}

CPanel::~CPanel()
{
}

void CPanel::Update()
{
	DragDrop_update();

	CUI::Update();
}

void CPanel::Render(HDC _dc)
{
	CUI::Render(_dc);
}

void CPanel::MouseLbtnClicked(Vec _vMousePos)
{
	CUI::MouseLbtnClicked(_vMousePos);

	int a = 0;
}