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
	, m_pAtlas(nullptr)
	, m_vecFrm(0)
	, m_iCuridx(0)
	, m_fAddTime(0)
	, m_bFinish(0)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish)
		true;

	m_fAddTime += DS;

	if (m_fAddTime >= m_vecFrm[m_iCuridx].fDuration)
	{
		++m_iCuridx;
		if (m_iCuridx >= m_vecFrm.size())
		{
			m_iCuridx -= 1;		// 마지막 프레임
			m_bFinish = true;
			return;
		}
		 m_fAddTime = m_fAddTime - m_vecFrm[m_iCuridx].fDuration;
	}
}

void CAnimation::Render(HDC _dc)
{
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetOwner()->GetPos());

	TransparentBlt(_dc
		, int(vRenderPos.x - m_vecFrm[m_iCuridx].vSize.x / 2.f + m_vecFrm[m_iCuridx].vOffset.x)	// x
		, int(vRenderPos.y - m_vecFrm[m_iCuridx].vSize.y / 2.f + m_vecFrm[m_iCuridx].vOffset.y)	// y
		, int(m_vecFrm[m_iCuridx].vSize.x)	// width
		, int(m_vecFrm[m_iCuridx].vSize.y)	// height
		, m_pAtlas->GetDC()	// Src's HDC
		, int(m_vecFrm[m_iCuridx].vLeftTop.x)	// x pos in atlas
		, int(m_vecFrm[m_iCuridx].vLeftTop.y)	// y pos in atlas
		, int(m_vecFrm[m_iCuridx].vSize.x)		// width in atlas
		, int(m_vecFrm[m_iCuridx].vSize.y)		// height int atlas
		, RGB(255, 0, 255));
}

void CAnimation::Create(const wstring& _strAnimName, CTexture* _pAtlasTex, Vec _vLeftTop, Vec _vSize, Vec _vOffset, float _fxDistance, float _fDuration, UINT _iFrmCount)
{
	m_strName = _strAnimName;
	m_pAtlas = _pAtlasTex;
	
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrmCount; i++)
	{
		frm.vLeftTop = Vec(_vLeftTop.x + (float)i * _fxDistance, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;
	
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
	//	파일 경로 찾기
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += m_strName;
	strFilePath += L".anim";
	
	// ===============
	//	  파일 열기
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// 파일 포인터 변수의 주소값을 받아가서 파일의 주소를 저장해준다.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"애니메이션 저장 오류", MB_OK);
	}

	// =======================
	// 애니메이션 데이터 저장하기
	// =======================

	// 애니메이션 이름
	SaveWString(m_strName, pFile);
	
	// 아틀라스 텍스쳐 정보 - 이름, 주소
	SaveWString(m_pAtlas->GetKey(), pFile);
	SaveWString(m_pAtlas->GetRelativePath(), pFile);

	// 각 프레임 정보
	size_t iFrmCount = m_vecFrm.size();
	fwrite(&iFrmCount, sizeof(size_t), 1, pFile);
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), m_vecFrm.size(), pFile);

	// ===============
	//	  파일 닫기
	// ===============
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	// ===============
	//	절대 경로 찾기
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	

	// ===============
	//	  파일 열기
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// 해당 경로의 파일을 읽기 모드로 열어 파일 포인터 변수의 주소값에 파일의 주소를 저장해준다.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"에러 발생, 에러코드: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"애니메이션 로딩 오류", MB_OK);
	}


	// =======================
	// 애니메이션 데이터 읽어오기
	// =======================
	
	// 애니메이션 이름
	LoadWString(m_strName, pFile);		
	
	// 아틀라스 텍스쳐 정보 - 이름, 주소
	wstring strAtlasName;
	wstring strAtlasRelativePath;

	LoadWString(strAtlasName, pFile);
	LoadWString(strAtlasRelativePath, pFile);

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strAtlasName, strAtlasRelativePath);

	// 각 프레임 정보
	size_t iFrmCount = 0;
	fread(&iFrmCount, sizeof(size_t), 1, pFile);
	
	for (size_t i = 0; i < iFrmCount; ++i)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}


	// ===============
	//	  파일 닫기
	// ===============
	fclose(pFile);

}

