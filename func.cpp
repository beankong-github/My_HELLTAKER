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
