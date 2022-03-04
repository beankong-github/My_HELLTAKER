#include "pch.h"
#include "func.h"
#include "CEventMgr.h"
#include "CObj.h"

void CreateObject(CObj* _pNewObj, EOBJ_TYPE _eType, Vec _vPos)
{
	// 위치 설정
	_pNewObj->SetPos(_vPos);

	// 이벤트 처리
	tEventInfo info = {};
	info.eType = EEVENT_TYPE::CREATE_OBJ;
	info.lParam = (DWORD_PTR)_pNewObj;
	info.wParam = (DWORD_PTR)_eType;
	
	CEventMgr::GetInst()->AddEvent(info);

}

void DeleteObject(CObj* _pTargetObj)
{
	// 이벤트 처리
	tEventInfo info = {};
	info.eType = EEVENT_TYPE::DELETE_OBJ;
	info.lParam = (DWORD_PTR)_pTargetObj;

	CEventMgr::GetInst()->AddEvent(info);
}

void ChangeStage(ESTAGE_TYPE _eNextStage)
{
	// 이벤트 처리
	tEventInfo info = {};
	info.eType = EEVENT_TYPE::STAGE_CHANGE;
	info.lParam = (DWORD_PTR)_eNextStage;

	CEventMgr::GetInst()->AddEvent(info);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	const wchar_t* pStr =  _str.c_str();
	
	size_t iLen = _str.length();

	// 문자열 글자수 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	
	// 문자열 저장
	fwrite(pStr, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	// 글자수 읽어오기
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	// 문자열 읽어오기
	wchar_t szData[256] = {};
	fread(szData, sizeof(wchar_t), iLen, _pFile);

	_str = szData;
}
