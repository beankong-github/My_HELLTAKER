#pragma once

class CObj;

void CreateObject(CObj* _pNewObj, EOBJ_TYPE _eObjType, Vec _vPos);

void DeleteObject(CObj* _pTargetObj);

void ChangeStage(ESTAGE_TYPE _eNextStage);