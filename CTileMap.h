#pragma once
#include "CObj.h"
class CTileMap :
    public CObj
{
private:
    wstring          m_strStageName;
    map<Vec, CTile*> m_mTileMap;
    
    CTile*  m_pStartTile; // ���� ��ġ : ����� ���� ��ġ
    Vec     m_vSize;     // Ÿ�ϸ� ũ��(����, ����)
    Vec     m_vPos;      // Ÿ�ϸ� ��ġ

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

