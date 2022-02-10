#pragma once
#include "CObj.h"
class CTileMap :
    public CObj
{
private:
    wstring          m_strStageName;
    map<Vec, CTile*> m_mTileMap;

    Vec     m_vSize;
    Vec     m_vPos;

public:
    void CreateTile(UINT _iCol, UINT _iRow, Vec _vPos);
    void CreateTile(Vec _vLoc, Vec _vPos);
    void ClearTileMap();

    void Save(const wstring& _strRelativeFolderPath);
    void Load(const wstring& _strRelativeFilePath);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CTileMap();
    virtual ~CTileMap();

};

