#pragma once
#include "CObj.h"
class CTileMap :
    public CObj
{
private:
    wstring          m_strStageName;
    map<Vec, CTile*> m_mTileMap;
    
    CTile*  m_pStartTile; // 시작 위치 : 히어로 스폰 위치
    Vec     m_vSize;     // 타일맵 크기(가로, 세로)
    Vec     m_vPos;      // 타일맵 위치

public:
    void CreateTile(UINT _iCol, UINT _iRow, Vec _vPos);
    void CreateTile(Vec _vLoc, Vec _vPos);
    
    CTile* FindTile(UINT _iCol, UINT _iRow);
    void ClearTileMap();
    
    CTile* GetStartTile() { return m_pStartTile; }

    void Save(const wstring& _strRelativeFolderPath);
    void Load(const wstring& _strRelativeFilePath);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CTileMap();
    virtual ~CTileMap();

};

