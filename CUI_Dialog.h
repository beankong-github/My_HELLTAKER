#pragma once
#include "CObj.h"
#include "CUI.h"

struct Dialog_Page
{   
    /* Dialog Info */
    CTexture* m_pPortrait;
   
    wstring m_wstrName;
    wstring m_wstrText;

    /* Button Info */
    wstring m_wstrOptionOneText;
    bool    m_bOptionOneIsAnswer;
    
    wstring m_wstrOptionTwoText;
    bool    m_bOptionTwoIsAnswer;
};

class CBtn_Option;

class CUI_Dialog :
    public CUI
{
private:
    wstring     m_wstrID;
    UINT        m_iSize;
    UINT        m_iCurPage;

    CTexture* m_pDialogBox;
    CTexture* m_pBGTex;
    bool      m_bBGFlow;
    
    CBtn_Option* m_pFirstOption;
    CBtn_Option* m_pSecondeOption;

    CAnimation* m_pBooper;

    vector<Dialog_Page*> m_pDialogs;

    /* Position Info*/
    Vec m_vBGPos;
    Vec m_vPortaritPos;
    Vec m_vBooperPos;
    Vec m_vOptionOnePos;
    Vec m_vOptionTwoPos;

public:
    UINT GetCurPage() { return m_iCurPage; }

public:
    void Load();

public:
    void FirstOptionSelected();
    void SecondOptionSelected();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    CUI_Dialog(wstring _ID);
    virtual ~CUI_Dialog();
};

