#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CCore.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CTexture.h"

CAnimation::CAnimation()
	: m_strName()
	, m_pAnimator(nullptr)
	, m_vecFrm(0)
	, m_iCuridx(0)
	, m_fAddTime(0)
	, m_bFinish(false)
	, m_bFlip(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish)
		return;

	m_fAddTime += DS;

	if (m_fAddTime >= m_vecFrm[m_iCuridx].fDuration)
	{
		++m_iCuridx;
		if (m_iCuridx >= m_vecFrm.size())
		{
			m_iCuridx -= 1;		// ������ ������
			m_bFinish = true;
			return;
		}
		 m_fAddTime = m_fAddTime - m_vecFrm[m_iCuridx].fDuration;
	}
}

void CAnimation::Render(HDC _dc)
{
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetOwner()->GetPos());
	m_bFlip = GetOwner()->IsFlip();

	if (m_bFlip)	// �̹��� �¿� ����
	{
		// �̹��� �¿� ������ ���� DC ����
		HDC reverseDC = CreateCompatibleDC(_dc);
		HBITMAP buffer = CreateCompatibleBitmap(m_vecFrm[m_iCuridx].pTex->GetDC(), (int)m_vecFrm[m_iCuridx].vSize.x, (int)m_vecFrm[m_iCuridx].vSize.y);
		HGDIOBJ oldObj = SelectObject(reverseDC, buffer);

		StretchBlt(reverseDC
			, int(m_vecFrm[m_iCuridx].vSize.x)	// x
			, 0	// y
			, int(-(m_vecFrm[m_iCuridx].vSize.x + 1))
			, int(m_vecFrm[m_iCuridx].vSize.y)
			, m_vecFrm[m_iCuridx].pTex->GetDC()
			, 0, 0
			, int(m_vecFrm[m_iCuridx].vSize.x)		// width in atlas
			, int(m_vecFrm[m_iCuridx].vSize.y)		// height int atlas
			, SRCCOPY
		);

		TransparentBlt(_dc
			, int(vRenderPos.x - m_vecFrm[m_iCuridx].vSize.x / 2.f)	// x
			, int(vRenderPos.y - m_vecFrm[m_iCuridx].vSize.y / 2.f)	// y
			, int(m_vecFrm[m_iCuridx].vSize.x)	// width
			, int(m_vecFrm[m_iCuridx].vSize.y)	// height
			, reverseDC	// Src's HDC
			, 0, 0
			, int(m_vecFrm[m_iCuridx].vSize.x)		// width in atlas
			, int(m_vecFrm[m_iCuridx].vSize.y)		// height int atlas
			, RGB(112, 12, 41));

		DeleteObject(buffer);
		DeleteObject(oldObj);
		DeleteObject(reverseDC);
	}

	else
	{
		TransparentBlt(_dc
			, int(vRenderPos.x - m_vecFrm[m_iCuridx].vSize.x / 2.f)	// x
			, int(vRenderPos.y - m_vecFrm[m_iCuridx].vSize.y / 2.f)	// y
			, int(m_vecFrm[m_iCuridx].vSize.x)	// width
			, int(m_vecFrm[m_iCuridx].vSize.y)	// height
			, m_vecFrm[m_iCuridx].pTex->GetDC()	// Src's HDC
			, 0, 0
			, int(m_vecFrm[m_iCuridx].vSize.x)		// width in atlas
			, int(m_vecFrm[m_iCuridx].vSize.y)		// height int atlas
			, RGB(112, 12, 41));
	}
}

void CAnimation::Create(const wstring& _strAnimName, const wstring& _strRelativePath, float _fDuration, UINT _iFrmCount)
{
	m_strName = _strAnimName;

	tAnimFrm frm = {};
	for (UINT i = 1; i <= _iFrmCount; i++)
	{
		frm.strName = _strAnimName + L"_" + std::to_wstring(i);
		frm.strRelativeTexPath = _strRelativePath + frm.strName + L".bmp";
		frm.pTex = CResMgr::GetInst()->LoadTexture(frm.strName, frm.strRelativeTexPath.c_str());
		frm.fDuration = _fDuration;
		frm.vSize = Vec{ frm.pTex->Width(), frm.pTex->Height() };
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Reset()
{
	m_iCuridx = 0;
	m_fAddTime = 0.f;
	m_bFinish = false;
}

CObj* CAnimation::GetOwner()
{ 
	return m_pAnimator->GetOwner();
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += m_strName;
	strFilePath += L".anim";

	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// ���� ������ ������ �ּҰ��� �޾ư��� ������ �ּҸ� �������ش�.
	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"�ִϸ��̼� ���� ����", MB_OK);

		return;
	}

	// =======================
	// �ִϸ��̼� ������ �����ϱ�
	// =======================

	// �ִϸ��̼� �̸�
	fwprintf_s(pFile, L"[Animation_Name]\n");
	fwprintf_s(pFile, m_strName.c_str());
	fwprintf_s(pFile, L"\n\n");

	// �� ������ ����
	fwprintf_s(pFile, L"[Frame_Information]\n");
	fwprintf_s(pFile, L"[Frame_Count]\n");
	fwprintf_s(pFile, L"%d", (int)m_vecFrm.size());
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[Frame_Name]\n");
		fwprintf_s(pFile, m_vecFrm[i].strName.c_str());
		fwprintf_s(pFile, L"\n");

		fwprintf_s(pFile, L"[Frame_Adress]\n");
		fwprintf_s(pFile, m_vecFrm[i].strRelativeTexPath.c_str());
		fwprintf_s(pFile, L"\n");


		fwprintf_s(pFile, L"[Size]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		fwprintf_s(pFile, L"[Duration]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].fDuration);
	}

	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;


	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// �ش� ����� ������ �б� ���� ���� ���� ������ ������ �ּҰ��� ������ �ּҸ� �������ش�.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"�ִϸ��̼� �ε� ����", MB_OK);

		return;
	}

	// =======================
	// �ִϸ��̼� ������ �о����
	// =======================


	// �ִϸ��̼� �̸�
	wchar_t szBuff[256] = L"";
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	m_strName = szBuff;

	// �� ������ ����
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);

	int iFrmCount = 0;
	fwscanf_s(pFile, L"%d", &iFrmCount);

	for (int i = 0; i < iFrmCount; ++i)
	{
		tAnimFrm frm = {};

		// ������ �̸�
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		frm.strName = szBuff;

		// ������ �ּ�
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		frm.strRelativeTexPath = szBuff;

		// ������ �ؽ�ó
		frm.pTex = CResMgr::GetInst()->LoadTexture(frm.strName, frm.strRelativeTexPath.c_str());


		// ������ �̹��� ũ��
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);

		// ������ ����
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f", &frm.fDuration);

		m_vecFrm.push_back(frm);
	}

	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

