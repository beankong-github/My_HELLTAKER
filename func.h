#pragma once

class CObj;

void CreateObject(CObj* _pNewObj, EOBJ_TYPE _eObjType, Vec _vPos);

void DeleteObject(CObj* _pTargetObj);

void ChangeStage(ESTAGE_TYPE _eNextStage);

void SaveWString(const wstring& _str, FILE* _pFile);

void LoadWString(wstring& _str, FILE* _pFile);
