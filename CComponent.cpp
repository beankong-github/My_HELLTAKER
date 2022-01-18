#include "pch.h"
#include "CComponent.h"


CComponent::CComponent(ECOM_TYPE _eType)
	: m_eType(_eType)
	, m_pOwer(nullptr)
{
}

CComponent::~CComponent()
{
}

void CComponent::Render(HDC _dc)
{
}
